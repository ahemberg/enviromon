#include "pins.h"

#include <Arduino.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DS3231.h>
#include <cli.h>

DS3231 Clock;
Cli cli = Cli(Clock);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature tempSensors(&oneWire);


float getTemperature() {
  tempSensors.requestTemperatures();
  return tempSensors.getTempCByIndex(0);
}

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  tempSensors.begin();
  pinMode(CLI_ENABLE, INPUT_PULLUP);
}

void loop()
{
  if (digitalRead(CLI_ENABLE) == LOW) {
    cli.mainL();
  }
  
  Serial.print(getTemperature());
  Serial.println("C");

  
}
