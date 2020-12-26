#pragma once
#include <Arduino.h>

class DateHolder
{
private:
    const uint8_t year;
    const uint8_t month;
    const uint8_t day;
    const uint8_t hour;
    const uint8_t minute;
    const uint8_t second;

public:
    DateHolder(const uint8_t year, const uint8_t month, const uint8_t day, const uint8_t hour, const uint8_t minute, const uint8_t second);
    DateHolder(const uint8_t year, const uint8_t month, const uint8_t day, const uint8_t hour, const uint8_t minute);
    DateHolder(const uint8_t year, const uint8_t month, const uint8_t day, const uint8_t hour);
    uint8_t getYear();
    uint8_t getMonth();
    uint8_t getDay();
    uint8_t getHour();
    uint8_t getMinute();
    uint8_t getSecond();
};

