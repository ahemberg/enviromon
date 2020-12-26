#pragma once

#include <Arduino.h>
#include "DateHolder.h"

//TODO These defines somewhere nice
#define MIN_TEMP -55.0
#define MAX_TEMP 125.0
#define MIN_HUMIDITY 0.0
#define MAX_HUMIDITY 100.0
#define MIN_BATT_V 2.5
#define MAX_BATT_V 4.5
#define MIN_SP_V 0.0
#define MAX_SP_V 12.0


/*
    Abstraction of measurement saved in memory
*/
class Measurement
{
private:
    uint8_t byteArray[7];
    DateHolder date;
    const float temperature;
    const float relativeHumidity;
    const float batteryVoltage;
    const float solarPanelVoltage;

public:
    Measurement(const DateHolder date,
                const float temperature,
                const float relativeHumidity,
                const float batteryVoltage,
                const float solarpanelVoltage);
    void getAsByteArray(uint8_t (&byteArray)[8]);
    static Measurement fromByteArray(uint8_t (&byteArray)[8]);
    const String toString();
};