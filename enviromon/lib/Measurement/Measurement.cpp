#include "Measurement.h"

Measurement::Measurement(const uint32_t unixTime,
                         const float temperature,
                         const float relativeHumidity,
                         const float barometricPressure,
                         const float batteryVoltage) : unixTime(unixTime),
                                                       temperature(temperature),
                                                       relativeHumidity(relativeHumidity),
                                                       barometricPressure(barometricPressure),
                                                       batteryVoltage(batteryVoltage)

{
}

/*
Used when dumping data to console.
*/
const String Measurement::toCsvString()
{
    return String(this->unixTime, DEC) + ";" +
           String(this->temperature, DEC) + ";" +
           String(this->relativeHumidity, DEC) + ";" +
           String(this->barometricPressure, DEC) + ";" +
           String(this->batteryVoltage, DEC);
}