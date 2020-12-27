#pragma once

#include <Arduino.h>
#include "DateHolder.h"
#include "constants.h"


/*
    Abstraction of measurement saved in memory
*/
class Measurement
{
private:
    uint8_t byteArray[MEM_SIZE];
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
    void getAsByteArray(uint8_t (&byteArray)[MEM_SIZE]);
    static Measurement fromByteArray(uint8_t (&byteArray)[MEM_SIZE]);
    const String toString();
};