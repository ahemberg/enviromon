#pragma once
#include <EEPROM.h>
#include <Measurement.h>
#include "constants.h"

class Storage
{
private:
    uint16_t nextAddress;
    uint16_t previousAddress;
public:
    Storage(/* args */);
    void readNextAddress();
    void writeMeasurement(Measurement measurement);
    Measurement getMeasurement(uint16_t address);
    Measurement getLatestMeasurement();
    void eraseMem();
    void updateAddress(uint16_t newAddress);
    uint16_t getNextAddress();
};
