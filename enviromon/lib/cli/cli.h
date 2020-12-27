#pragma once
#include <Arduino.h>
#include <DS3231.h>
#include <Storage.h>
#include "constants.h"

class Cli {
  private:
    DS3231 Clock;
    Storage storage;
    bool century;
    bool h12Flag;
    bool pmFlag;
    void time();
    void mem();

  public:
    Cli(DS3231 Clock, Storage storage);
    void mainL();
};