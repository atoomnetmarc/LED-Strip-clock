/**
 * @file Log.h
 * @brief Lightweight ESP_LOGI-style logging for ESP8266 Arduino
 *
 * @copyright Marc Ketel
 * SPDX-License-Identifier: Apache-2.0
 */

#pragma once

#include <Arduino.h>

#define LOGI(tag, fmt, ...) \
    Serial.printf_P(PSTR("[%8lu] I %s: " fmt "\r\n"), millis(), tag, ##__VA_ARGS__)
#define LOGW(tag, fmt, ...) \
    Serial.printf_P(PSTR("[%8lu] W %s: " fmt "\r\n"), millis(), tag, ##__VA_ARGS__)
#define LOGE(tag, fmt, ...) \
    Serial.printf_P(PSTR("[%8lu] E %s: " fmt "\r\n"), millis(), tag, ##__VA_ARGS__)
