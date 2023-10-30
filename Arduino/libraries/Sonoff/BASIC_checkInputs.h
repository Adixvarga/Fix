// if no digital devices on gpio2 (ds18, dht, etc) use as standard pin
void checkInputs()
{
  static bool lastGpio02State = digitalRead(GPIO_02);
  static bool lastGpio04State = digitalRead(GPIO_04);
  static bool lastGpio14State = digitalRead(GPIO_14);
  static bool lastGpio16State = digitalRead(GPIO_16);

  if (gpio02Devices == 0 && digitalRead(GPIO_02) != lastGpio02State) {
	  gpio02Timestamp = millis();
      gpio02LED.setValue(digitalRead(GPIO_02) * 255);
	  lastGpio02State = digitalRead(GPIO_02);
	  
      if (gpio02NotifyEnabled) Blynk.notify(String(unitName) + ": " + s1Notif);
      
	  #ifdef MAIL_G02_STATE
      Blynk.email("mgbiker3@gmail.com", MAIL_G02_MESSAGE, "device " + unitName + ": " + MAIL_G02_MESSAGE);
      #endif
  }

  if (type != 4 && gpio04Devices == 0 && digitalRead(GPIO_04) != lastGpio04State) {
      gpio04Timestamp = millis();
      gpio04LED.setValue(digitalRead(GPIO_04) * 255);
	  lastGpio04State = digitalRead(GPIO_04);
	  
      if (gpio04NotifyEnabled) Blynk.notify(String(unitName) + ": " + s2Notif);
      
	  #ifdef MAIL_G04_STATE
      Blynk.email("mgbiker3@gmail.com", MAIL_G04_MESSAGE, "device " + unitName + ": " + MAIL_G04_MESSAGE);
      #endif
  }

  if (type != 4 && gpio14Devices == 0 && digitalRead(GPIO_14) != lastGpio14State) {
      gpio14Timestamp = millis();
      gpio14LED.setValue(digitalRead(GPIO_14) * 255);
	  lastGpio14State = digitalRead(GPIO_14);
	  
      if (gpio14NotifyEnabled) Blynk.notify(String(unitName) + ": " + s3Notif);
      
	  #ifdef MAIL_G14_STATE
      Blynk.email("mgbiker3@gmail.com", MAIL_G14_MESSAGE, "device " + unitName + ": " + MAIL_G14_MESSAGE);
      #endif
  }

  if (gpio16Devices == 0 && digitalRead(GPIO_16) != lastGpio16State) {
      gpio16Timestamp = millis();
      gpio16LED.setValue(digitalRead(GPIO_16) * 255);
	  lastGpio16State = digitalRead(GPIO_16);
	  
      if (gpio16NotifyEnabled) Blynk.notify(String(unitName) + ": " + s4Notif);
	  
	  #ifdef MAIL_G16_STATE
      Blynk.email("mgbiker3@gmail.com", MAIL_G16_MESSAGE, "device " + unitName + ": " + MAIL_G16_MESSAGE);
      #endif
  }
}

