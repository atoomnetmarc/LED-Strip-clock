/**
 * @file WebServerService.cpp
 * @brief Embedded web UI, API and OTA server
 *
 * @copyright Marc Ketel
 * SPDX-License-Identifier: Apache-2.0
 */

#include "WebServerService.h"

#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <Updater.h>
#include <Wire.h>
#include <time.h>

#include "RtcService.h"

#include "ConfigStore.h"
#include "Log.h"
#include "PowerMonitor.h"
#include "WebContent.h"

namespace webserver {
    ESP8266WebServer server(80);
    DNSServer *dnsServer = nullptr;

    bool portal = false;
    uint32_t staDisconnectedSince = 0;
    constexpr uint32_t PORTAL_FALLBACK_DELAY_MS = 30000;

    // Single active login session (STA mode).
    char sessionToken[33] = "";
    uint32_t sessionExpiry = 0;
    constexpr uint32_t SESSION_TTL_MS = 60UL * 60 * 1000;

    uint32_t lastNtpSync = 0; // millis() of last successful sync

    void noteNtpSync() {
        lastNtpSync = millis();
    }

    bool portalActive() {
        return portal;
    }

    // ------------------------------------------------------------------
    // Helpers
    // ------------------------------------------------------------------

    void sendGzipRoot() {
        server.sendHeader("Content-Encoding", "gzip");
        server.sendHeader("Cache-Control", "no-cache");
        server.send_P(200, "text/html", reinterpret_cast<PGM_P>(WEBUI_HTML_GZ), WEBUI_HTML_GZ_LEN);
    }

    bool sessionValid() {
        if (sessionToken[0] == '\0' || millis() > sessionExpiry) {
            return false;
        }

        String cookie = server.header("Cookie");
        int pos = cookie.indexOf("lsck=");
        if (pos < 0) {
            return false;
        }
        String token = cookie.substring(pos + 5, pos + 5 + 32);
        return token == sessionToken;
    }

    // Writes are allowed when the AP portal is open (physical possession of
    // the network) or with a valid login session on STA.
    bool authorized() {
        return portal || sessionValid();
    }

    bool requireAuth() {
        if (authorized()) {
            return true;
        }
        server.send(401, "application/json", "{\"error\":\"not authorized\"}");
        return false;
    }

    // Extract a "key":"value" string from a small JSON body.
    bool jsonGetString(const char *body, const char *key, char *out, size_t outLen) {
        char pattern[40];
        snprintf(pattern, sizeof(pattern), "\"%s\":\"", key);
        const char *start = strstr(body, pattern);
        if (start == nullptr) {
            return false;
        }
        start += strlen(pattern);

        size_t pos = 0;
        while (*start != '\0' && *start != '"' && pos + 1 < outLen) {
            if (*start == '\\' && *(start + 1) != '\0') {
                start++;
            }
            out[pos++] = *start++;
        }
        out[pos] = '\0';
        return true;
    }

    bool jsonGetNumber(const char *body, const char *key, long &out) {
        char pattern[40];
        snprintf(pattern, sizeof(pattern), "\"%s\":", key);
        const char *start = strstr(body, pattern);
        if (start == nullptr) {
            return false;
        }
        start += strlen(pattern);
        out = strtol(start, nullptr, 10);
        return true;
    }

    // ------------------------------------------------------------------
    // Handlers
    // ------------------------------------------------------------------

    void handleRoot() {
        sendGzipRoot();
    }

