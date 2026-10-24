/**
 * @file WiFiService.cpp
 * @brief WiFi connection manager
 *
 * @copyright Marc Ketel
 * SPDX-License-Identifier: Apache-2.0
 */

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

#include "ConfigStore.h"
#include "Log.h"
#include "WebServerService.h"

namespace wifi {

static WiFiEventHandler stationModeGotIPHandler;
static WiFiEventHandler stationModeDisconnectedHandler;

static void onStationModeGotIP(const WiFiEventStationModeGotIP &evt) {
    Serial.print(F("IP address: "));
    Serial.println(WiFi.localIP());

    MDNS.begin(configstore::config.hostname);
}

static void onStationModeDisconnected(const WiFiEventStationModeDisconnected &evt) {
    Serial.println(F("WiFi got disconnected."));
}

static const char TAG[] = "wifi";

void setup() {
    LOGI(TAG, "setup: registering handlers");
    stationModeGotIPHandler = WiFi.onStationModeGotIP(&onStationModeGotIP);
    stationModeDisconnectedHandler = WiFi.onStationModeDisconnected(&onStationModeDisconnected);

    LOGI(TAG, "setup: mode STA, hostname=%s", configstore::config.hostname);
    WiFi.mode(WIFI_STA);
    WiFi.hostname(configstore::config.hostname);
    WiFi.setPhyMode(WIFI_PHY_MODE_11N);
    WiFi.setSleepMode(WIFI_NONE_SLEEP);
    LOGI(TAG, "setup: WiFi.begin ssid=%s", configstore::config.ssid);
    WiFi.begin(configstore::config.ssid, configstore::config.wifiPassword);
    LOGI(TAG, "setup: done");
}

void loop() {
    MDNS.update();
}

} // namespace wifi
