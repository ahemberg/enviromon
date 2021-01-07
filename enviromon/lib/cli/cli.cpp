#include "cli.h"

Cli::Cli(RTC_DS3231 &r) : rtc(r) {}

void Cli::mem()
{
  File dataLog = SD.open(DATALOG);
  if (dataLog) {
    while (dataLog.available()) {
      Serial.write(dataLog.read());
    }
  }
}

void Cli::time()
{
  Serial.println("GET | SET | EXIT ");

  while (true)
  {
    Serial.print("TIME $: ");
    while (!Serial.available())
    {
    }
    String subCommand = Serial.readStringUntil('\n');
    subCommand.trim();
    if (subCommand.equalsIgnoreCase("SET"))
    {
      Serial.println("SET");
      Serial.print("YR: ");
      while (!Serial.available())
      {
      }
      uint16_t year = Serial.readStringUntil('\n').toInt();
      Serial.println(year, DEC);
      Serial.print("MTH: ");
      while (!Serial.available())
      {
      }
      uint8_t month = Serial.readStringUntil('\n').toInt();
      Serial.println(month, DEC);

      Serial.print("DY: ");
      while (!Serial.available())
      {
      }
      uint8_t day = Serial.readStringUntil('\n').toInt();
      Serial.println(day, DEC);

      Serial.print("HR: ");
      while (!Serial.available())
      {
      }
      uint8_t hour = Serial.readStringUntil('\n').toInt();
      Serial.println(hour, DEC);

      Serial.print("MIN: ");
      while (!Serial.available())
      {
      }
      uint8_t minute = Serial.readStringUntil('\n').toInt();
      Serial.println(minute, DEC);
      DateTime dt(year, month, day, hour, minute);
      rtc.adjust(dt);
    }
    else if (subCommand.equalsIgnoreCase("GET"))
    {
      DateTime now = rtc.now();
      Serial.print(now.year(), DEC);
      Serial.print("-");
      Serial.print(now.month(), DEC);
      Serial.print("-");
      Serial.print(now.day(), DEC);
      Serial.print(" ");
      Serial.print(now.hour(), DEC);
      Serial.print(":");
      Serial.print(now.minute(), DEC);
      Serial.print(":");
      Serial.println(now.second(), DEC);
    }
    else if (subCommand.equalsIgnoreCase("EXIT"))
    {
      break;
    }
    else
    {
      Serial.println("invalid!");
    }
  }
}

void Cli::mainL()
{
  if (Serial.available() > 0)
  {
    String baseCommand = Serial.readStringUntil('\n');
    baseCommand.trim();
    if (baseCommand.equalsIgnoreCase("TIME"))
    {
      Serial.println(baseCommand);
      time();
    }
    else if (baseCommand.equalsIgnoreCase("MEM"))
    {
      mem();
    }
    else
    {
      Serial.println("err! TIME | MEM ");
    }
  }
}
