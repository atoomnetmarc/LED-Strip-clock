#include <Arduino.h>

#define FASTLED_ESP8266_RAW_PIN_ORDER
#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 1

// For led chips like WS2812, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN
// Clock pin only needed for SPI based chipsets when not using hardware SPI
#define DATA_PIN 12
//#define CLOCK_PIN 13

// Define the array of leds
CRGB leds[NUM_LEDS];

const int dataPin = 13;
const int clockPin = 14;
const int latchPin = 15;

void setup()
{
    Serial.begin(115200);
    FastLED.addLeds<PL9823, DATA_PIN, RGB>(leds, NUM_LEDS);
    FastLED.setBrightness(5);
    digitalWrite(2, LOW);
    pinMode(2, OUTPUT);

    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
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
    leds[0] = CRGB::Red;
    FastLED.show();
    delay(333);
    leds[0] = CRGB::Green;
    FastLED.show();
    delay(333);
    leds[0] = CRGB::Blue;
    FastLED.show();
    delay(333);

    static uint8_t temp = 0;

    digitalWrite(latchPin, LOW);
    uint8_t d = digits[temp];
    if (temp % 3 == 0)
        d |= 0b10000000;
    shiftOut(dataPin, clockPin, MSBFIRST, d);
    digitalWrite(latchPin, HIGH);
    Serial.println(temp);

    temp++;
    if (temp > 9)
        temp = 0;
}