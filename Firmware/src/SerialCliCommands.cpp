/**
 * @file SerialCliCommands.cpp
 * @brief Serial CLI commands for the LED strip clock
 *
 * @copyright Marc Ketel
 * SPDX-License-Identifier: Apache-2.0
 */

#include "SerialCliCommands.h"

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <LittleFS.h>
#include <time.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "ConfigStore.h"
#include "Pins.h"
#include "PowerMonitor.h"
#include "RtcService.h"
#include "WebServerService.h"
#include "WiFiService.h"

namespace cli {
    namespace {
        bool g_inputDebugEnabled = false;

        void print(const char *text) {
            Serial.print(text);
            Serial.print("\r\n");
        }

        void cmdStatus(int argc, char **argv) {
            (void)argc;
            (void)argv;

            char line[160];

            time_t now = time(nullptr);
            struct tm timeinfo;
            localtime_r(&now, &timeinfo);
            bool timeValid = timeinfo.tm_year > (2020 - 1900);

            snprintf(line, sizeof(line), "hostname: %s",
                     configstore::config.hostname);
            print(line);

            snprintf(line, sizeof(line), "wifi: %s",
                     WiFi.status() == WL_CONNECTED ? "connected" : "disconnected");
            print(line);

            if (WiFi.status() == WL_CONNECTED) {
                snprintf(line, sizeof(line), "ip: %s",
                         WiFi.localIP().toString().c_str());
                print(line);
                snprintf(line, sizeof(line), "rssi: %d", WiFi.RSSI());
                print(line);
            }

            snprintf(line, sizeof(line), "portal: %s",
                     webserver::portalActive() ? "running" : "stopped");
            print(line);

            if (timeValid) {
                char tbuf[32];
                strftime(tbuf, sizeof(tbuf), "%Y-%m-%d %H:%M:%S", &timeinfo);
                snprintf(line, sizeof(line), "time: %s", tbuf);
            } else {
                snprintf(line, sizeof(line), "time: not synchronised");
            }
            print(line);

            snprintf(line, sizeof(line), "config: %s",
                     configstore::usingDefaults() ? "defaults" : "stored");
            print(line);
        }

        void cmdReboot(int argc, char **argv) {
            (void)argc;
            (void)argv;
            print("Rebooting...");
            delay(100);
            ESP.restart();
        }

        void cmdFactoryReset(int argc, char **argv) {
            if (argc < 2 || strcmp(argv[1], "confirm") != 0) {
                print("WARNING: erases the stored configuration (WiFi credentials).");
                print("Run 'factoryreset confirm' to proceed.");
                return;
            }
            print("Erasing config and rebooting...");
            LittleFS.remove("/config.json");
            delay(100);
            ESP.restart();
        }

        void cmdPortal(int argc, char **argv) {
            if (argc < 2) {
                print("usage: portal on|off");
                return;
            }
            if (strcmp(argv[1], "on") == 0) {
                if (webserver::portalActive()) {
                    print("Portal already running.");
                    return;
                }
                webserver::beginPortal();
                print("Portal started.");
            } else if (strcmp(argv[1], "off") == 0) {
                if (!webserver::portalActive()) {
                    print("Portal not running.");
                    return;
                }
                webserver::endPortal();
                print("Portal stopped.");
            } else {
                print("usage: portal on|off");
            }
        }

        void cmdWifi(int argc, char **argv) {
            if (argc < 2 || strcmp(argv[1], "status") == 0) {
                char line[128];

                snprintf(line, sizeof(line), "wifi: %s",
                         WiFi.status() == WL_CONNECTED ? "connected" : "disconnected");
                print(line);

                if (WiFi.status() == WL_CONNECTED) {
                    snprintf(line, sizeof(line), "sta: ssid='%s', channel=%d, rssi=%d",
                             WiFi.SSID().c_str(), WiFi.channel(), WiFi.RSSI());
                    print(line);
                    snprintf(line, sizeof(line), "ip: %s",
                             WiFi.localIP().toString().c_str());
                    print(line);
                }
                return;
            }

            if (strcmp(argv[1], "scan") == 0) {
                print("scanning...");
                int n = WiFi.scanNetworks();
                char line[96];
                snprintf(line, sizeof(line), "found %d networks", n);
                print(line);
                for (int i = 0; i < n; i++) {
                    snprintf(line, sizeof(line), "  [%d] '%s' ch=%d rssi=%d%s",
                             i, WiFi.SSID(i).c_str(), WiFi.channel(i), WiFi.RSSI(i),
                             WiFi.encryptionType(i) == ENC_TYPE_NONE ? " (open)" : "");
                    print(line);
                }
                WiFi.scanDelete();
                return;
            }

            if (strcmp(argv[1], "disconnect") == 0) {
                WiFi.disconnect(false);
                print("disconnected");
                return;
            }

            print("usage: wifi status|scan|disconnect");
        }

