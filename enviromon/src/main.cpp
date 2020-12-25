#include <Arduino.h>
#include <Wire.h>
#include <DS3231.h>
#include <cli.h>

DS3231 Clock;
Cli cli = Cli(Clock);


void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
}

void loop()
{
  cli.mainL();
}