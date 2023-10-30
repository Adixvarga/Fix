// send digital devices data to blynk (gpio16 is not compatible with digital devices - no interrupt?)
void sendDevices()
{
  static String noSensor = "no sensor";
	
  if (gpio02Devices != 0) {
    devicesGpio02.requestTemperatures();

    for (byte i = 0; i < gpio02Devices; i++) {
      Blynk.virtualWrite(V_GPIO_02_SENS01 + i, floatReductor(String(devicesGpio02.getTempCByIndex(i)), 2));
    }
  }
  else if (readDHT(2)) {
    Blynk.virtualWrite(V_GPIO_02_SENS01    , floatReductor(String(G02t), 2));
    Blynk.virtualWrite(V_GPIO_02_SENS01 + 1, floatReductor(String(G02h), 1));
  }
  else {
	for (byte i = 0; i < 11; i++) {
      Blynk.virtualWrite(V_GPIO_02_SENS01 + i, noSensor);
    }
  }

  ////////////////////////////////////////////////
  if (type != 4 && gpio04Devices != 0) {
    devicesGpio04.requestTemperatures();

    for (byte i = 0; i < gpio04Devices; i++) {
      Blynk.virtualWrite(V_GPIO_04_SENS01 + i, floatReductor(String(devicesGpio04.getTempCByIndex(i)), 2));
    }
  }
  else if (type != 4 && readDHT(4)) {
    Blynk.virtualWrite(V_GPIO_04_SENS01    , floatReductor(String(G04t), 2));
    Blynk.virtualWrite(V_GPIO_04_SENS01 + 1, floatReductor(String(G04h), 1));
  }
  else {
	for (byte i = 0; i < 11; i++) {
      Blynk.virtualWrite(V_GPIO_04_SENS01 + i, noSensor);
    }
  }

  /////////////////////////////////////////////////
  if (type != 4 && gpio14Devices != 0) {
    devicesGpio14.requestTemperatures();

    for (byte i = 0; i < gpio14Devices; i++) {
      Blynk.virtualWrite(V_GPIO_14_SENS01 + i, floatReductor(String(devicesGpio14.getTempCByIndex(i)), 2));
    }
  }
  else if (type != 4 && readDHT(14)) {
    Blynk.virtualWrite(V_GPIO_14_SENS01    , floatReductor(String(G14t), 2));
    Blynk.virtualWrite(V_GPIO_14_SENS01 + 1, floatReductor(String(G14h), 1));
  }
  else {
	for (byte i = 0; i < 11; i++) {
      Blynk.virtualWrite(V_GPIO_14_SENS01 + i, noSensor);
    }
  }
}
