#include "cli.h"

Cli::Cli(RTC_DS3231 &r, Storage &s) : rtc(r), storage(s) {}

void Cli::mem()
{
  Serial.println("Memory interface: GETADDR | DUMP | DUMPALL | LATEST | ERASE | EXIT ");

  while (true)
  {
    Serial.print("MEM $: ");
    while (!Serial.available())
    {
    }
    String subCommand = Serial.readStringUntil('\n');
    subCommand.trim();
    if (subCommand.equalsIgnoreCase("GETADDR"))
    {
      Serial.print("\nGETADDR: ");
      Serial.print("Memory points to ");
      Serial.println(storage.getNextAddress());
    }
    else if (subCommand.equalsIgnoreCase("DUMP"))
    {
      //TODO don't print if erased?
      Serial.println("Measurements:");
      for (uint16_t addr = 2; addr < storage.getNextAddress(); addr += MEM_SIZE)
      {
        Serial.println(storage.getMeasurement(addr).toString());
      }
    }
    else if (subCommand.equalsIgnoreCase("DUMPALL"))
    {
      //TODO don't print if erased?
      Serial.println("Measurements:");
      for (uint16_t addr = 2; addr < (EEPROM.length() - MEM_SIZE); addr += MEM_SIZE)
      {
        Serial.println(storage.getMeasurement(addr).toString());
      }
    }
    else if (subCommand.equalsIgnoreCase("LATEST"))
    {
      //TODO don't print if erased?
      Serial.println("Latest measurement: ");
      Serial.println(storage.getLatestMeasurement().toString());
    }
    else if (subCommand.equalsIgnoreCase("ERASE"))
    {
      Serial.print("Will erase all! Continue? [y/N] ");
      while (!Serial.available())
      {
      }
      String confirm = Serial.readStringUntil('\n');
      confirm.trim();
      if (confirm.equalsIgnoreCase("Y"))
      {
        Serial.println("Yes");
        storage.eraseMem();
        Serial.println("Memory Erased!");
      }
      else
      {
        Serial.println("No");
        Serial.println("Aborting!");
      }
    }
    else if (subCommand.equalsIgnoreCase("EXIT"))
    {
      Serial.println("Bye..");
      break;
    }
    else
    {
      Serial.println("invalid command! GETADDR | DUMP | DUMPALL | LATEST | ERASE | EXIT");
    }
  }
}

void Cli::time()
{
  Serial.println("Time interface. GET | SET | EXIT ");

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
      Serial.println("SET ---- ");
      Serial.print("YEAR: ");
      while (!Serial.available())
      {
      }
      uint16_t year = Serial.readStringUntil('\n').toInt();
      Serial.println(year, DEC);
      Serial.print("MONTH: ");
      while (!Serial.available())
      {
      }
      uint8_t month = Serial.readStringUntil('\n').toInt();
      Serial.println(month, DEC);

      Serial.print("DAY: ");
      while (!Serial.available())
      {
      }
      uint8_t day = Serial.readStringUntil('\n').toInt();
      Serial.println(day, DEC);

      Serial.print("HOUR: ");
      while (!Serial.available())
      {
      }
      uint8_t hour = Serial.readStringUntil('\n').toInt();
      Serial.println(hour, DEC);

      Serial.print("MINUTE: ");
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
      Serial.println("Bye..");
      break;
    }
    else
    {
      Serial.println("invalid command! SET | GET | EXIT");
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
      time();
    }
    else if (baseCommand.equalsIgnoreCase("MEM"))
    {
      mem();
    }
    else
    {
      Serial.println("Invalid Command! TIME | MEM ");
    }
  }
}
