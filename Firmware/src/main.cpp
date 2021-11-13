/*

Copyright 2021 Marc Ketel
SPDX-License-Identifier: Apache-2.0

*/

#include <sys/time.h>

#include <Arduino.h>

#include <Wire.h>

#include <coredecls.h>
#include <time.h>
#include <TZ.h>

#include "config.h"
#include "wific.h"

void time_is_set(bool from_sntp)
{
    Serial.println("The NTP server was called!");
}

uint32_t sntp_update_delay_MS_rfc_not_less_than_15000 ()
{
  return 24 * 60 * 60 * 1000UL; // 24 hours
}

void setup()
{
    Wire.begin(SDA, SCL);

    Serial.begin(115200);
    Serial.println(F("Booting"));

    settimeofday_cb(time_is_set);
    configTime(TIMEZONE, NTP_SERVER);

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

    WificSetup();
}

const char digits[] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111  // 9
};

void loop()
{
    static uint32_t timer = 0;

    int16_t remainingms = 0;

    if (timer <= millis())
    {
        time_t now;
        time(&now);

        struct timeval tv;
        gettimeofday(&tv, NULL);

        int16_t milliseconds = tv.tv_usec / 1000;

        remainingms = 1000 - milliseconds;
        if (remainingms == 0)
            remainingms = 1000;

        timer = millis() + remainingms;

        tm timeInfo;
        localtime_r(&now, &timeInfo);

        digitalWrite(PIN_SHIFT_LATCH, LOW);

        for (uint8_t i = 0; i < 6; i++)
        {
            uint8_t d = 0;

            if (i == 5)
                d = (timeInfo.tm_hour / 10U) % 10;

            if (i == 4)
                d = (timeInfo.tm_hour / 1U) % 10;

            if (i == 3)
                d = (timeInfo.tm_min / 10U) % 10;

            if (i == 2)
                d = (timeInfo.tm_min / 1U) % 10;

            if (i == 1)
                d = (timeInfo.tm_sec / 10U) % 10;

            if (i == 0)
                d = (timeInfo.tm_sec / 1U) % 10;

            shiftOut(PIN_SHIFT_DATA, PIN_SHIFT_CLOCK, MSBFIRST, digits[d]);
        }

        digitalWrite(PIN_SHIFT_LATCH, HIGH);

        static uint8_t single = 0;
        if (single == 0)
        {
            Serial.println("Setting brightness");
            single = 1;
            analogWrite(PIN_SHIFT_NOT_OUTPUT_ENABLE, 950);
        }

        Serial.print(timeInfo.tm_year + 1900);
        Serial.print(F("-"));
        Serial.print(timeInfo.tm_mon);
        Serial.print(F("-"));
        Serial.print(timeInfo.tm_mday);
        Serial.print(F(" "));
        Serial.print(timeInfo.tm_hour);
        Serial.print(F(":"));
        Serial.print(timeInfo.tm_min);
        Serial.print(F(":"));
        Serial.print(timeInfo.tm_sec);
        Serial.print(F("."));
        Serial.print(milliseconds);
        Serial.println();
    }

    WiFicLoop();
}