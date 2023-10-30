void blynkHandler()
{
  static unsigned long lastConnected;

  if (Blynk.connected()) {                      // connected to blynk Server
    checkFirstRun();

    //digitalWrite(LED_BUILTIN, HIGH);            // flash builtin led (show network activity)
    Blynk.run();                                // run blynk activities
    digitalWrite(LED_BUILTIN, LOW);             // turn off builtin led

    lastConnected = millis();
  }
  else {                                        // not connected to blynk server
    Serial.print("Rtc time is:");
    Serial.println(getTime());

    digitalWrite(LED_BUILTIN, HIGH);            // turn on builtin led
    Blynk.connect();                            // no longer used! - checkBlynk() used instead

    if (Blynk.connected()) {
      terminal.println(" ");
      terminal.flush();

      terminal.println(getTime());
      terminal.flush();
      terminal.println("pompe incalzire v" VERSION " RE-connected w/o reset");
      terminal.flush();
    }

    //if (millis() > (lastConnected + BLYNK_WDT)) WDTreset();
  }
}
