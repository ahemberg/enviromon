#pragma once

#include <Arduino.h>
#include "constants.h"

/*
    Abstraction of measurement saved in memory
*/
class Measurement
{
private:
    const uint32_t unixTime;
    const float temperature;
    const float relativeHumidity;
    const float barometricPressure;
    const float batteryVoltage;

public:
    Measurement(const uint32_t unixTime,
                const float temperature,
                const float relativeHumidity,
                const float barometricPressure,
                const float batteryVoltage);
    const String toCsvString();
};