    void handleStatus() {
        time_t now;
        time(&now);
        tm timeInfo;
        localtime_r(&now, &timeInfo);

        char timeBuf[16];
        char dateBuf[16];
        snprintf(timeBuf, sizeof(timeBuf), "%02d:%02d:%02d",
                 timeInfo.tm_hour, timeInfo.tm_min, timeInfo.tm_sec);
        snprintf(dateBuf, sizeof(dateBuf), "%04u-%02u-%02u",
                 static_cast<unsigned>(timeInfo.tm_year + 1900),
                 static_cast<unsigned>(timeInfo.tm_mon + 1),
                 static_cast<unsigned>(timeInfo.tm_mday));

        // RTC presence is probed once at boot by the RtcService (DS3231 @ 0x68).
        bool rtcPresent = rtc::present();

        char timeSource[32];
        if (lastNtpSync != 0 && millis() - lastNtpSync < 2UL * 24 * 60 * 60 * 1000) {
            snprintf(timeSource, sizeof(timeSource), "NTP");
        } else if (rtcPresent) {
            snprintf(timeSource, sizeof(timeSource), "RTC");
        } else {
            snprintf(timeSource, sizeof(timeSource), "system clock");
        }

        char lastSync[32];
        if (lastNtpSync == 0) {
            strlcpy(lastSync, "never", sizeof(lastSync));
        } else {
            uint32_t ago = (millis() - lastNtpSync) / 1000;
            snprintf(lastSync, sizeof(lastSync), "%lus ago", static_cast<unsigned long>(ago));
        }

        char wifiBuf[48];
        if (WiFi.status() == WL_CONNECTED) {
            snprintf(wifiBuf, sizeof(wifiBuf), "connected (%s)", WiFi.SSID().c_str());
        } else if (portal) {
            strlcpy(wifiBuf, "config portal", sizeof(wifiBuf));
        } else {
            strlcpy(wifiBuf, "disconnected", sizeof(wifiBuf));
        }

        char powerBuf[48];
        if (powermonitor::present() && powermonitor::sample()) {
            snprintf(powerBuf, sizeof(powerBuf), "%.2f V, %.0f mA, %.1f W",
                     powermonitor::busVoltage(),
                     powermonitor::currentMilliAmps(),
                     powermonitor::powerMilliWatts() / 1000.0f);
        } else {
            strlcpy(powerBuf, "not found", sizeof(powerBuf));
        }

        char uptimeBuf[24];
        uint32_t up = millis() / 1000;
        snprintf(uptimeBuf, sizeof(uptimeBuf), "%luh%02lum",
                 static_cast<unsigned long>(up / 3600),
                 static_cast<unsigned long>((up % 3600) / 60));

        char json[1024];
        snprintf(json, sizeof(json),
                 "{\"portal\":%s,\"authed\":%s,"
                 "\"time\":\"%s\",\"date\":\"%s\",\"timeSource\":\"%s\","
                 "\"lastNtpSync\":\"%s\",\"wifi\":\"%s\",\"rssi\":%d,"
                 "\"ip\":\"%s\",\"hostname\":\"%s\",\"firmware\":\"%s %s\","
                 "\"uptime\":\"%s\",\"freeHeap\":%u,\"brightness\":%u,"
                 "\"rtc\":\"%s\",\"power\":\"%s\"}",
                 portal ? "true" : "false",
                 authorized() ? "true" : "false",
                 timeBuf, dateBuf, timeSource,
                 lastSync, wifiBuf, WiFi.status() == WL_CONNECTED ? WiFi.RSSI() : 0,
                 (portal ? WiFi.softAPIP() : WiFi.localIP()).toString().c_str(),
                 configstore::config.hostname,
                 __DATE__, __TIME__,
                 uptimeBuf, ESP.getFreeHeap(), configstore::config.brightness,
                 rtcPresent ? "present" : "not found",
                 powerBuf);

        server.send(200, "application/json", json);
    }

