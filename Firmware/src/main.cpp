/**
 * @file main.cpp
 * @brief LED strip clock firmware entry point
 *
 * @copyright Marc Ketel
 * SPDX-License-Identifier: Apache-2.0
 */

#include <sys/time.h>

#include <Arduino.h>

#include <Wire.h>

#include <coredecls.h>
#include <time.h>

#include "ConfigStore.h"
#include "Display.h"
#include "Log.h"
#include "Pins.h"
#include "PowerMonitor.h"
#include "RotaryService.h"
#include "RtcService.h"
#include "SerialCliCommands.h"
#include "WebServerService.h"
#include "WiFiService.h"
#include "utils/SerialCli.h"

void time_is_set(bool from_sntp) {
    Serial.println(F("The NTP server was called!"));
    webserver::noteNtpSync();
    rtc::syncFromSystem();
}

uint32_t sntp_update_delay_MS_rfc_not_less_than_15000() {
    return 24 * 60 * 60 * 1000UL; // 24 hours
}

static cli::SerialCli serialCli([](const char *data, size_t len) {
    Serial.write(data, len);
});

static const char TAG[] = "main";

// Display modes: the message modes take over the display completely.
enum class DisplayMode : uint8_t {
    Time,
    Save,
    Ap,
    Brightness
};

static DisplayMode displayMode = DisplayMode::Time;
static uint32_t displayModeUntil = 0;
// Next display refresh deadline; shared with showBrightness() so it can
// force an immediate redraw.
static uint32_t displayTimer = 0;

static void showSave() {
    displayMode = DisplayMode::Save;
    displayModeUntil = millis() + 2000;
}

static void showBrightness() {
    displayMode = DisplayMode::Brightness;
    displayModeUntil = millis() + 2000;
    // Force an immediate redraw instead of waiting for the next
    // second boundary, so the percentage updates live while turning.
    displayTimer = 0;
}

static void applyBrightness() {
    analogWrite(PIN_SHIFT_NOT_OUTPUT_ENABLE,
                configstore::pwmFromBrightness(configstore::config.brightness));
}

static void handleRotaryEvent(rotary::Event event) {
    if (cli::inputDebugEnabled()) {
        const char *name = nullptr;
        switch (event) {
            case rotary::Event::Cw:
                name = "CW";
                break;
            case rotary::Event::Ccw:
                name = "CCW";
                break;
            case rotary::Event::Press:
                name = "press";
                break;
            case rotary::Event::Release:
                name = "release";
                break;
            case rotary::Event::LongPress:
                name = "long press";
                break;
            default:
                return;
        }
        LOGI(TAG, "Encoder %s", name);
    }

    switch (event) {
        case rotary::Event::Cw:
        case rotary::Event::Ccw:
            if (webserver::portalActive()) {
                return; // no brightness control while the AP is open
            }
            if (event == rotary::Event::Cw) {
                configstore::config.brightness =
                    configstore::clampBrightness(configstore::config.brightness + 1L);
            } else {
                configstore::config.brightness =
                    configstore::clampBrightness(configstore::config.brightness - 1L);
            }
            applyBrightness();
            showBrightness();
            break;

        case rotary::Event::Press:
            if (webserver::portalActive()) {
                return;
            }
            if (configstore::save()) {
                showSave();
            }
            break;

        case rotary::Event::LongPress:
            if (webserver::portalActive()) {
                webserver::endPortal();
            } else {
                webserver::beginPortal();
                displayMode = DisplayMode::Ap;
            }
            break;

        default:
            break;
    }
}

