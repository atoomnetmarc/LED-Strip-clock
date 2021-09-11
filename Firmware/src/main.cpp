#include <Arduino.h>

const int dataPin = 13;
const int clockPin = 14;
const int latchPin = 15;

void setup()
{
    digitalWrite(16, LOW);
    pinMode(16, OUTPUT);

    digitalWrite(2, HIGH);
    pinMode(2, OUTPUT);
    delay(500);

    Serial.begin(115200);
    Serial.println("Hello");

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
    delay(500);

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

    static uint8_t single = 0;
    if (single == 0)
    {
        single = 1;
        analogWrite(2, 1000);
    }
}