        void cmdInfo(int argc, char **argv) {
            (void)argc;
            (void)argv;

            char line[128];

            snprintf(line, sizeof(line), "app: ledstripclock");
            print(line);

            snprintf(line, sizeof(line), "build: %s %s", __DATE__, __TIME__);
            print(line);

            snprintf(line, sizeof(line), "sdk: %s", ESP.getSdkVersion());
            print(line);

            snprintf(line, sizeof(line), "core: %s", ESP.getCoreVersion().c_str());
            print(line);

            snprintf(line, sizeof(line), "reset reason: %s",
                     ESP.getResetReason().c_str());
            print(line);
        }

        void cmdHeap(int argc, char **argv) {
            (void)argc;
            (void)argv;

            char line[96];

            snprintf(line, sizeof(line), "free heap: %u", ESP.getFreeHeap());
            print(line);

            snprintf(line, sizeof(line), "fragmentation: %u%%",
                     ESP.getHeapFragmentation());
            print(line);

            snprintf(line, sizeof(line), "max free block: %u",
                     ESP.getMaxFreeBlockSize());
            print(line);
        }

        void cmdBrightness(int argc, char **argv) {
            if (argc < 2) {
                char line[64];
                snprintf(line, sizeof(line), "brightness: %u%%",
                         configstore::config.brightness);
                print(line);
                print("usage: brightness <0-100> [save]");
                return;
            }

            long value = atol(argv[1]);
            if (value < 0 || value > 100) {
                print("value out of range (0-100)");
                return;
            }

            configstore::config.brightness = configstore::clampBrightness(value);
            analogWrite(PIN_SHIFT_NOT_OUTPUT_ENABLE,
                        configstore::pwmFromBrightness(configstore::config.brightness));

            if (argc >= 3 && strcmp(argv[2], "save") == 0) {
                if (configstore::save()) {
                    print("ok: saved");
                } else {
                    print("error: save failed");
                }
            } else {
                print("ok (not saved, use 'brightness <v> save' to persist)");
            }
        }

        void cmdConfig(int argc, char **argv) {
            if (argc < 2) {
                char line[128];

                snprintf(line, sizeof(line), "ssid: '%s'", configstore::config.ssid);
                print(line);
                snprintf(line, sizeof(line), "ntpServer: %s", configstore::config.ntpServer);
                print(line);
                snprintf(line, sizeof(line), "timezone: %s", configstore::config.timezone);
                print(line);
                snprintf(line, sizeof(line), "hostname: %s", configstore::config.hostname);
                print(line);
                snprintf(line, sizeof(line), "brightness: %u", configstore::config.brightness);
                print(line);
                return;
            }

            if (strcmp(argv[1], "set") != 0 || argc < 4) {
                print("usage: config | config set <key> <value>");
                print("keys: ssid, ntpServer, timezone, hostname");
                return;
            }

            const char *key = argv[2];
            const char *value = argv[3];
            bool ok = false;

            if (strcmp(key, "ssid") == 0) {
                strlcpy(configstore::config.ssid, value, sizeof(configstore::config.ssid));
                ok = true;
            } else if (strcmp(key, "ntpServer") == 0) {
                strlcpy(configstore::config.ntpServer, value, sizeof(configstore::config.ntpServer));
                ok = true;
            } else if (strcmp(key, "timezone") == 0) {
                strlcpy(configstore::config.timezone, value, sizeof(configstore::config.timezone));
                ok = true;
            } else if (strcmp(key, "hostname") == 0) {
                strlcpy(configstore::config.hostname, value, sizeof(configstore::config.hostname));
                ok = true;
            }

            if (!ok) {
                print("unknown key");
                return;
            }

            if (configstore::save()) {
                print("ok: saved (reboot to apply)");
            } else {
                print("error: save failed");
            }
        }

        void cmdNtp(int argc, char **argv) {
            (void)argc;
            (void)argv;

            time_t now = time(nullptr);
            struct tm timeinfo;
            localtime_r(&now, &timeinfo);

            char line[96];
            if (timeinfo.tm_year > (2020 - 1900)) {
                char tbuf[32];
                strftime(tbuf, sizeof(tbuf), "%Y-%m-%d %H:%M:%S", &timeinfo);
                snprintf(line, sizeof(line), "time: %s", tbuf);
            } else {
                snprintf(line, sizeof(line), "time: not synchronised");
            }
            print(line);

            snprintf(line, sizeof(line), "ntpServer: %s", configstore::config.ntpServer);
            print(line);

            snprintf(line, sizeof(line), "timezone: %s", configstore::config.timezone);
            print(line);

            print("forcing resync...");
            configTime(configstore::config.timezone, configstore::config.ntpServer);
        }