void setup() {
    Serial.begin(115200);
    delay(100);
    LOGI(TAG, "Booting");

    LOGI(TAG, "Wire.begin");
    Wire.begin(SDA, SCL);

    LOGI(TAG, "rtc::begin");
    rtc::begin();
    LOGI(TAG, "rtc::begin done");

    LOGI(TAG, "configstore::begin");
    configstore::begin();
    LOGI(TAG, "configstore::begin done");

    LOGI(TAG, "configTime tz=%s ntp=%s", configstore::config.timezone,
         configstore::config.ntpServer);
    settimeofday_cb(time_is_set);
    configTime(configstore::config.timezone, configstore::config.ntpServer);
    LOGI(TAG, "configTime done");

    LOGI(TAG, "pin setup");
    digitalWrite(PIN_BUFFER_NOT_ENABLE, LOW);
    pinMode(PIN_BUFFER_NOT_ENABLE, OUTPUT);

    digitalWrite(PIN_SHIFT_NOT_OUTPUT_ENABLE, HIGH);
    pinMode(PIN_SHIFT_NOT_OUTPUT_ENABLE, OUTPUT);
    analogWriteRange(1023);
    analogWriteFreq(2000);
    delay(500);

    pinMode(PIN_SHIFT_LATCH, OUTPUT);
    pinMode(PIN_SHIFT_CLOCK, OUTPUT);
    pinMode(PIN_SHIFT_DATA, OUTPUT);
    applyBrightness();
    LOGI(TAG, "pin setup done");

    LOGI(TAG, "powermonitor::begin");
    powermonitor::begin();
    LOGI(TAG, "powermonitor::begin done");

    LOGI(TAG, "rotary::begin");
    rotary::begin(handleRotaryEvent);
    LOGI(TAG, "rotary::begin done");

    LOGI(TAG, "wifi::setup");
    wifi::setup();
    LOGI(TAG, "wifi::setup done");

    LOGI(TAG, "webserver::setup");
    webserver::setup();
    LOGI(TAG, "webserver::setup done");

    cli::registerCommands(serialCli);
    LOGI(TAG, "setup complete, free heap=%u", ESP.getFreeHeap());
}

void loop() {
    uint32_t &timer = displayTimer;

    int16_t remainingms = 0;

    if (timer <= millis()) {
        time_t now;
        time(&now);

        struct timeval tv;
        gettimeofday(&tv, NULL);

        int16_t milliseconds = tv.tv_usec / 1000;

        remainingms = 1000 - milliseconds;
        if (remainingms == 0) {
            remainingms = 1000;
        }

        timer = millis() + remainingms;

        tm timeInfo;
        localtime_r(&now, &timeInfo);

        uint8_t patterns[display::kDigitCount];
        if (displayMode == DisplayMode::Ap) {
            display::textPatterns(patterns, "_AP_");
        } else if (displayMode == DisplayMode::Save) {
            display::textPatterns(patterns, "SAVE");
        } else if (displayMode == DisplayMode::Brightness) {
            // Percentage centered on the HHMM positions, seconds blank.
            // Build the padded text first: calling textPatterns() on
            // patterns + pad would blank kDigitCount entries and run one
            // byte past the end of the patterns array.
            char text[5];
            snprintf(text, sizeof(text), "%u", configstore::config.brightness);
            char padded[display::kDigitCount + 1] = "      ";
            const uint8_t len = static_cast<uint8_t>(strlen(text));
            const uint8_t pad = (4 - len) / 2;
            memcpy(padded + pad, text, len);
            display::textPatterns(patterns, padded);
        } else {
            display::timePatterns(patterns, timeInfo);
        }

        digitalWrite(PIN_SHIFT_LATCH, LOW);
        display::write(patterns);
        digitalWrite(PIN_SHIFT_LATCH, HIGH);
    }

    // Return from temporary display modes.
    if (displayMode != DisplayMode::Time && millis() > displayModeUntil) {
        displayMode = DisplayMode::Time;
    }
    // Leave AP mode when the portal closes (e.g. saved via web interface).
    if (displayMode == DisplayMode::Ap && !webserver::portalActive()) {
        displayMode = DisplayMode::Time;
    }

    while (Serial.available()) {
        serialCli.feed(Serial.read());
    }

    rotary::loop();

    wifi::loop();
    webserver::loop();
}
