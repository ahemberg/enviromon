#include "Measurement.h"

uint8_t encodeValue(float value, float minValue, float maxValue)
{

    if (value <= minValue)
    {
        return (uint8_t)0;
    }
    else if (value >= maxValue)
    {
        return (uint8_t)255;
    }

    float encoded = ((value - minValue) * 255.0) / (maxValue - minValue);
    return (uint8_t)round(encoded);
}

float decodeValue(uint8_t encoded, float minValue, float maxValue)
{
    float voltage = minValue + (encoded * (maxValue - minValue)) / 255.0;
}

void Measurement::getAsByteArray(uint8_t (&byteArray)[8])
{
    byteArray[0] = this->date.getYear();
    byteArray[1] = this->date.getMonth();
    byteArray[2] = this->date.getDay();
    byteArray[3] = this->date.getHour();
    byteArray[4] = encodeValue(this->temperature, -55.0, 125.0); //TODO: These are sensor min/max. Will never encounter extremes. Narrower band gives higher res!
    byteArray[5] = encodeValue(this->relativeHumidity, 0.0, 100.0);
    byteArray[6] = encodeValue(this->batteryVoltage, 2.5, 4.5);
    byteArray[7] = encodeValue(this->solarPanelVoltage, 0.0, 10.0);
}

Measurement::Measurement(const DateHolder date,
                         const float temperature,
                         const float relativeHumidity,
                         const float batteryVoltage,
                         const float solarPanelVoltage) : date(date),
                                                          temperature(temperature),
                                                          relativeHumidity(relativeHumidity),
                                                          batteryVoltage(batteryVoltage),
                                                          solarPanelVoltage(solarPanelVoltage)
{
}

/*
Used when dumping data to console.
*/
const String Measurement::toString()
{
    return String(this->date.getYear(), DEC) + "-" +
           String(this->date.getMonth(), DEC) + "-" +
           String(this->date.getDay(), DEC) + " " +
           String(this->date.getHour(), DEC) + ":" +
           String(this->date.getMinute(), DEC) + " | " +
           String(this->temperature, DEC) + " | " +
           String(this->relativeHumidity, DEC) + " | " +
           String(this->batteryVoltage, DEC) + " | " +
           String(this->solarPanelVoltage, DEC);
}