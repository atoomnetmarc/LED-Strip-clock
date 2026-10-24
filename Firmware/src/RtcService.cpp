/**
 * @file RtcService.cpp
 * @brief DS3231 RTC support: boot time seeding and NTP write-back
 *
 * @copyright Marc Ketel
 * SPDX-License-Identifier: Apache-2.0
 */

#include "RtcService.h"

#include <sys/time.h>
#include <time.h>

#include <DS3232.h>

#include "Log.h"

static const char TAG[] = "rtc";

// DS3231MZ fixed I2C address.
static const uint8_t RTC_I2C_ADDRESS = 0x68;

static DS3231 rtcDevice(&Wire);
static bool rtcPresent = false;

// Convert a UTC struct tm to Unix epoch seconds without relying on the
// timezone environment (mktime() interprets struct tm as local time, and the
// ESP8266 core's configTime() timezone handling is not reliably switchable
// via setenv/tzset). Howard Hinnant's days_from_civil algorithm.
static time_t utcToEpoch(const struct tm &t) {
    int y = t.tm_year + 1900;
    int m = t.tm_mon + 1;
    int d = t.tm_mday;

    y -= m <= 2;
    int era = (y >= 0 ? y : y - 399) / 400;
    int yoe = y - era * 400;                                  // [0, 399]
    int doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1; // [0, 365]
    int doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;          // [0, 146096]
    int64_t days = static_cast<int64_t>(era) * 146097 + doe - 719468;

    return static_cast<time_t>(days * 86400LL +
                               t.tm_hour * 3600LL + t.tm_min * 60LL +
                               t.tm_sec);
}

namespace rtc {

    void begin() {
        if (rtcDevice.begin() != DS3232_OK || !rtcDevice.isConnected()) {
            LOGW(TAG, "DS3231 not found at 0x%02X", RTC_I2C_ADDRESS);
            rtcPresent = false;
            return;
        }
        rtcPresent = true;

        if (rtcDevice.read() != DS3232_OK) {
            LOGW(TAG, "DS3231 read failed");
            return;
        }

        // The year register holds 0-99; the DS3231 has no century register, so
        // assume 2000+ (valid until 2099).
        struct tm timeInfo = {};
        timeInfo.tm_sec = rtcDevice.seconds();
        timeInfo.tm_min = rtcDevice.minutes();
        timeInfo.tm_hour = rtcDevice.hours();
        timeInfo.tm_mday = rtcDevice.day();
        timeInfo.tm_mon = rtcDevice.month() - 1;
        timeInfo.tm_year = (rtcDevice.year() % 100) + 100; // 2000-based
        timeInfo.tm_isdst = -1;

        time_t rtcTime = utcToEpoch(timeInfo);
        struct timeval tv = {.tv_sec = rtcTime, .tv_usec = 0};
        settimeofday(&tv, nullptr);

        char timeBuf[32];
        strftime(timeBuf, sizeof(timeBuf), "%Y-%m-%d %H:%M:%S",
                 gmtime(&rtcTime));
        LOGI(TAG, "system clock seeded from RTC (UTC): %s", timeBuf);
    }

    bool present() {
        return rtcPresent;
    }

    bool getTime(struct tm &out) {
        if (!rtcPresent || rtcDevice.read() != DS3232_OK) {
            return false;
        }

        out = {};
        out.tm_sec = rtcDevice.seconds();
        out.tm_min = rtcDevice.minutes();
        out.tm_hour = rtcDevice.hours();
        out.tm_mday = rtcDevice.day();
        out.tm_mon = rtcDevice.month() - 1;
        out.tm_year = (rtcDevice.year() % 100) + 100; // 2000-based
        out.tm_isdst = -1;
        return true;
    }

    int32_t driftSeconds() {
        struct tm rtcTm;
        if (!getTime(rtcTm)) {
            return 0;
        }

        time_t rtcTime = utcToEpoch(rtcTm);
        time_t now;
        time(&now);
        return static_cast<int32_t>(difftime(rtcTime, now));
    }

    float temperature() {
        if (!rtcPresent) {
            return 0.0f;
        }
        return rtcDevice.getTemperature();
    }

    bool syncFromSystem() {
        if (!rtcPresent) {
            return false;
        }

        time_t now;
        time(&now);
        struct tm timeInfo;
        gmtime_r(&now, &timeInfo);

        rtcDevice.setSeconds(timeInfo.tm_sec);
        rtcDevice.setMinutes(timeInfo.tm_min);
        rtcDevice.setHours(timeInfo.tm_hour);
        rtcDevice.setDay(timeInfo.tm_mday);
        rtcDevice.setMonth(timeInfo.tm_mon + 1);
        rtcDevice.setYear(timeInfo.tm_year % 100);

        if (rtcDevice.write() != DS3232_OK) {
            LOGW(TAG, "write-back to DS3231 failed");
            return false;
        }
        LOGI(TAG, "RTC updated from NTP-synced system clock");
        return true;
    }

}
