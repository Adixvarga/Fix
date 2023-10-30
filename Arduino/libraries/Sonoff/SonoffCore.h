/*
  Sonoff core 2019. written by mgbiker3@gmail.com
*/

void APIwriteDevicePin(String token, String pin, String value)
{
  HTTPClient http;

  // http://blynk-cloud.com/6756b9cb9aba4980a5e4fbd65c33714c/update/v14?value=HH

  String url = "http://blynk-cloud.com/";  // url
  url += token;                            // blynk token
  url += "/update/";
  url += pin;                              // pin to update
  url += "?value=";
  url += value;                            // value to write

  http.begin(url);
  http.GET();
  delay(50);
  http.end();
  delay(10);
}

String APIreadDevicePin(String token, String pin)
{
  HTTPClient http;

  String payload = "request failed";

  // more info at: https://techtutorialsx.com/2016/07/17/esp8266-http-get-requests/
  // http://blynk-cloud.com/auth_token/get/pin

  String url = "http://blynk-cloud.com/";
  url += token;                                  // blynk token
  url += "/get/";
  url += pin;                                    // pin to read

  http.begin(url);
  
  int httpCode = http.GET();
  delay(50);

  if (httpCode > 0) {
	  payload = http.getString();                // get response payload as String
	  
	  payload.remove(0, 2);
      payload.remove(payload.length() - 2);      // strip [""]
    }
  else payload = payload + ", httpCode: " + httpCode;

  http.end();
  delay(10);

  return payload;
}

// set short or long timestamp
String getTime(bool tsShort = 0)
{
  String timestamp;

  if (tsShort) timestamp = String("<") + hour() + "." + minute() + "." + second() + "> ";
  else timestamp = String("<") + year() + "." + month() + "." + day() + "-" + hour() + "." + minute() + "." + second() + "> ";

  return timestamp;
}

// returns system vcc in volts
float getVcc()
{
	float vcc = (ESP.getVcc() + COMP) / 1000.0;  // -200 is needed for compensation
	return vcc;
}

// returns free ram in %
byte getRamPr()
{
	byte ramPr = ESP.getFreeHeap() * 100 / 81920;
	
	return ramPr;
}

/*
// terminal widget - debug redirect
void serialEvent()
{
  while (Serial.available()) {            // check for data on serial port
    terminal.print((char)Serial.read());  // fires data back out to terminal
  }
  
  terminal.flush();
}
*/

// keeps just the first x decimals in floats
String floatReductor(String data, byte dec)
{
  unsigned int point = data.indexOf('.');

  if (point < data.length()) data.remove(point + dec);
  
  return data;
}

// push system parameters to server
void sendSystemPramaters()
{
	static byte eventCounter;  // send max 10 warnings
	byte freeRam = getRamPr();
	
	int32_t dBm = WiFi.RSSI();
	
	float vcc = getVcc();
	
	if (eventCounter < 11) {
		if (freeRam < 10) {
			Blynk.notify(unitName + " low memory: " + freeRam);
		
			terminal.println(getTime() + unitName + " low memory: " + String(freeRam));
			terminal.flush();
		
			eventCounter++;
		}
		if (vcc > 3.6 || vcc < 2.7) {
			Blynk.notify(unitName + " critical voltage: " + vcc);
		
			terminal.println(getTime() + unitName + " critical voltage: " + String(vcc));
			terminal.flush();
		
			eventCounter++;
		}
		if (dBm > -20 || dBm < -85) {
			Blynk.notify(unitName + " critical dBm: " + dBm);
		
			terminal.println(getTime() + unitName + " critical dBm: " + String(dBm));
			terminal.flush();
			
			eventCounter++;
		}
	}
	
	Blynk.virtualWrite(V_DBM, dBm);                            // wifi signal in dbm
	Blynk.virtualWrite(V_RAM, freeRam);                        // free ram in %
	Blynk.virtualWrite(V_VCC, floatReductor(String(vcc), 2));  // vcc in v
	Blynk.virtualWrite(V_SEND_RTC, getTime(1));
}

void checkBlynk()
{
  if (wifiMulti.run() == WL_CONNECTED) {
    unsigned long startConnecting = millis();

    while (!Blynk.connected()) {
      Blynk.connect();

      if (millis() > startConnecting + SERVER_TIMEOUT) {
        //Serial.print("\tUnable to connect to server. ");
        break;
      }
	  
	  if (Blynk.connected() && !firstRun) {
		  terminal.println(getTime());
	      terminal.flush();
	  
          terminal.println("device " + unitName + " v" + VC + VERSION + " RE-connected w/o restart");
          terminal.flush();
	  
	      terminal.println("connected to: " + WiFi.SSID());
	      terminal.flush();
	  
	      terminal.println("gateway mac: " + WiFi.BSSIDstr());
	      terminal.flush();
	  
	      terminal.println("gateway ip: " + WiFi.gatewayIP().toString());
	      terminal.flush();
	  
	      terminal.println("local ip: " + WiFi.localIP().toString());
	      terminal.flush();
	    }
    }
  }

  //if (WiFi.status() != 3) Serial.print("\tNo WiFi. ");
  //Serial.printf("\tChecking again in %is.\n", BLYNK_CONNECTION_INTERVAL / 1000);
  //Serial.println();
}

