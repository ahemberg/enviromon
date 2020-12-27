#include "cli.h"

Cli::Cli(DS3231 c, Storage s) : Clock(c), storage(s) {}

void Cli::mem()
{
  Serial.println("Memory interface: GETADDR | DUMP | LATEST | ERASE | EXIT ");

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
      Serial.println("invalid command! GETADDR | DUMP | LATEST | ERASE | EXIT");
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
      Serial.print("YEAR (only decade!): ");
      while (!Serial.available())
      {
      }
      byte year = Serial.readStringUntil('\n').toInt(); //Error prone but maybe ok..
      Serial.println(year, DEC);
      Clock.setYear(year);

      Serial.print("MONTH: ");
      while (!Serial.available())
      {
      }
      byte month = Serial.readStringUntil('\n').toInt(); //Error prone but maybe ok..
      Serial.println(month, DEC);
      Clock.setMonth(month);

      Serial.print("DAY: ");
      while (!Serial.available())
      {
      }
      byte day = Serial.readStringUntil('\n').toInt(); //Error prone but maybe ok..
      Serial.println(day, DEC);
      Clock.setDate(day);

      Serial.print("HOUR: ");
      while (!Serial.available())
      {
      }
      byte hour = Serial.readStringUntil('\n').toInt(); //Error prone but maybe ok..
      Serial.println(hour, DEC);
      Clock.setHour(hour);

      Serial.print("MINUTE: ");
      while (!Serial.available())
      {
      }
      byte minute = Serial.readStringUntil('\n').toInt(); //Error prone but maybe ok..
      Clock.setMinute(minute);
      Serial.println(minute, DEC);
      Clock.setSecond(0);
    }
    else if (subCommand.equalsIgnoreCase("GET"))
    {
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
  //TODO break this out into a cli object that will be called IF a pin is high. Then we add a toggle switch for CLI mode..
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
