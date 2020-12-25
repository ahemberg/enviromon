#include <Arduino.h>
#include <Wire.h>
#include <DS3231.h>

DS3231 Clock;
bool century;
bool h12Flag;
bool pmFlag;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
}

/*
  If serial available (and pin high, but that for later) check keywords:

  TIME SET YYYY-MM-DD HH:mm
  TIME GET -> Returns set time





*/

void loop()
{
  if (Serial.available() > 0)
  {
    Serial.println(Serial.available());
    String baseCommand = Serial.readStringUntil('\n');
    baseCommand.trim();
    Serial.print("DEBUG: baseCommand -- ");
    Serial.println(baseCommand);
    if (baseCommand.equalsIgnoreCase("TIME"))
    {
      bool exit = false;
      while (!exit)
      {
        Serial.print("TIME $: ");
        while (!Serial.available()) {}
        String subCommand = Serial.readStringUntil('\n');
        subCommand.trim();
        if (subCommand.equalsIgnoreCase("SET")) {

          Serial.println("SET ---- ");
          Serial.print("YEAR (only decade!): ");
          while (!Serial.available()) {}
          byte year = Serial.readStringUntil('\n').toInt(); //Error prone but maybe ok..
          Serial.println(year, DEC);
          Clock.setYear(year);

          Serial.print("MONTH: ");
          while (!Serial.available()) {}
          byte month = Serial.readStringUntil('\n').toInt(); //Error prone but maybe ok..
          Serial.println(month, DEC);
          Clock.setMonth(month);


          Serial.print("DAY: ");
          while (!Serial.available()) {}
          byte day = Serial.readStringUntil('\n').toInt(); //Error prone but maybe ok..
          Serial.println(day, DEC);
          Clock.setDate(day);


          Serial.print("HOUR: ");
          while (!Serial.available()) {}
          byte hour = Serial.readStringUntil('\n').toInt(); //Error prone but maybe ok..
          Serial.println(hour, DEC);
          Clock.setHour(hour);

          Serial.print("MINUTE: ");
          while (!Serial.available()) {}
          byte minute = Serial.readStringUntil('\n').toInt(); //Error prone but maybe ok..
          Clock.setMinute(minute);
          Serial.println(minute, DEC);
          Clock.setSecond(0);
        } else if (subCommand.equalsIgnoreCase("GET")) {
          //GET TIME
          Serial.print(20, DEC);
          Serial.print(Clock.getYear(), DEC);
          Serial.print("-");
          Serial.print(Clock.getMonth(century), DEC);
          Serial.print("-");
          Serial.print(Clock.getDate(), DEC);
          Serial.print(" ");
          Serial.print(Clock.getHour(h12Flag, pmFlag), DEC);
          Serial.print(":");
          Serial.print(Clock.getMinute(), DEC);
          Serial.print(":");
          Serial.println(Clock.getSecond(), DEC);
        } else if (subCommand.equalsIgnoreCase("EXIT")) {
          break;
        } else {
          Serial.println("invalid command! SET | GET | HELP | EXIT");
        }
      }
    }
  }
  delay(100);
  Serial.println("DEBUG: Loop rerun.");
}