    void handleLogin() {
        if (portal) {
            server.send(200, "application/json", "{\"ok\":true}");
            return;
        }

        String body = server.arg("plain");
        char password[65] = "";
        jsonGetString(body.c_str(), "password", password, sizeof(password));

        if (password[0] == '\0' ||
            strcmp(password, configstore::config.adminPassword) != 0) {
            server.send(401, "application/json", "{\"error\":\"wrong password\"}");
            return;
        }

        // Fresh random session token.
        for (uint8_t i = 0; i < 32; i++) {
            sessionToken[i] = "0123456789abcdef"[ESP.random() & 0xF];
        }
        sessionToken[32] = '\0';
        sessionExpiry = millis() + SESSION_TTL_MS;

        String cookie = "lsck=" + String(sessionToken) +
                        "; Path=/; HttpOnly; Max-Age=3600";
        server.sendHeader("Set-Cookie", cookie);
        server.send(200, "application/json", "{\"ok\":true}");
    }

    void handleLogout() {
        sessionToken[0] = '\0';
        sessionExpiry = 0;
        server.sendHeader("Set-Cookie", "lsck=; Path=/; Max-Age=0");
        server.send(200, "application/json", "{\"ok\":true}");
    }

    void handleConfigGet() {
        if (!requireAuth()) {
            return;
        }

        const auto &cfg = configstore::config;
        char json[1024];
        snprintf(json, sizeof(json),
                 "{\"ssid\":\"%s\",\"wifiPasswordSet\":%s,"
                 "\"ntpServer\":\"%s\",\"timezone\":\"%s\","
                 "\"hostname\":\"%s\",\"brightness\":%u}",
                 cfg.ssid,
                 cfg.wifiPassword[0] != '\0' ? "true" : "false",
                 cfg.ntpServer, cfg.timezone, cfg.hostname, cfg.brightness);
        server.send(200, "application/json", json);
    }

    void handleConfigPost() {
        if (!requireAuth()) {
            return;
        }

        String body = server.arg("plain");
        const char *b = body.c_str();

        auto &cfg = configstore::config;

        char buf[65];
        if (jsonGetString(b, "ssid", buf, sizeof(buf))) {
            strlcpy(cfg.ssid, buf, sizeof(cfg.ssid));
        }
        if (jsonGetString(b, "wifiPassword", buf, sizeof(buf)) && buf[0] != '\0') {
            strlcpy(cfg.wifiPassword, buf, sizeof(cfg.wifiPassword));
        }
        if (jsonGetString(b, "ntpServer", buf, sizeof(buf)) && buf[0] != '\0') {
            strlcpy(cfg.ntpServer, buf, sizeof(cfg.ntpServer));
        }
        if (jsonGetString(b, "timezone", buf, sizeof(buf)) && buf[0] != '\0') {
            strlcpy(cfg.timezone, buf, sizeof(cfg.timezone));
        }
        if (jsonGetString(b, "hostname", buf, sizeof(buf)) && buf[0] != '\0') {
            strlcpy(cfg.hostname, buf, sizeof(cfg.hostname));
        }
        if (jsonGetString(b, "adminPassword", buf, sizeof(buf)) && buf[0] != '\0') {
            // Changing the password invalidates the active session.
            strlcpy(cfg.adminPassword, buf, sizeof(cfg.adminPassword));
            sessionToken[0] = '\0';
            sessionExpiry = 0;
        }
        long brightness;
        if (jsonGetNumber(b, "brightness", brightness)) {
            cfg.brightness = configstore::clampBrightness(brightness);
        }

        if (!configstore::save()) {
            server.send(500, "application/json", "{\"error\":\"eeprom write failed\"}");
            return;
        }

        server.send(200, "application/json", "{\"ok\":true}");
        // Reboot so WiFi, NTP and hostname come up with the new config.
        delay(500);
        ESP.restart();
    }