bool readDS18(byte pin)
{
  float TDS18G02, TDS18G04, TDS18G14;
	
  switch(pin) {
    case 2:
      devicesGpio02.requestTemperatures();
      TDS18G02 = devicesGpio02.getTempCByIndex(0);

      if (!isnan(TDS18G02) &&
          TDS18G02 >  -40  &&
          TDS18G02 <  125) {

        G02t = TDS18G02;
		
		return true;
      }
      else return false;
	  
      break;
    case 4:
      devicesGpio04.requestTemperatures();
      TDS18G04 = devicesGpio04.getTempCByIndex(0);

      if (!isnan(TDS18G04) &&
          TDS18G04 >  -40  &&
          TDS18G04 <  125) {

        G04t = TDS18G04;
		
		return true;
      }
      else return false;
	  
      break;
	case 14:
      devicesGpio14.requestTemperatures();
      TDS18G14 = devicesGpio14.getTempCByIndex(0);

      if (!isnan(TDS18G14) &&
          TDS18G14 >  -40  &&
          TDS18G14 <  125) {

        G14t = TDS18G14;
		
		return true;
      }
      else return false;
	  
      break;
    default:
      return false;
  }
}

// read and validate dht sensor data
bool readDHT(byte pin)
{
  float TdhtG02t, TdhtG02h;
  float TdhtG04t, TdhtG04h;
  float TdhtG14t, TdhtG14h;
	
  switch(pin) {
    case  2:
      TdhtG02t = dhtG02.readTemperature();
      TdhtG02h = dhtG02.readHumidity();

      if (!isnan(TdhtG02t) &&
          !isnan(TdhtG02h) &&
          TdhtG02t >  -40  &&
          TdhtG02t <   80  &&
          TdhtG02h >    0  &&
          TdhtG02h <  101) {

        G02t = TdhtG02t;
        G02h = TdhtG02h;
		
		return true;
      }
      else return false;
	  
      break;
	case  4:
      TdhtG04t = dhtG04.readTemperature();
      TdhtG04h = dhtG04.readHumidity();

      if (!isnan(TdhtG04t) &&
          !isnan(TdhtG04h) &&
          TdhtG04t >  -40  &&
          TdhtG04t <   80  &&
          TdhtG04h >    0  &&
          TdhtG04h <  101) {

        G04t = TdhtG04t;
        G04h = TdhtG04h;
		
		return true;
      }
      else return false;
	  
      break;  
    case 14:
      TdhtG14t = dhtG14.readTemperature();
      TdhtG14h = dhtG14.readHumidity();

      if (!isnan(TdhtG14t) &&
          !isnan(TdhtG14h) &&
          TdhtG14t >  -40  &&
          TdhtG14t <   80  &&
          TdhtG14h >    0  &&
          TdhtG14h <  101) {

        G14t = TdhtG14t;
        G14h = TdhtG14h;
		
		return true;
      }
      else return false;
	  
      break;
    default:
      return false;
  }
}

void snooze()
{
  if (millis() > snooze02Timeout) {
    snooze02 = false;
    Blynk.virtualWrite(V_SNOOZE02_BUTTON, 0);
  }

  if (millis() > snooze04Timeout) {
    snooze04 = false;
    Blynk.virtualWrite(V_SNOOZE04_BUTTON, 0);
  }

  if (millis() > snooze14Timeout) {
    snooze14 = false;
    Blynk.virtualWrite(V_SNOOZE14_BUTTON, 0);
  }

  if (millis() > snooze16Timeout) {
    snooze16 = false;
    Blynk.virtualWrite(V_SNOOZE16_BUTTON, 0);
  }
}

String getMAC()
{
  byte macArray[6];
  String mac;

  WiFi.macAddress(macArray);

  for (byte i = 0; i <= 5; i++) {
    mac += String(macArray[i], HEX);
    if (i < 5) mac += String("-");
  }

  return mac;
}

String EepromRead(String type)
{
  byte dataLength;
  char nNameArray[40];
  String data = "";

  if (type == "tk:") {                               // token
    for (byte i = 0; i < 32; i++) {
      auth[i] = (char)EEPROM.read(i);
    }
  }
  else if (type == "nm:") {                          // device name (number)
    dataLength = EEPROM.read(34);

    if (dataLength > 0 && dataLength < 35) {
      for (byte i = 0; i < dataLength; i++)
      {
        nNameArray[i] = (char)EEPROM.read(i + 35);
        data = data + String(nNameArray[i]);
      }
    }
    else data = getMAC();                            // if custom name is not set, use mac address
  }
  else if (type == "s1:") {                          // sensor notification
    dataLength = EEPROM.read(70);

    if (dataLength > 1 && dataLength < 35) {
      for (byte i = 0; i < dataLength; i++)
      {
        nNameArray[i] = (char)EEPROM.read(i + 71);
        data = data + String(nNameArray[i]);
      }
    }
    else data = "s1 state changed!";
  }
  else if (type == "s2:") {
    dataLength = EEPROM.read(107);

    if (dataLength > 1 && dataLength < 35) {
      for (byte i = 0; i < dataLength; i++)
      {
        nNameArray[i] = (char)EEPROM.read(i + 108);
        data = data + String(nNameArray[i]);
      }
    }
    else data = "s2 state changed!";
  }
  else if (type == "s3:") {
    dataLength = EEPROM.read(144);

    if (dataLength > 1 && dataLength < 35) {
      for (byte i = 0; i < dataLength; i++)
      {
        nNameArray[i] = (char)EEPROM.read(i + 145);
        data = data + String(nNameArray[i]);
      }
    }
    else data = "s3 state changed!";
  }
  else if (type == "s4:") {
    dataLength = EEPROM.read(181);

    if (dataLength > 1 && dataLength < 35) {
      for (byte i = 0; i < dataLength; i++)
      {
        nNameArray[i] = (char)EEPROM.read(i + 182);
        data = data + String(nNameArray[i]);
      }
    }
    else data = "s4 state changed!";
  }
  else if (type == "F1:") {                           // float storage in eeprom
    dataLength = EEPROM.read(330);

    if (dataLength < 9) {
      for (byte i = 0; i < dataLength; i++)
      {
        nNameArray[i] = (char)EEPROM.read(i + 331);
        data = data + String(nNameArray[i]);
      }
    }
  }
  else if (type == "F2:") {
    dataLength = EEPROM.read(340);

    if (dataLength < 9) {
      for (byte i = 0; i < dataLength; i++)
      {
        nNameArray[i] = (char)EEPROM.read(i + 341);
        data = data + String(nNameArray[i]);
      }
    }
  }
  else if (type == "F3:") {
    dataLength = EEPROM.read(350);

    if (dataLength < 9) {
      for (byte i = 0; i < dataLength; i++)
      {
        nNameArray[i] = (char)EEPROM.read(i + 351);
        data = data + String(nNameArray[i]);
      }
    }
  }
  else if (type == "F4:") {
    dataLength = EEPROM.read(360);

    if (dataLength < 9) {
      for (byte i = 0; i < dataLength; i++)
      {
        nNameArray[i] = (char)EEPROM.read(i + 361);
        data = data + String(nNameArray[i]);
      }
    }
  }
  else if (type == "F5:") {
    dataLength = EEPROM.read(370);

    if (dataLength < 9) {
      for (byte i = 0; i < dataLength; i++)
      {
        nNameArray[i] = (char)EEPROM.read(i + 371);
        data = data + String(nNameArray[i]);
      }
    }
  }

  delay(1);
  return data;
}

