/*

Copyright 2021 Marc Ketel
SPDX-License-Identifier: Apache-2.0

*/

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>

#include "config.h"
#include "ota.h"


WiFiEventHandler stationModeGotIPHandler;
void onStationModeGotIP(const WiFiEventStationModeGotIP &evt)
{
    Serial.print(F("IP address: "));
    Serial.println(WiFi.localIP());

    OTASetup();
    //MqttOnWifiConnect();
    //WebserverOnWifiConnect();

    //event.Fire(EVENT_WIFI);
}

WiFiEventHandler stationModeConnectedHandler;
void onStationModeConnected(const WiFiEventStationModeConnected &evt)
{
    Serial.print(F("WiFi connected to: "));
    Serial.println(WiFi.SSID());
}

WiFiEventHandler stationModeDisconnectedHandler;
void onStationModeDisconnected(const WiFiEventStationModeDisconnected &evt)
{
    Serial.println(F("WiFi got disconnected."));
    //MqttOnWifiDisconnect();

    //event.Fire(EVENT_WIFI);
}

void WificSetup()
{
    stationModeGotIPHandler = WiFi.onStationModeGotIP(&onStationModeGotIP);
    stationModeConnectedHandler = WiFi.onStationModeConnected(&onStationModeConnected);
    stationModeDisconnectedHandler = WiFi.onStationModeDisconnected(&onStationModeDisconnected);

    WiFi.mode(WIFI_STA);
    WiFi.hostname(otahostname);
    WiFi.setPhyMode(WIFI_PHY_MODE_11N);
    WiFi.setSleepMode(WIFI_NONE_SLEEP);
    WiFi.begin(ssid, password);
}

void WiFicLoop()
{
    OTALoop();
}