    void handleOtaUpload() {
        HTTPUpload &upload = server.upload();

        if (upload.status == UPLOAD_FILE_START) {
            if (!requireAuth()) {
                return;
            }
            Serial.println(F("OTA: start"));
            uint32_t maxSketchSpace = (ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000;
            if (!Update.begin(maxSketchSpace, U_FLASH)) {
                Serial.printf_P(PSTR("OTA: Update.begin failed: %s\n"), Update.getErrorString());
            }
            Update.runAsync(true);
        } else if (upload.status == UPLOAD_FILE_WRITE && Update.isRunning()) {
            if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
                Serial.printf_P(PSTR("OTA: Update.write failed: %s\n"), Update.getErrorString());
            }
        } else if (upload.status == UPLOAD_FILE_END && Update.isRunning()) {
            if (Update.end(true)) {
                Serial.printf_P(PSTR("OTA: success, %u bytes\n"), Update.progress());
            } else {
                Serial.printf_P(PSTR("OTA: Update.end failed: %s\n"), Update.getErrorString());
            }
        } else if (upload.status == UPLOAD_FILE_ABORTED) {
            Update.end();
            Serial.println(F("OTA: aborted"));
        }
    }

    void handleOtaPost() {
        if (!requireAuth()) {
            return;
        }

        if (Update.hasError()) {
            server.send(500, "text/plain", "Firmware update failed");
            return;
        }

        server.send(200, "text/plain", "Firmware upload success, rebooting...");
        delay(500);
        ESP.restart();
    }

    void handleNotFound() {
        if (portal) {
            // Captive portal: redirect everything to the root page.
            server.sendHeader("Location", "http://" + WiFi.softAPIP().toString() + "/", true);
            server.send(302, "text/plain", "");
        } else {
            server.send(404, "text/plain", "Not found");
        }
    }

    // ------------------------------------------------------------------
    // AP config portal fallback
    // ------------------------------------------------------------------

    void beginPortal() {
        if (portal) {
            return;
        }

        char apName[48];
        snprintf(apName, sizeof(apName), "%s-portal", configstore::config.hostname);

        Serial.printf_P(PSTR("Starting config portal AP '%s'\n"), apName);
        WiFi.disconnect(false);
        WiFi.mode(WIFI_AP);
        WiFi.softAP(apName);

        dnsServer = new DNSServer();
        dnsServer->start(53, "*", WiFi.softAPIP());

        portal = true;
        Serial.printf_P(PSTR("Portal started at http://%s/\n"),
                        WiFi.softAPIP().toString().c_str());
    }

    void endPortal() {
        if (!portal) {
            return;
        }

        portal = false;
        if (dnsServer != nullptr) {
            dnsServer->stop();
            delete dnsServer;
            dnsServer = nullptr;
        }
        WiFi.softAPdisconnect(true);
        WiFi.mode(WIFI_STA);
        Serial.println(F("Portal stopped"));
    }

    // ------------------------------------------------------------------
    // Setup / loop
    // ------------------------------------------------------------------

    static const char TAG[] = "http";

    void setup() {
        LOGI(TAG, "setup: registering routes");
        server.on("/", HTTP_GET, handleRoot);
        server.on("/api/status", HTTP_GET, handleStatus);
        server.on("/api/login", HTTP_POST, handleLogin);
        server.on("/api/logout", HTTP_POST, handleLogout);
        server.on("/api/config", HTTP_GET, handleConfigGet);
        server.on("/api/config", HTTP_POST, handleConfigPost);
        server.on("/api/ota", HTTP_POST, handleOtaPost, handleOtaUpload);
        server.onNotFound(handleNotFound);
        // Needed so server.header("Cookie") works for session validation.
        server.collectHeaders(F("Cookie"));
        LOGI(TAG, "setup: server.begin");
        server.begin();
        LOGI(TAG, "setup: done");
    }

    void loop() {
        if (portal) {
            dnsServer->processNextRequest();
        } else if (WiFi.status() != WL_CONNECTED) {
            if (staDisconnectedSince == 0) {
                staDisconnectedSince = millis();
            } else if (millis() - staDisconnectedSince > PORTAL_FALLBACK_DELAY_MS) {
                beginPortal();
                staDisconnectedSince = 0;
            }
        } else {
            staDisconnectedSince = 0;
            endPortal();
        }

        server.handleClient();
    }
}
