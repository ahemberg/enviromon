#pragma once
#include <Arduino.h>
#include <DS3231.h>

class Cli {
  private:
    DS3231 Clock;
    bool century;
    bool h12Flag;
    bool pmFlag;
    void time();
    void mem();

  public:
    Cli(DS3231 Clock);
    void mainL();
};