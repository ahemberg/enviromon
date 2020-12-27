#include <Storage.h>

/* Erases all measurements by resetting addr to first memory address*/
void Storage::eraseMem()
{
    EEPROM.write(0, 0);
    EEPROM.write(1, 2);
}
//TODO: Handle overflow
Measurement Storage::getMeasurement(uint16_t address)
{
    uint8_t byteArray[MEM_SIZE];

    for (uint8_t i = 0; i < MEM_SIZE; i++)
    {
        byteArray[i] = EEPROM.read(address + i);
    }

    return Measurement::fromByteArray(byteArray);
}

void Storage::writeMeasurement(Measurement measurement)
{
    uint8_t byteArray[MEM_SIZE];
    readNextAddress();

    if (this->nextAddress + MEM_SIZE > EEPROM.length())
    {
        //Measurement would wrap over. Not handling this case. Wrap before write
        this->nextAddress = 2;
    }

    measurement.getAsByteArray(byteArray);

    for (uint8_t i = 0; i < MEM_SIZE; i++)
    {
        EEPROM.write(this->nextAddress + i, byteArray[i]);
    }
    updateAddress(this->nextAddress + MEM_SIZE);
}

void Storage::readNextAddress()
{
    this->nextAddress = (uint16_t)((uint8_t)EEPROM.read(0) << 8 | (uint8_t)EEPROM.read(1));

    if (this->nextAddress < 2 + MEM_SIZE)
    {
        this->previousAddress = 2;
    }
    else
    {
        this->previousAddress = this->nextAddress - MEM_SIZE;
    }
}

void Storage::updateAddress(uint16_t newAddress)
{
    EEPROM.write(0, (uint8_t)(newAddress >> 8));
    EEPROM.write(1, (uint8_t)(newAddress & 0xFF));
    this->previousAddress = nextAddress;
    this->nextAddress = newAddress;
}

uint16_t Storage::getNextAddress()
{
    return this->nextAddress;
}

Measurement Storage::getLatestMeasurement()
{
    return getMeasurement(this->previousAddress);
}

Storage::Storage()
{
    readNextAddress();
}