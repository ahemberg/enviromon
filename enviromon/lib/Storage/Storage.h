#pragma once
#include <EEPROM.h>
#include <Measurement.h>

class Storage
{
private:
    uint16_t nextAddress;
    void updateAddress(uint16_t newAddress);

public:
    Storage(/* args */);
    void readAddress();
    void writeMeasurement(Measurement measurement);
    void eraseMem();
};

/* Erases all measurements by resetting addr to first memory address*/
void Storage::eraseMem()
{
    EEPROM.write(0, 0);
    EEPROM.write(1, 2);
}

void Storage::writeMeasurement(Measurement measurement)
{
    uint8_t byteArray[8];
    readAddress();
    measurement.getAsByteArray(byteArray);

    for (uint8_t i = 0; i < 8; i++)
    {
        EEPROM.write(this->nextAddress, byteArray[i]);
    }
    updateAddress(this->nextAddress + 8);
}

void Storage::readAddress()
{
    this->nextAddress = (uint16_t)((uint8_t)EEPROM.read(0) << 8 | (uint8_t)EEPROM.read(1));
}

void Storage::updateAddress(uint16_t newAddress)
{
    EEPROM.write(0, (uint8_t)(newAddress >> 8));
    EEPROM.write(1, (uint8_t)(newAddress & 0xFF));
    this->nextAddress = newAddress;
}

Storage::Storage(/* args */)
{
}