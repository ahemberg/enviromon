#include "pins.h"

#include <Arduino.h>
#include <Wire.h>
#include <DS3231.h>
#include <cli.h>

DS3231 Clock;
Cli cli = Cli(Clock);


void setup()
{
  Serial.begin(9600);
  Wire.begin();
  pinMode(CLI_ENABLE, INPUT_PULLUP);
}

void loop()
{
  if (digitalRead(CLI_ENABLE) == LOW) {
    cli.mainL();
  }
}