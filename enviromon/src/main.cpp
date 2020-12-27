#include "pins.h"

#include <Arduino.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <RTClib.h>
#include <cli.h>
#include <DateHolder.h>
#include <Measurement.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <EEPROM.h>
#include <Storage.h>
#include <avr/sleep.h>

RTC_DS3231 rtc;
Storage storage; //This should probablt by volatile...
Cli cli = Cli(rtc, storage);
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
  return Measurement(rtc.now(), getTemperature(), dht.readHumidity() - 10, 0, 0);
}

void alarm_ISR() {
  // This runs when SQW pin is low. It will wake up the µController
  
  sleep_disable(); // Disable sleep mode
  detachInterrupt(digitalPinToInterrupt(ALARM_PIN)); // Detach the interrupt to stop it firing
}

void enterSleep(){
  sleep_enable();                       // Enabling sleep mode
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);  // Setting the sleep mode, in this case full sleep
  
  noInterrupts();                       // Disable interrupts
  attachInterrupt(digitalPinToInterrupt(ALARM_PIN), alarm_ISR, LOW);
  
  Serial.println("Going to sleep!");    // Print message to serial monitor
  Serial.flush();                       // Ensure all characters are sent to the serial monitor
  
  interrupts();                         // Allow interrupts again
  sleep_cpu();                          // Enter sleep mode

  /* The program will continue from here when it wakes */
  
  // Disable and clear alarm
  rtc.disableAlarm(1);
  rtc.clearAlarm(1);
  
  Serial.println("I'm back!");          // Print message to show we're back
 }

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  tempSensors.begin();
  dht.begin();
  pinMode(CLI_ENABLE, INPUT_PULLUP);
  pinMode(ALARM_PIN, INPUT_PULLUP);

  rtc.disableAlarm(DS3231_ALARM1);
  rtc.disableAlarm(DS3231_ALARM2);
  rtc.clearAlarm(DS3231_ALARM1);
  rtc.clearAlarm(DS3231_ALARM2);

  rtc.writeSqwPinMode(DS3231_OFF);
}

void loop()
{

  //TODO Trigger measurement on alarm.
  //Add reading of voltages
  //Then done and ready to test!
  //Have Switch to CLI_ENABLE set interrupt low aswell. This should wake the
  if (digitalRead(CLI_ENABLE) == LOW)
  {
    detachInterrupt(digitalPinToInterrupt(ALARM_PIN));
    cli.mainL();
    Serial.flush();
  }
  else
  {
    //Do measurement and save
    Measurement measurement = doMeasurement();
    storage.writeMeasurement(measurement);

    // Get current time and set alarm to a time to wake
    //DateTime now = rtc.now();  // Get current time
    //rtc.setAlarm1(now + TimeSpan(0, 0, 0, 10), DS3231_A1_Second); // In 10 seconds
    rtc.setAlarm1(DateTime(2020, 6, 25, 0, 0, 0), DS3231_A1_Second); // Or can be set explicity
    
    enterSleep();  // Go to slee
    
    //ENTER SLEEP MODE
    //Serial.println(storage.getNextAddress());
    //Serial.println(triggered);
    //Measurement measurement = doMeasurement();
    //storage.writeMeasurement(measurement);
    //delay(100);
    //attachInterrupt(digitalPinToInterrupt(ALARM_PIN), alarm_ISR, FALLING);

    //Sleep...
  }
}