        void cmdPower(int argc, char **argv) {
            (void)argc;
            (void)argv;

            if (!powermonitor::present()) {
                print("power: INA219 not found");
                return;
            }

            if (!powermonitor::sample()) {
                print("power: read failed");
                return;
            }

            char line[96];
            snprintf(line, sizeof(line), "bus: %.3f V", powermonitor::busVoltage());
            print(line);
            snprintf(line, sizeof(line), "current: %.1f mA", powermonitor::currentMilliAmps());
            print(line);
            snprintf(line, sizeof(line), "power: %.1f mW", powermonitor::powerMilliWatts());
            print(line);
        }

        void cmdRtc(int argc, char **argv) {
            if (!rtc::present()) {
                print("rtc: DS3231 not found");
                return;
            }

            if (argc >= 2 && strcmp(argv[1], "set") == 0) {
                if (rtc::syncFromSystem()) {
                    print("rtc: updated from system clock");
                } else {
                    print("rtc: write failed");
                }
                return;
            }

            if (argc >= 2 && strcmp(argv[1], "temp") == 0) {
                char line[48];
                snprintf(line, sizeof(line), "temperature: %.2f C", rtc::temperature());
                print(line);
                return;
            }

            if (argc >= 2) {
                print("usage: rtc | rtc set | rtc temp");
                return;
            }

            struct tm rtcTm;
            char line[96];

            if (rtc::getTime(rtcTm)) {
                char tbuf[32];
                strftime(tbuf, sizeof(tbuf), "%Y-%m-%d %H:%M:%S", &rtcTm);
                snprintf(line, sizeof(line), "rtc time (UTC): %s", tbuf);
            } else {
                snprintf(line, sizeof(line), "rtc time: read failed");
            }
            print(line);

            time_t now = time(nullptr);
            struct tm sysTm;
            gmtime_r(&now, &sysTm);
            char sbuf[32];
            strftime(sbuf, sizeof(sbuf), "%Y-%m-%d %H:%M:%S", &sysTm);
            snprintf(line, sizeof(line), "system time (UTC): %s", sbuf);
            print(line);

            int32_t drift = rtc::driftSeconds();
            snprintf(line, sizeof(line), "drift (rtc - system): %ld s",
                     static_cast<long>(drift));
            print(line);

            snprintf(line, sizeof(line), "temperature: %.2f C", rtc::temperature());
            print(line);
        }

        void cmdInputDebug(int argc, char **argv) {
            if (argc < 2) {
                char line[48];
                snprintf(line, sizeof(line), "inputdebug: %s",
                         inputDebugEnabled() ? "on" : "off");
                print(line);
                return;
            }

            if (strcmp(argv[1], "on") == 0) {
                setInputDebugEnabled(true);
                print("inputdebug: on");
            } else if (strcmp(argv[1], "off") == 0) {
                setInputDebugEnabled(false);
                print("inputdebug: off");
            } else {
                print("usage: inputdebug on|off");
            }
        }

    } // namespace

    void setInputDebugEnabled(bool enabled) {
        g_inputDebugEnabled = enabled;
    }

    bool inputDebugEnabled() {
        return g_inputDebugEnabled;
    }

    void registerCommands(SerialCli &cli) {
        cli.registerCommand({"status", cmdStatus, "WiFi, portal and time status"});
        cli.registerCommand({"reboot", cmdReboot, "Reboot the device"});
        cli.registerCommand({"factoryreset", cmdFactoryReset, "Erase config and reboot (use 'factoryreset confirm')"});
        cli.registerCommand({"portal", cmdPortal, "Start/stop the config portal: portal on|off"});
        cli.registerCommand({"wifi", cmdWifi, "WiFi diagnostics: wifi status|scan|disconnect"});
        cli.registerCommand({"info", cmdInfo, "Firmware and build info"});
        cli.registerCommand({"heap", cmdHeap, "Free heap overview"});
        cli.registerCommand({"brightness", cmdBrightness, "Get/set display brightness in %: brightness [0-100] [save]"});
        cli.registerCommand({"config", cmdConfig, "Show/change config: config | config set <key> <value>"});
        cli.registerCommand({"ntp", cmdNtp, "Show time/NTP status and force resync"});
        cli.registerCommand({"power", cmdPower, "INA219 bus voltage, current and power"});
        cli.registerCommand({"rtc", cmdRtc, "DS3231 status: rtc | rtc set | rtc temp"});
        cli.registerCommand({"inputdebug", cmdInputDebug, "Toggle input event debug output: inputdebug on|off"});
    }

} // namespace cli
