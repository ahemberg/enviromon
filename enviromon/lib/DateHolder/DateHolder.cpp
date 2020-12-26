#include "DateHolder.h"

DateHolder::DateHolder(const uint8_t year,
           const uint8_t month,
           const uint8_t day,
           const uint8_t hour,
           const uint8_t minute,
           const uint8_t second) : year(year),
                                   month(month),
                                   day(day),
                                   hour(hour),
                                   minute(minute),
                                   second(second)
{
}

DateHolder::DateHolder(const uint8_t year,
           const uint8_t month,
           const uint8_t day,
           const uint8_t hour,
           const uint8_t minute) : year(year),
                                   month(month),
                                   day(day),
                                   hour(hour),
                                   minute(minute),
                                   second(0)
{
}

DateHolder::DateHolder(const uint8_t year,
           const uint8_t month,
           const uint8_t day,
           const uint8_t hour) : year(year),
                                 month(month),
                                 day(day),
                                 hour(hour),
                                 minute(0),
                                 second(0)
{
}

uint8_t DateHolder::getYear()
{
    return this->year;
}
uint8_t DateHolder::getMonth()
{
    return this->month;
}

uint8_t DateHolder::getDay()
{
    return this->day;
}

uint8_t DateHolder::getHour()
{
    return this->hour;
}

uint8_t DateHolder::getMinute()
{
    return this->minute;
}

uint8_t DateHolder::getSecond()
{
    return this->second;
}