/*
    EEPROM map (factory default values: 255):

     0 -  32 : blynk token
    34       : name length (max 34)
    35 -  69 : name
    70       : S1 notification string length (max 34)
    71 - 106 : S1 notification
   107       : S2 notification string length
   108 - 143 : S2 notification
   144       : S3 notification string length
   145 - 180 : S3 notification
   181       : S4 notification string length
   182 - 217 : S4 notification
   300       : restart event (stores in eeprom the last restart cause. see below)
   301       : sonoff type
   311 - 320 : relay state
   321       : server type (cloud == 255) - not used

   330       : store float 1 (max 8 char !!!)
   340       : store float 2
   350       : store float 3
   360       : store float 4
   370       : store float 5
   
   500       : tempThreshold
   503       : ecoReduce
   504       : ecoStartH
   505       : ecoStartM
   506       : ecoStopH
   507       : ecoStopM

  300:
   1 - remote restart
   2 - wifi disconnect timeout
   3 - MY_AUTH defined
   4 - oti performed
   5 - blackout / other

  301 (type):
   1 - 1ch (th10/16)
   2 - 2ch
   3 - n/a
   4 - 4ch
*/

bool EepromWrite(String type, String data)
{
  bool success = false;
  byte dataLength = data.length();

  if (dataLength > 0 && dataLength < 35) {   // validate data
    if (type == "tk:" && dataLength == 32) {
      for (byte i = 0; i < dataLength; i++) EEPROM.write(i, (uint8_t) data.charAt(i));
      success = true;
    }
    else if (type == "nm:") {
      EEPROM.write(34, dataLength);

      for (byte i = 0; i < dataLength; i++) EEPROM.write(i + 35, (uint8_t) data.charAt(i));
      unitName = data;
      success = true;
    }
    else if (type == "s1:") {
      EEPROM.write(70, dataLength);

      for (byte i = 0; i < dataLength; i++) EEPROM.write(i + 71, (uint8_t) data.charAt(i));
      s1Notif = data;
      success = true;
    }
    else if (type == "s2:") {
      EEPROM.write(107, dataLength);

      for (byte i = 0; i < dataLength; i++) EEPROM.write(i + 108, (uint8_t) data.charAt(i));
      s2Notif = data;
      success = true;
    }
    else if (type == "s3:") {
      EEPROM.write(144, dataLength);

      for (byte i = 0; i < dataLength; i++) EEPROM.write(i + 145, (uint8_t) data.charAt(i));
      s3Notif = data;
      success = true;
    }
    else if (type == "s4:") {
      EEPROM.write(181, dataLength);

      for (byte i = 0; i < dataLength; i++) EEPROM.write(i + 182, (uint8_t) data.charAt(i));
      s4Notif = data;
      success = true;
    }
	else if (type == "F1:" && dataLength < 9) {
      EEPROM.write(330, dataLength);

      for (byte i = 0; i < dataLength; i++) EEPROM.write(i + 331, (uint8_t) data.charAt(i));
      success = true;
    }
	else if (type == "F2:" && dataLength < 9) {
      EEPROM.write(340, dataLength);

      for (byte i = 0; i < dataLength; i++) EEPROM.write(i + 341, (uint8_t) data.charAt(i));
      success = true;
    }
	else if (type == "F3:" && dataLength < 9) {
      EEPROM.write(350, dataLength);

      for (byte i = 0; i < dataLength; i++) EEPROM.write(i + 351, (uint8_t) data.charAt(i));
      success = true;
    }
	else if (type == "F4:" && dataLength < 9) {
      EEPROM.write(360, dataLength);

      for (byte i = 0; i < dataLength; i++) EEPROM.write(i + 361, (uint8_t) data.charAt(i));
      success = true;
    }
	else if (type == "F5:" && dataLength < 9) {
      EEPROM.write(370, dataLength);

      for (byte i = 0; i < dataLength; i++) EEPROM.write(i + 371, (uint8_t) data.charAt(i));
      success = true;
    }
  }

  EEPROM.commit();
  delay(10);

  return success;
}

void EepromLoad()
{
#ifdef NEW_NAME
  EepromWrite("nm:", NEW_NAME);
#endif

#ifdef MY_AUTH
  EepromWrite("tk:", MY_AUTH);
#endif

  unitName = EepromRead("nm:");

  s1Notif = EepromRead("s1:");
  s2Notif = EepromRead("s2:");
  s3Notif = EepromRead("s3:");
  s4Notif = EepromRead("s4:");

  relay01Timeout = EEPROM.read(321);
  relay02Timeout = EEPROM.read(322);
  relay03Timeout = EEPROM.read(323);
  relay04Timeout = EEPROM.read(324);

  EepromRead("tk:");
}

