void getDS18temp()
{
  sensors.requestTemperatures();

  DS18All[0] = sensors.getTempC(DS18boiler);
  DS18All[1] = sensors.getTempC(DS18pool);
  DS18All[2] = sensors.getTempC(DS18outside);
  DS18All[3] = sensors.getTempC(DS18agent);
  DS18All[4] = sensors.getTempC(DS18inside);
  }
