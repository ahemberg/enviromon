#include "pins.h"

#include <Arduino.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <DS3231.h>
#include <cli.h>
#include <DateHolder.h>
#include <Measurement.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

DS3231 Clock;
Cli cli = Cli(Clock);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature tempSensors(&oneWire);
DHT dht(DHTPIN, DHTTYPE);

float temperature;
float internalTemperature; //Temperature from RTC. Not to be saved but maybe used for battery heater?
float relHumidity;
float dhtTemp;
uint8_t byteArray[8];

float getTemperature()
{
  tempSensors.requestTemperatures();
  return tempSensors.getTempCByIndex(0);
}

Measurement doMeasurement() {
    bool timeFlag = false;
    DateHolder measurementDate = DateHolder(
        Clock.getYear(),
        Clock.getMonth(timeFlag),
        Clock.getDate(),
        Clock.getHour(timeFlag, timeFlag),
        Clock.getMinute(),
        Clock.getSecond());
    return Measurement(measurementDate, getTemperature(), dht.readHumidity(), 0, 0);
  }

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  tempSensors.begin();
  dht.begin();
  pinMode(CLI_ENABLE, INPUT_PULLUP);
}

void loop()
{

  //TODO Trigger measurement on alarm.
  //Calculate memory map from a measurement
  //Save to eeprom 
  //Create Measurement object from memory
  //Need a memory management class 

  if (digitalRead(CLI_ENABLE) == LOW)
  {
    cli.mainL();
  }
  else
  {
    Measurement measurement = doMeasurement();
    measurement.getAsByteArray(byteArray);
    Serial.print("      Meas: ");
    Serial.println(measurement.toString());
    Serial.print("From Bytes: ");
    Serial.println(Measurement::fromByteArray(byteArray).toString());
  }
}