// get update over the internet
void OTI()
{
  terminal.println(getTime() + "OTI started!");
  terminal.flush();
	  
  if (!firstRun) {
    Blynk.virtualWrite(V_MESSAGE, getTime() + "OTI...");

    EEPROM.write(300, 4);                     // save restart cause in eeprom
    EEPROM.commit();
    delay(10);

    delay(random(100));                       // delay to distribute simultaneous connections to the oti server
    t_httpUpdate_return ret = ESPhttpUpdate.update(OTI_ADDRESS + mcuType);

    switch (ret) {
      case HTTP_UPDATE_FAILED:
        Blynk.virtualWrite(V_MESSAGE, getTime(1), ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
		
		terminal.println(getTime() + ESPhttpUpdate.getLastErrorString().c_str());
        terminal.flush();
        
		EEPROM.write(300, 5);                 // save restart cause in eeprom (reset to: blackout/other)
        EEPROM.commit();
        delay(10);
		break;

      case HTTP_UPDATE_NO_UPDATES:
        Blynk.virtualWrite(V_MESSAGE, getTime() + "NO UPDATES!");
		
		terminal.println(getTime() + "no updates!");
        terminal.flush();
        break;

      case HTTP_UPDATE_OK:
        Blynk.virtualWrite(V_MESSAGE, getTime() + "OTI OK!");
		
		terminal.println(getTime() + "OTI successful!");
        terminal.flush();
        break;
    }
  }
}

void blinkBlueLed()
{
  digitalWrite(LED_BLUE, ON);
  delay(10);
  digitalWrite(LED_BLUE, OFF);
}

// ISR function for buttons, do not use delays here !!!
void button1ISR()
{
  if (millis() > relay01Timestamp + 500) {            // debounce button
    digitalWrite(RELAY_1, !digitalRead(RELAY_1));
    relay01Timestamp = millis();
    channelToSync = 1;
	
	if (unitName == "027") {          // not nice!!!! better idea??????? (needed for central heating unit)
		snooze14 = true;
        snooze14Timeout = millis() + SNOOZE_TIMEOUT;
    }
  }
}

/*
void button2ISR()
{
  if (millis() > relay02Timestamp + 500) {
    digitalWrite(RELAY_2, !digitalRead(RELAY_2));
    relay02Timestamp = millis();
    channelToSync = 2;
  }
}

void button3ISR()
{
  if (millis() > relay03Timestamp + 500) {
    digitalWrite(RELAY_3, !digitalRead(RELAY_3));
    relay03Timestamp = millis();
    channelToSync = 3;
  }
}
*/

void button4ISR()
{
  if (millis() > relay04Timestamp + 500) {
    digitalWrite(RELAY_4, !digitalRead(RELAY_4));
    relay04Timestamp = millis();
    channelToSync = 4;
  }
}

void checkFirstRun()
{
  if (firstRun) {
	byte rtcCounter;  
	  
	while (year() < 2019 && rtcCounter < 5) {
      delay(500);
      Blynk.run();
	  delay(100);
	  getTime();
      rtcCounter++;
	  
	  terminal.println("syncing rtc...");
	  terminal.flush();
	}

    if (typeNotSet) Blynk.notify(unitName + " type is not set!");

    if (year() >= 2018) {
      byte causeBin = EEPROM.read(300);  // get restart cause in binary format from eeprom
      String cause = "";

      switch (causeBin) {
        case 1:
          cause = "remote restart";
          break;
        case 2:
          cause = "wifi timeout";
          break;
        case 3:
          cause = "MY_AUTH enabled";
          break;
        case 4:
          cause = "oti performed";
          break;
        case 5:
          cause = "blackout/other";
          break;
        default:
          cause = causeBin;
          break;
      }

      EEPROM.write(300, 5);               // preset restart cause to "blackout/other"
      EEPROM.commit();
      yield();

      getTime();
      firstRun = false;

      Blynk.virtualWrite(V_RESTART_CAUSE, cause + " (" + ESP.getResetReason() + ")");
      Blynk.virtualWrite(V_MESSAGE, getTime() + unitName + " STARTED, v" + VC + VERSION);
      Blynk.virtualWrite(V_MAC, getMAC());

	  terminal.println(" ");
	  terminal.flush();
	  
      terminal.println(getTime());
	  terminal.flush();
	  
      terminal.println("device " + unitName + "." + type + " v" + VC + VERSION + " connected");
      terminal.flush();
	  
	  terminal.println("lib v" BLYNK_VERSION " on " BLYNK_INFO_DEVICE);
      terminal.flush();
	  
	  terminal.println("free RAM: " + String(getRamPr()) + "%");
	  terminal.flush();
	  
	  terminal.println("vcc: " + floatReductor(String(getVcc()), 2) + "v");
	  terminal.flush();
	  
	  terminal.println("connected to: " + WiFi.SSID());
	  terminal.flush();
	  
	  terminal.println("gateway mac: " + WiFi.BSSIDstr());
	  terminal.flush();
	  
	  terminal.println("gateway ip: " + WiFi.gatewayIP().toString());
	  terminal.flush();
	  
	  terminal.println("local ip: " + WiFi.localIP().toString());
	  terminal.flush();
	  
	  terminal.println("restart caused by " + cause + " (" + ESP.getResetReason() + ")");
	  terminal.flush();
	  
#ifdef MY_AUTH
      Blynk.email("mgbiker3@gmail.com", "sonoff nfo", "mac: " + getMAC() + ", token: " + MY_AUTH + ", name: " + unitName + ", type: " + type);
#endif

      yield();
      sendDevices();                      // update sensor values on first connect
    }
  }
}

// check for digital sensors on input pins and init if found
void initDevices()
{
  devicesGpio02.begin();                                     // look for ds18 on esp8285 based devices
  gpio02Devices = devicesGpio02.getDeviceCount();

  if (gpio02Devices != 0) {
    for (byte i = 0; i < gpio02Devices; i++) {
      devicesGpio02.setResolution(oneWireDevices[i], 10);    // set device resolution (9-12 bit)
    }
  }
  else {
    dhtG02.begin();                                          // if no ds18 sensors found on pin 2, probe for dht22

    if (type != 4) {
      devicesGpio04.begin();                                 // look for ds18 on esp8266 based devices
      gpio04Devices = devicesGpio04.getDeviceCount();

      if (gpio04Devices != 0) {
        for (byte i = 0; i < gpio04Devices; i++) {
          devicesGpio04.setResolution(oneWireDevices[i], 10);    // set device resolution (9-12 bit)
        }
      }
      else {
        dhtG04.begin();                                          // if no ds18 sensors found on pin 14, probe for dht22

        devicesGpio14.begin();                                   // look for ds18 on esp8266 based devices
        gpio14Devices = devicesGpio14.getDeviceCount();

        if (gpio14Devices != 0) {
          for (byte i = 0; i < gpio14Devices; i++) {
            devicesGpio14.setResolution(oneWireDevices[i], 10);  // set device resolution (9-12 bit)
          }
        }
        else dhtG14.begin();                                     // if no ds18 sensors found on pin 14, probe for dht22
      }
    }
  }
}
  
/*
     Mode     Res.       Conversion time
      9 bits  0.5   °C    94 ms
     10 bits  0.25  °C   188 ms
     11 bits  0.125 °C   375 ms
     12 bits  0.0625°C   750 ms
*/

void setType()
{
#ifdef TYPE
  EEPROM.write(301, TYPE);
  EEPROM.commit();
#endif

  type = EEPROM.read(301);

  pinMode(GPIO_02, INPUT_PULLUP);

  pinMode(LED_BLUE, OUTPUT);
  digitalWrite(LED_BLUE, OFF);

  switch (type) {
    case 1:
      mcuType = "ESP8266.bin";                                // for all ESP8266 based devices, inlcuding wemos

      pinMode(GPIO_04, INPUT_PULLUP);
      pinMode(GPIO_14, INPUT_PULLUP);

      pinMode(RELAY_1, OUTPUT);

      digitalWrite(RELAY_1, EEPROM.read(E_RELAY_1));          // restore relay state

      attachInterrupt(BUTTON_1, button1ISR, FALLING);
      break;
	  
	case 2:                                                   // for sonoff basic with DOUT!!!
      mcuType = "ESP8266DOUT.bin";

      pinMode(GPIO_04, INPUT_PULLUP);
      pinMode(GPIO_14, INPUT_PULLUP);

      pinMode(RELAY_1, OUTPUT);

      digitalWrite(RELAY_1, EEPROM.read(E_RELAY_1));          // restore relay state

      attachInterrupt(BUTTON_1, button1ISR, FALLING);
      break;
	  
    case 4:
      mcuType = "ESP8566.bin";                                     // for 4ch v2

	  //pinMode( 9, INPUT);
      //pinMode(10, INPUT);
	  
      pinMode(GPIO_16, INPUT);

      pinMode(RELAY_1, OUTPUT);
      pinMode(RELAY_2, OUTPUT);
      pinMode(RELAY_3, OUTPUT);
      pinMode(RELAY_4, OUTPUT);
	  
      digitalWrite(RELAY_1, EEPROM.read(E_RELAY_1));
      digitalWrite(RELAY_2, EEPROM.read(E_RELAY_2));
      digitalWrite(RELAY_3, EEPROM.read(E_RELAY_3));
      digitalWrite(RELAY_4, EEPROM.read(E_RELAY_4));

      attachInterrupt(BUTTON_1, button1ISR, FALLING);
      //attachInterrupt(BUTTON_2, button2ISR, FALLING);
      //attachInterrupt(BUTTON_3, button3ISR, FALLING);
      attachInterrupt(BUTTON_4, button4ISR, FALLING);
      break;
    default:
      typeNotSet = true;
      mcuType = "NA";
      break;
  }

  delay(1);
}

void syncBlynk()   // sync relay state to blynk button
{	
  static bool oldRELAY_1 = !digitalRead(RELAY_1);
  static bool oldRELAY_2 = !digitalRead(RELAY_2);
  static bool oldRELAY_3 = !digitalRead(RELAY_3);
  static bool oldRELAY_4 = !digitalRead(RELAY_4);

  if (digitalRead(RELAY_1) != oldRELAY_1) {
    Blynk.virtualWrite(V_RELAY_1_STATE, digitalRead(RELAY_1));
    oldRELAY_1 = digitalRead(RELAY_1);
  }

  if (digitalRead(RELAY_2) != oldRELAY_2) {
    Blynk.virtualWrite(V_RELAY_2_STATE, digitalRead(RELAY_2));
    oldRELAY_2 = digitalRead(RELAY_2);
  }

  if (digitalRead(RELAY_3) != oldRELAY_3) {
    Blynk.virtualWrite(V_RELAY_3_STATE, digitalRead(RELAY_3));
    oldRELAY_3 = digitalRead(RELAY_3);
  }

  if (digitalRead(RELAY_4) != oldRELAY_4) {
    Blynk.virtualWrite(V_RELAY_4_STATE, digitalRead(RELAY_4));
    oldRELAY_4 = digitalRead(RELAY_4);
  }
}

void syncEeprom()  // save relay state to eeprom
{
  switch (channelToSync) {
    case 1:
      EEPROM.write(E_RELAY_1, digitalRead(RELAY_1));
      EEPROM.commit();
      break;
    case 2:
      EEPROM.write(E_RELAY_2, digitalRead(RELAY_2));
      EEPROM.commit();
      break;
    case 3:
      EEPROM.write(E_RELAY_3, digitalRead(RELAY_3));
      EEPROM.commit();
      break;
    case 4:
      EEPROM.write(E_RELAY_4, digitalRead(RELAY_4));
      EEPROM.commit();
      break;
    default:
      break;
  }

  delay(10);
  channelToSync = 0;
}

void updateLabels()
{
  Blynk.setProperty(V_RELAY_1_STATE,  "label", unitName + " RELAY 1");    // relay button on / off widget
  Blynk.setProperty(V_RELAY_2_STATE,  "label", unitName + " RELAY 2");
  Blynk.setProperty(V_RELAY_3_STATE,  "label", unitName + " RELAY 3");
  Blynk.setProperty(V_RELAY_4_STATE,  "label", unitName + " RELAY 4");

  Blynk.setProperty(V_GPIO_02_LED,    "label", unitName + " S1");         // activity led widget
  Blynk.setProperty(V_GPIO_04_LED,    "label", unitName + " S2");
  Blynk.setProperty(V_GPIO_14_LED,    "label", unitName + " S3");
  Blynk.setProperty(V_GPIO_16_LED,    "label", unitName + " S4");

  yield();
  Blynk.run();

  Blynk.setProperty(V_GPIO_02_NOTIFY, "label", unitName + " NOTIFY S1");  // notification on / off button widget
  Blynk.setProperty(V_GPIO_04_NOTIFY, "label", unitName + " NOTIFY S2");
  Blynk.setProperty(V_GPIO_14_NOTIFY, "label", unitName + " NOTIFY S3");
  Blynk.setProperty(V_GPIO_16_NOTIFY, "label", unitName + " NOTIFY S4");

  Blynk.setProperty(V_GPIO_02_SENS01, "label", unitName + " S1");         // sensors display widget
  Blynk.setProperty(V_GPIO_04_SENS01, "label", unitName + " S2");
  Blynk.setProperty(V_GPIO_14_SENS01, "label", unitName + " S3");
  Blynk.setProperty(V_GPIO_16_SENS01, "label", unitName + " S4");
}

void wifiSelector()
{
  // ADD NEW CLIENTS HERE:
  wifiMulti.addAP("bubu"         , "raisaeleea");
  wifiMulti.addAP("DIGI-uT9H"    , "3WHDAM2h");
  wifiMulti.addAP("default"      , "123456789");
  wifiMulti.addAP("mg2.4"        , "lonyaL333mg2.4");
  wifiMulti.addAP("Rompac"       , OPEN_WIFI);
  wifiMulti.addAP("Intern"       , "wilddavid21A");
  wifiMulti.addAP("Skipass"      , "skipasswifi");
  wifiMulti.addAP("GuestSkipass" , OPEN_WIFI);
  wifiMulti.addAP("dungeon"      , "M3t4ll1c4");
  wifiMulti.addAP("Rompac Office", "tahografe");
  wifiMulti.addAP("NETJUNIOR"    , "transilvania");

  unsigned long startWiFi = millis();

  while (wifiMulti.run() != WL_CONNECTED) {          // connect to the strongest network
    digitalWrite(LED_BLUE, OFF);
    delay(400);
    digitalWrite(LED_BLUE, ON);
    delay(100);

    //Serial.println(millis());
    //Serial.println("in wifi loop");

    if (millis() > startWiFi + WIFI_TIMEOUT) {
      //Serial.println("no wifi");
      break;
    }
  }

  if (wifiMulti.run() == WL_CONNECTED) {
	//Serial.println("connected to wifi");
	  
    for (byte i = 0; i < 10; i++) {
      blinkBlueLed();   // signal if connected to wifi
      delay(50);
    }
  }
}

/*
  -30 dBm: amazing  (unlikely in real life)
  -67 dBm: strong   (minimum for real time hd streaming)
  -70 dBm: okay     (minimum for reliable packet delivery)
  -80 dBm: weak     (minimum signal strength for basic connectivity. packet delivery may be unreliable)
  -90 dBm: unusable (any functionality is highly unlikely)
*/

BLYNK_WRITE(V_RELAY_1_STATE)                        // ALL BLYNK WRITES COME HERE !!!
{
  bool buttonState = param.asInt();
/*
  if (BUTTON_PROTECTED_MODE) {                      // don't allow 2 relays in the same state
    if ((digitalRead(RELAY_2) ==  buttonState) ||
        (digitalRead(RELAY_3) ==  buttonState) ||
        (digitalRead(RELAY_4) ==  buttonState)) {

      Blynk.notify(unitName + " ACTION FORBIDDEN! ");

      return;
    }
  }
*/
  relay01Timestamp = millis();

  if (buttonState) {
    digitalWrite(RELAY_1, HIGH);
    EEPROM.write(E_RELAY_1, 1);                     // save relay state to eeprom
  }

  else {
    digitalWrite(RELAY_1, LOW);
    EEPROM.write(E_RELAY_1, 0);
  }

  EEPROM.commit();
}

BLYNK_WRITE(V_RELAY_2_STATE)                        // ALL BLYNK WRITES COME HERE !!!
{
  bool buttonState = param.asInt();

  /*
  if (BUTTON_PROTECTED_MODE) {                      // don't allow 2 relays in the same state
    if ((digitalRead(RELAY_1) ==  buttonState) ||
        (digitalRead(RELAY_3) ==  buttonState) ||
        (digitalRead(RELAY_4) ==  buttonState)) {

      Blynk.notify(unitName + " ACTION FORBIDDEN! ");

      return;
    }
  }
*/
  relay02Timestamp = millis();

  if (buttonState) {
    digitalWrite(RELAY_2, HIGH);
    EEPROM.write(E_RELAY_2, 1);                     // save relay state to eeprom
  }

  else {
    digitalWrite(RELAY_2, LOW);
    EEPROM.write(E_RELAY_2, 0);
  }

  EEPROM.commit();
}

BLYNK_WRITE(V_RELAY_3_STATE)                        // ALL BLYNK WRITES COME HERE !!!
{
  bool buttonState = param.asInt();
/*
  if (BUTTON_PROTECTED_MODE) {                      // don't allow 2 relays in the same state
    if ((digitalRead(RELAY_1) ==  buttonState) ||
        (digitalRead(RELAY_2) ==  buttonState) ||
        (digitalRead(RELAY_4) ==  buttonState)) {

      Blynk.notify(unitName + " ACTION FORBIDDEN! ");

      return;
    }
  }
*/
  relay03Timestamp = millis();

  if (buttonState) {
    digitalWrite(RELAY_3, HIGH);
    EEPROM.write(E_RELAY_3, 1);                     // save relay state to eeprom
  }

  else {
    digitalWrite(RELAY_3, LOW);
    EEPROM.write(E_RELAY_3, 0);
  }

  EEPROM.commit();
}

BLYNK_WRITE(V_RELAY_4_STATE)                        // ALL BLYNK WRITES COME HERE !!!
{
  bool buttonState = param.asInt();
/*
  if (BUTTON_PROTECTED_MODE) {                      // don't allow 2 relays in the same state
    if ((digitalRead(RELAY_1) ==  buttonState) ||
        (digitalRead(RELAY_2) ==  buttonState) ||
        (digitalRead(RELAY_3) ==  buttonState)) {

      Blynk.notify(unitName + " ACTION FORBIDDEN! ");

      return;
    }
  }
*/
  relay04Timestamp = millis();

  if (buttonState) {
    digitalWrite(RELAY_4, HIGH);
    EEPROM.write(E_RELAY_4, 1);                     // save relay state to eeprom
  }

  else {
    digitalWrite(RELAY_4, LOW);
    EEPROM.write(E_RELAY_4, 0);
  }

  EEPROM.commit();
}

BLYNK_WRITE(V_GPIO_02_NOTIFY)              // enable / disable notification for respective gpio
{
  gpio02NotifyEnabled = param.asInt();
}

BLYNK_WRITE(V_GPIO_04_NOTIFY)
{
  gpio04NotifyEnabled = param.asInt();
}

BLYNK_WRITE(V_GPIO_14_NOTIFY)
{
  gpio14NotifyEnabled = param.asInt();
}

BLYNK_WRITE(V_GPIO_16_NOTIFY)
{
  gpio16NotifyEnabled = param.asInt();
}

BLYNK_WRITE(V_SNOOZE02_BUTTON)
{
  snooze02 = param.asInt();
  if (snooze02) snooze02Timeout = millis() + SNOOZE_TIMEOUT;
}

BLYNK_WRITE(V_SNOOZE04_BUTTON)
{
  snooze04 = param.asInt();
  if (snooze04) snooze04Timeout = millis() + SNOOZE_TIMEOUT;  // if snooze button is pressed, pause notification for given time
}

BLYNK_WRITE(V_SNOOZE14_BUTTON)
{
  snooze14 = param.asInt();
  if (snooze14) snooze14Timeout = millis() + SNOOZE_TIMEOUT;
  
  gpio14notifyCounter = 0;
}

BLYNK_WRITE(V_SNOOZE16_BUTTON)
{
  snooze16 = param.asInt();
  if (snooze16) snooze16Timeout = millis() + SNOOZE_TIMEOUT;
}

BLYNK_WRITE(V_ALL_NOTIFY)                  // toggle ALL notifications
{
  if (!param.asInt()) {
    gpio02NotifyEnabled = false;
    gpio04NotifyEnabled = false;
    gpio14NotifyEnabled = false;
    gpio16NotifyEnabled = false;

    Blynk.virtualWrite(V_GPIO_02_NOTIFY, 0);
    Blynk.virtualWrite(V_GPIO_04_NOTIFY, 0);
    Blynk.virtualWrite(V_GPIO_14_NOTIFY, 0);
    Blynk.virtualWrite(V_GPIO_16_NOTIFY, 0);
  }
  else {
    gpio02NotifyEnabled = true;
    gpio04NotifyEnabled = true;
    gpio14NotifyEnabled = true;
    gpio16NotifyEnabled = true;

    Blynk.virtualWrite(V_GPIO_02_NOTIFY, 1);
    Blynk.virtualWrite(V_GPIO_04_NOTIFY, 1);
    Blynk.virtualWrite(V_GPIO_14_NOTIFY, 1);
    Blynk.virtualWrite(V_GPIO_16_NOTIFY, 1);
  }
}

BLYNK_WRITE(V_GET_UPDATE)                  // check for oti update
{
  if (param.asInt()) OTI();
}

BLYNK_WRITE(V_UPDATE_TOKEN)                // check for new token
{
  if (EepromWrite("tk:", param.asStr())) {
    Blynk.virtualWrite(V_MESSAGE, getTime() + "TOKEN UPDATED: " + param.asStr());
    Blynk.virtualWrite(V_GPIO_02_NOTIFY, 0);
    Blynk.virtualWrite(V_GPIO_04_NOTIFY, 0);
    Blynk.virtualWrite(V_GPIO_14_NOTIFY, 0);
    Blynk.virtualWrite(V_GPIO_16_NOTIFY, 0);
    delay(5);

#ifdef MY_AUTH
    EEPROM.write(300, 3);                  // save restart cause in eeprom
    EEPROM.commit();
    delay(100);

    blinkBlueLed();
    ESP.restart();
    delay(1000);
#endif
  }
  else Blynk.virtualWrite(V_MESSAGE, getTime() + "TOKEN UPDATE FAILED!");
}

/*
  BLYNK_WRITE(V_UPDATE_NAME)              // check for new name
  {
  if (EepromWrite("nm:", param.asStr())) {
    updateLabels();
    Blynk.virtualWrite(V_MESSAGE, getTime() + "LABELS UPDATED TO: " + unitName);
  }
  else Blynk.virtualWrite(V_MESSAGE, getTime() + "NAME NOT UPDATED. LENGTH MISMATCH!");
  }
*/

BLYNK_WRITE(V_RESTART)                  // remote restart
{
  if (param.asInt()) {
    EEPROM.write(300, 1);               // save restart cause in eeprom
    EEPROM.commit();

    Blynk.virtualWrite(V_MESSAGE, getTime() + "REMOTE RESTART...");

    delay(1000);
    ESP.restart();
    delay(1000);
    ESP.reset();
    delay(1000);
    while (1) {}
    delay(1000);
  }
}

BLYNK_WRITE(V_SET_TYPE)                  // get sonoff type
{
  EEPROM.write(301, param.asInt());      // save type to eeprom
  EEPROM.commit();
  yield();
}

BLYNK_WRITE(V_TERMINAL)                  // update unit name
{
  String incomingData = param.asStr();

  if (incomingData.length() > 4 && EepromWrite(incomingData.substring(0, 3), incomingData.substring(4))) {
    terminal.println(" ");
    terminal.flush();
	terminal.println("OK, set to: " + incomingData.substring(4));
    terminal.flush();

    //updateLabels();
  }
  else if (incomingData == "vcc") {
	  terminal.println("vcc: " + String(getVcc()) + "v");
      terminal.flush();
  }
  else if (incomingData == "ram") {
	  terminal.println("free ram: " + String(getRamPr()) + "%");
      terminal.flush();
  }
  else {
	terminal.println(" ");
    terminal.flush();
    terminal.println("try one of these:");
	terminal.flush();
    //terminal.println("nm: set name");
	//terminal.flush();
    terminal.println("s1: set notification for s1 \n(respective s2, s3, s4)");
    terminal.flush();
	terminal.println("vcc: get mcu voltage");
    terminal.flush();
	terminal.println("ram: get free memory %");
    terminal.flush();
  }
}

BLYNK_CONNECTED()
{
  //Blynk.syncAll();

#ifdef NEW_NAME
  //updateLabels();
#endif

  Blynk.virtualWrite(V_GET_UPDATE, 0);  // create object for OTI virtual pin
  
  Blynk.syncVirtual(V98, V99, V100, V101, V102, V103, V104, V105, V106, V107, V108, V109, 
                    V110, V111, V112, V113, V114, V115, V116,
                    V_GPIO_02_NOTIFY, V_GPIO_04_NOTIFY, V_GPIO_14_NOTIFY, V_GPIO_16_NOTIFY,
                    V_SNOOZE02_BUTTON, V_SNOOZE04_BUTTON, V_SNOOZE14_BUTTON, V_SNOOZE16_BUTTON);
}

void setup()
{
/*
  Serial.begin(115200);
  Serial.println();
  Serial.println("serial ready");
  Serial.println();
*/

  EEPROM.begin(512);                                 // init eeprom

  setType();                                         // set sonoff type and init pins based on sonoff type
  EepromLoad();                                      // write / load custom values from eeprom
  
  //ArduinoOTA.setPort(8266);                        // port defaults to 8266
  
  char unitNameChar[5];
  unitName.toCharArray(unitNameChar, 5);
  
  ArduinoOTA.setHostname(unitNameChar);
  ArduinoOTA.setPassword((const char *)OTA_PWD);
  
  initDevices();                                     // check for digital sensors and init if found
  
  wifiSelector();                                    // set wifi environment (home / production)
  
  
  digitalWrite(LED_BLUE, ON);                        // signal with solid blue the begin of blynk connect
  
  //Serial.print(F("token: "));
  //Serial.println(auth);
  
  Blynk.config(auth, server);
  checkBlynk();
  digitalWrite(LED_BLUE, OFF);                       // when the blue led is off, the device is connected to blynk server

  ArduinoOTA.begin();
  rtc.begin();

  timer.setInterval(   800, sendSystemPramaters);   // send system parameters to server
  timer.setInterval(   500, checkInputs);           // check digital pins state and push to server if changed
  timer.setInterval(    53, syncBlynk);             // sync button states to blynk
  timer.setInterval(   202, syncEeprom);            // sync relay states to eeprom
  timer.setInterval(30070L, blinkBlueLed);          // flash blue led every x seconds to signal unit is working
  timer.setInterval(60000L, sendDevices);           // send peripheral device / sensor data to server
  timer.setInterval(SNOOZE_CHECK, snooze);          // how often to check for snooze timeout
  timer.setInterval(BLYNK_CONNECTION_INTERVAL, checkBlynk);
  //timer.setInterval(  2000, serialEvent);           // redirect serial debug data to terminal widget (experimental)
  
  personalisedSetup();  // extra setup functions in personalized version (default: empty function)
  
  //Serial.println(F("setup finished"));
}

// needed to handle lost wifi/server connections (to prevent code locks)
void blynkHandler()
{
  static unsigned long lastConnected;

  if (Blynk.connected()) {                      // connected to blynk Server
    checkFirstRun();

    //digitalWrite(LED_BLUE, ON);               // flash blue led (show network activity)
    Blynk.run();                                // run blynk activities

    digitalWrite(LED_BLUE, OFF);                // turn off Blue led
    lastConnected = millis();
  }
  else {                                        // not connected to blynk server
    digitalWrite(LED_BLUE, ON);                 // turn on Blue led
    //Blynk.connect();                          // no longer used! - checkBlynk() used instead

    if (millis() > (lastConnected + BLYNK_WDT)) {
      EEPROM.write(300, 2);                     // save restart cause in eeprom
      EEPROM.commit();
      delay(100);

      ESP.restart();                            // if timeout, restart system
      delay(1000);

      while (1) {}                              // just an alternative restart method, by wdt
      delay(1000);
    }
  }
}
