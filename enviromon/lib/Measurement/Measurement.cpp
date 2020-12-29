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

void Measurement::getAsByteArray(uint8_t (&byteArray)[MEM_SIZE])
{

    uint32_t unixTime = this->date.unixtime();

    byteArray[0] = (uint8_t)(unixTime >> 24);
    byteArray[1] = (uint8_t)(unixTime >> 16) & 0xFF;
    byteArray[2] = (uint8_t)(unixTime >> 8) & 0xFF;
    byteArray[3] = (uint8_t)(unixTime & 0xFF);
    byteArray[4] = encodeValue(this->temperature, MIN_TEMP, MAX_TEMP);
    byteArray[5] = encodeValue(this->relativeHumidity, MIN_HUMIDITY, MAX_HUMIDITY);
    byteArray[6] = encodeValue(this->batteryVoltage, MIN_BATT_V, MAX_BATT_V);
    byteArray[7] = encodeValue(this->solarPanelVoltage, MIN_SP_V, MAX_SP_V);
}

Measurement Measurement::fromByteArray(uint8_t (&byteArray)[MEM_SIZE])
{

    uint32_t unixTime = (uint32_t)((uint32_t)byteArray[0] << 24 | (uint32_t)byteArray[1] << 16 | (uint32_t)byteArray[2] << 8 | (uint32_t)byteArray[3]);

    DateTime date(unixTime);

    Measurement measurement(date,
                            decodeValue(byteArray[4], MIN_TEMP, MAX_TEMP),
                            decodeValue(byteArray[5], MIN_HUMIDITY, MAX_HUMIDITY),
                            decodeValue(byteArray[6], MIN_BATT_V, MAX_BATT_V),
                            decodeValue(byteArray[7], MIN_SP_V, MAX_SP_V));

    return measurement;
}

Measurement::Measurement(const DateTime date,
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
    return String(this->date.year(), DEC) + "-" +
           String(this->date.month(), DEC) + "-" +
           String(this->date.day(), DEC) + " " +
           String(this->date.hour(), DEC) + ":" +
           String(this->date.minute(), DEC) + " | " +
           String(this->temperature, DEC) + " | " +
           String(this->relativeHumidity, DEC) + " | " +
           String(this->batteryVoltage, DEC) + " | " +
           String(this->solarPanelVoltage, DEC);
}

/*
Used when dumping data to console.
*/
const String Measurement::toCsvString()
{
    return String(this->date.unixtime(), DEC) + ";" +
           String(this->temperature, DEC) + ";" +
           String(this->relativeHumidity, DEC) + ";" +
           String(this->batteryVoltage, DEC) + ";" +
           String(this->solarPanelVoltage, DEC);
}