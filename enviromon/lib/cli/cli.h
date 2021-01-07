#pragma once
#include <Arduino.h>
#include <RTClib.h>
//#include <Storage.h>
#include "constants.h"
#include <SPI.h>
#include <SD.h>

class Cli
{
private:
  RTC_DS3231 &rtc;
  bool century;
  bool h12Flag;
  bool pmFlag;
  void time();
  void mem();

public:
  Cli(RTC_DS3231 &rtc);
  void mainL();
};