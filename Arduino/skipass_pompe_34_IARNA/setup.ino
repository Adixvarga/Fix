void setup()
{
  MCUSR = 0;
  // wdt_disable();

  // https://tomblanch.wordpress.com/2014/02/26/resetting-an-arduino-from-software/

  // handle stopping / resetting the watchdog timer to prevent infinite loops:
  WDTCSR |= _BV(WDCE) | _BV(WDE);  // Write logical one to WDCE and WDE
  WDTCSR = 0;                      // Keep old prescaler setting to prevent unintentional time-out

  //pinMode(22, INPUT_PULLUP);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  pinMode(19, OUTPUT);       // widgetRtc module gnd
  digitalWrite(19, LOW);
  delay(100);
  pinMode(18, OUTPUT);       // widgetRtc module vcc
  digitalWrite(18, HIGH);

  pinMode     (SDCARD_CS, OUTPUT);
  digitalWrite(SDCARD_CS, HIGH);  // Deselect the SD card

  Serial.begin(115200);

  widgetRtcSetup();

  printVersionInfo();

  for (byte input = 2; input < 18; input++) {                    // setup inputs
    if (input ==  4) continue;
    if (input == 13) continue;

    pinMode(input, INPUT_PULLUP);
  }

  if (!digitalRead(2)) debugMode = true;

  for (byte relay = 27; relay < 47; relay++) {                   // setup relays as outputs
    pinMode(relay, OUTPUT);

    if (debugMode) {
      digitalWrite(relay, RELAY_ON);                                    // check if all relays are working
      delay(500);
    }

    digitalWrite(relay, RELAY_OFF);
  }

  digitalWrite(LED_BUILTIN, HIGH);

Serial.print("using static IP: ");
Serial.println(arduino_ip);




  Ethernet.begin(arduino_mac, arduino_ip, dns_ip, gateway_ip, subnet_mask );  // use manual ethernet config
  Blynk.config(auth, "blynk.NorthBSD.org", 80);

  unsigned long maxMillis = millis() + 10000;                                 // watchdog for connection timeout
  while ((Blynk.connect() == false) && ( millis() <= maxMillis)) {}

  widgetRtc.begin();
  digitalWrite(LED_BUILTIN, LOW);

  sensors.begin();  // startup ds18
  delay(500);

  // locate devices on the bus
  Serial.print("Locating DS18 devices... found ");
  Serial.println(sensors.getDeviceCount(), DEC);

  sensors.setResolution(DS18inside,  TEMPERATURE_PRECISION);
  sensors.setResolution(DS18outside, TEMPERATURE_PRECISION);
  sensors.setResolution(DS18boiler,  TEMPERATURE_PRECISION);
  sensors.setResolution(DS18pool,    TEMPERATURE_PRECISION);
  sensors.setResolution(DS18agent,   TEMPERATURE_PRECISION);
  sensors.setResolution(DS18aux,     TEMPERATURE_PRECISION);

  getDS18temp();
  //delay(1000);

  for (byte sens = 0; sens < TOTAL_DS18; sens++) {
    Serial.println(DS18All[sens]);
  }

  timer.setInterval(   2000L, sendDevices);
  timer.setInterval(  10003L, boiler);
  timer.setInterval(  10000L, checkTimers);
  timer.setInterval(  60001L, timeTable);
  timer.setInterval( 300000L, piscina);
  timer.setInterval(  60000L, getDS18temp);
  timer.setInterval(3600030L, setSetPoint);
}
