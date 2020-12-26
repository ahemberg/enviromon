#pragma once

#include <Arduino.h>
#include "DateHolder.h"

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
    Measurement fromByteArray(uint8_t &measArray);
    const String toString();
};