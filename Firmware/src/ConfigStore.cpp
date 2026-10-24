/**
 * @file ConfigStore.cpp
 * @brief JSON configuration store on LittleFS
 *
 * @copyright Marc Ketel
 * SPDX-License-Identifier: Apache-2.0
 */

#include <TZ.h>

#include "ConfigStore.h"
#include "Log.h"

#include <ArduinoJson.h>
#include <LittleFS.h>

namespace configstore {
    Config config;

    static bool defaultsInUse = true;

    static constexpr const char *CONFIG_PATH = "/config.json";
    static constexpr const char *CONFIG_TMP_PATH = "/config.json.tmp";

    // Hard-coded first-boot defaults; everything is configurable via the
    // web UI afterwards (stored in /config.json on LittleFS).
    static const char TAG[] = "cfg";

    static void loadDefaults() {
        LOGI(TAG, "loadDefaults: memset");
        memset(&config, 0, sizeof(config));
        config.brightness = 20;
        LOGI(TAG, "loadDefaults: ssid/pw");
        strlcpy(config.ssid, "", sizeof(config.ssid));
        strlcpy(config.wifiPassword, "", sizeof(config.wifiPassword));
        LOGI(TAG, "loadDefaults: ntpServer");
        strlcpy(config.ntpServer, "pool.ntp.org", sizeof(config.ntpServer));
        // TZ_Europe_Amsterdam is a PSTR (flash address); plain strlcpy reads it
        // byte-wise (l8ui) which raises Exception 3 on ESP8266. Copy with
        // pgm_read_byte instead.
        {
            const char *tz = TZ_Europe_Amsterdam;
            size_t i = 0;
            while (i < sizeof(config.timezone) - 1 &&
                   (config.timezone[i] = (char)pgm_read_byte(&tz[i])) != '\0') {
                i++;
            }
            config.timezone[i] = '\0';
        }
        LOGI(TAG, "loadDefaults: timezone ok: %s", config.timezone);
        strlcpy(config.hostname, "ledstripclock", sizeof(config.hostname));
        strlcpy(config.adminPassword, "very secury ota password", sizeof(config.adminPassword));
        LOGI(TAG, "loadDefaults: done");
    }

    static void applyJson(const JsonDocument &doc) {
        long b = doc["brightness"] | config.brightness;
        if (b < 0) {
            b = 0;
        } else if (b > 100) {
            b = 100;
        }
        config.brightness = static_cast<uint8_t>(b);
        strlcpy(config.ssid, doc["ssid"] | "", sizeof(config.ssid));
        strlcpy(config.wifiPassword, doc["wifiPassword"] | "", sizeof(config.wifiPassword));
        strlcpy(config.ntpServer, doc["ntpServer"] | config.ntpServer, sizeof(config.ntpServer));
        strlcpy(config.timezone, doc["timezone"] | config.timezone, sizeof(config.timezone));
        strlcpy(config.hostname, doc["hostname"] | config.hostname, sizeof(config.hostname));
        strlcpy(config.adminPassword, doc["adminPassword"] | config.adminPassword, sizeof(config.adminPassword));
    }

    void begin() {
        LOGI(TAG, "begin: loadDefaults");
        loadDefaults();

        LOGI(TAG, "begin: LittleFS.begin");
        if (!LittleFS.begin()) {
            LOGW(TAG, "begin: LittleFS mount failed, formatting");
            LittleFS.format();
            LittleFS.begin();
        }
        LOGI(TAG, "begin: LittleFS ok");

        LOGI(TAG, "begin: open %s", CONFIG_PATH);
        File file = LittleFS.open(CONFIG_PATH, "r");
        if (file) {
            JsonDocument doc;
            DeserializationError error = deserializeJson(doc, file);
            file.close();

            if (error == DeserializationError::Ok) {
                LOGI(TAG, "begin: config parsed, applying");
                applyJson(doc);
                defaultsInUse = false;
                return;
            } else {
                LOGW(TAG, "begin: config parse error: %s", error.c_str());
            }
        } else {
            LOGI(TAG, "begin: no config file, using defaults");
        }

        // No valid config file: persist the defaults so the next boot
        // starts from a known-good record.
        LOGI(TAG, "begin: saving defaults");
        save();
        LOGI(TAG, "begin: save done");
    }

    bool save() {
        JsonDocument doc;
        doc["brightness"] = config.brightness;
        doc["ssid"] = config.ssid;
        doc["wifiPassword"] = config.wifiPassword;
        doc["ntpServer"] = config.ntpServer;
        doc["timezone"] = config.timezone;
        doc["hostname"] = config.hostname;
        doc["adminPassword"] = config.adminPassword;

        File file = LittleFS.open(CONFIG_TMP_PATH, "w");
        if (!file) {
            return false;
        }

        bool ok = serializeJson(doc, file) > 0;
        file.flush();
        file.close();

        if (!ok) {
            LittleFS.remove(CONFIG_TMP_PATH);
            return false;
        }

        LittleFS.remove(CONFIG_PATH);
        ok = LittleFS.rename(CONFIG_TMP_PATH, CONFIG_PATH);

        if (ok) {
            defaultsInUse = false;
        }
        return ok;
    }

    bool usingDefaults() {
        return defaultsInUse;
    }
}
