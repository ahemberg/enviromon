#include "pins.h"

#include <Arduino.h>
#include <Wire.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <RTClib.h>
//#include <cli.h>
#include <Measurement.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include <DHT.h>
#include <avr/sleep.h>
#include <avr/power.h>

#include <SPI.h>
#include <SD.h>

RTC_DS3231 rtc;
//Cli cli = Cli(rtc);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature tempSensors(&oneWire);
DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

float measureVoltage(int pin, float r1 = 1, float r2 = 1)
{
  float rawVoltage = ((float)analogRead(pin) / 1024.0) * BUS_VOLTAGE;
  return (rawVoltage * (r1 + r2)) / r2;
}

float measurePressure()
{
  sensors_event_t event;
  bmp.getEvent(&event);
  return event.pressure;
}

//TODO need to save all of these more memory efficiently. Convert to uint16_t and save as is. Deconversion could be made offline
//Store voltages as the 10 bit numbers they are for instance!
Measurement doMeasurement()
{
  tempSensors.requestTemperatures();
  return Measurement(rtc.now().unixtime(),
                     tempSensors.getTempCByIndex(0),
                     dht.readHumidity() - 10,
                     measurePressure(),
                     measureVoltage(BATT_V_PIN, BATT_R1, BATT_R2));
}

void alarm_ISR()
{
  sleep_disable();                                   // Disable sleep mode
  detachInterrupt(digitalPinToInterrupt(ALARM_PIN)); // Detach the interrupt to stop it firing
}

void enterSleep()
{
  sleep_enable(); // Enabling sleep mode

  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // Setting the sleep mode, in this case full sleep

  noInterrupts(); // Disable interrupts
  attachInterrupt(digitalPinToInterrupt(ALARM_PIN), alarm_ISR, LOW);

  //Serial.println(F("sleep")); // Print message to serial monitor
  Serial.flush(); // Ensure all characters are sent to the serial monitor

  power_adc_disable();
  power_spi_disable();
  power_twi_disable();
  power_timer0_disable();
  power_timer1_disable();
  power_usart0_disable();

  interrupts(); // Allow interrupts again
  sleep_cpu();  // Enter sleep mode

  /* The program will continue from here when it wakes */
  power_adc_enable();
  power_spi_enable();
  power_twi_enable();
  power_timer0_enable();
  power_timer1_enable();
  power_usart0_enable();

  // Disable and clear alarm
  rtc.disableAlarm(1);
  rtc.clearAlarm(1);

  Serial.println(F("wake")); // Print message to show we're back
}

void setup()
{

  //SD Card
  SD.begin(4);

  //Serial and onewire
  Serial.begin(115200);
  Wire.begin();

  //Sensors
  tempSensors.begin();
  dht.begin();
  bmp.begin();

  //Input Pins
  pinMode(CLI_ENABLE, INPUT_PULLUP);
  pinMode(ALARM_PIN, INPUT_PULLUP);

  //ANALOG PINS
  pinMode(BATT_V_PIN, INPUT);

  //RTC MODULE SETUP
  rtc.disableAlarm(DS3231_ALARM1);
  rtc.disableAlarm(DS3231_ALARM2);
  rtc.clearAlarm(DS3231_ALARM1);
  rtc.clearAlarm(DS3231_ALARM2);
  rtc.writeSqwPinMode(DS3231_OFF);
}

void loop()
{
  //Debounce delay (TODO consider removing, or identifying a button press!)
  //delay(10);

  //Logic for CLI removed due to no memory left
  //if (digitalRead(CLI_ENABLE) == LOW)
  //{
  //  detachInterrupt(digitalPinToInterrupt(ALARM_PIN));
  //Serial.println("Recompile with CLI enabled to set time");
  //cli.mainL();
  //Serial.flush();
  //}
  //else
  //{
  //Do measurement and save
  Measurement measurement = doMeasurement();
  File dataFile = SD.open(DATALOG, FILE_WRITE);
  Serial.println(measurement.toCsvString());
  dataFile.println(measurement.toCsvString());
  rtc.setAlarm1(DateTime(2020, 6, 25, 0, 0, 0), DS3231_A1_Second); // Set Alarm at even minute
  dataFile.close();
  enterSleep();
  //}
}
