#pragma once
#include <Arduino.h>
#include <RTClib.h>
#include <Storage.h>
#include "constants.h"

class Cli
{
private:
  RTC_DS3231 &rtc;
  Storage &storage;
  bool century;
  bool h12Flag;
  bool pmFlag;
  void time();
  void mem();

public:
  Cli(RTC_DS3231 &rtc, Storage &storage);
  void mainL();
};