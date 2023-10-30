void checkFirstRun()
{
  if (firstRun) {
    byte widgetRtcCounter;

    while (year() < 2018 && widgetRtcCounter < 5) {
      widgetRtc.begin();
      delay(500);
      Blynk.run();
      delay(100);
      getTime();

      widgetRtcCounter++;

      terminal.println("syncing widgetRtc...");
      terminal.flush();
      Blynk.run();
    }

    if (year() > 2018) {
      getTime();
      firstRun = false;

      Blynk.virtualWrite(V_MESSAGE, getTime() + " STARTED, v" + VERSION);
      Blynk.virtualWrite(V_VCC, "-");
      Blynk.virtualWrite(V_RAM, "-");
      
      rtc.adjust(DateTime(year(), month(), day(), hour(), minute(), second()));  // if there is a correct server time, adjust the hw rtc

      terminal.println(" ");
      terminal.flush();

      terminal.println(getTime());
      terminal.flush();

      terminal.println("pompe incalzire v" VERSION " connected");
      terminal.flush();

      terminal.println("arduino IP: " + ip2String(arduino_ip));
      terminal.flush();

      terminal.println("gateway IP: " + ip2String(gateway_ip));
      terminal.flush();

      terminal.println("lib v" BLYNK_VERSION " on " BLYNK_INFO_DEVICE);
      terminal.flush();

      Blynk.syncAll();
      
      sendDevices();                      // update sensor values on first connect
      boiler();
      checkTimers();
      timeTable();
      piscina();
 
    }
  }
}
