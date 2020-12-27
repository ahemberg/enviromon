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
#include <EEPROM.h>
#include <Storage.h>

DS3231 Clock;
Storage storage;
Cli cli = Cli(Clock, storage);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature tempSensors(&oneWire);
DHT dht(DHTPIN, DHTTYPE);


float getTemperature()
{
  tempSensors.requestTemperatures();
  return tempSensors.getTempCByIndex(0);
}

Measurement doMeasurement()
{
  bool timeFlag = false;
  DateHolder measurementDate = DateHolder(
      Clock.getYear(),
      Clock.getMonth(timeFlag),
      Clock.getDate(),
      Clock.getHour(timeFlag, timeFlag),
      Clock.getMinute(),
      Clock.getSecond());
  return Measurement(measurementDate, getTemperature(), dht.readHumidity() - 10, 0, 0);
}

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  tempSensors.begin();
  dht.begin();
  pinMode(CLI_ENABLE, INPUT_PULLUP);
}

void loop()
{

  //TODO Trigger measurement on alarm.
  //CLI to dump memory
  if (digitalRead(CLI_ENABLE) == LOW)
  {
    cli.mainL();
  }
  else
  {
    Measurement measurement = doMeasurement();
    storage.writeMeasurement(measurement);
    Serial.println(storage.getNextAddress());
    delay(1000);
  }
}
