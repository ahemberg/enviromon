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
    return minValue + (encoded * (maxValue - minValue)) / 255.0;
}

void Measurement::getAsByteArray(uint8_t (&byteArray)[8])
{
    byteArray[0] = this->date.getYear();
    byteArray[1] = this->date.getMonth();
    byteArray[2] = this->date.getDay();
    byteArray[3] = this->date.getHour();
    byteArray[4] = encodeValue(this->temperature, MIN_TEMP, MAX_TEMP);
    byteArray[5] = encodeValue(this->relativeHumidity, MIN_HUMIDITY, MAX_HUMIDITY);
    byteArray[6] = encodeValue(this->batteryVoltage, MIN_BATT_V, MAX_BATT_V);
    byteArray[7] = encodeValue(this->solarPanelVoltage, MIN_SP_V, MAX_SP_V);
}

Measurement Measurement::fromByteArray(uint8_t (&byteArray)[8])
{

    DateHolder date(byteArray[0], byteArray[1], byteArray[2], byteArray[3]);

    Measurement measurement(date,
                            decodeValue(byteArray[4], MIN_TEMP, MAX_TEMP),
                            decodeValue(byteArray[5], MIN_HUMIDITY, MAX_HUMIDITY),
                            decodeValue(byteArray[6], MIN_BATT_V, MAX_BATT_V),
                            decodeValue(byteArray[7], MIN_SP_V, MAX_SP_V));

    return measurement;
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