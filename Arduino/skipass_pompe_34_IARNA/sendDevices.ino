void sendDevices()
{
  static bool firstNotifyPressureApa = true;
  static bool firstNotifyPressurePiscina = true;
  static bool firstNotifyDS18[TOTAL_DS18] = {true};
  String DS18byName[] = {"boiler", "pool", "outside", "agent", "inside", "aux"};

  //Blynk.virtualWrite(V_VCC, readVCC());
  Blynk.virtualWrite(V_SEND_widgetRtc, getTime());
  Blynk.virtualWrite(V_UPTIME, millis() / 3600000);

  Blynk.virtualWrite(V_PRESS_APA, readPressure(PRESS_APA));
  Blynk.virtualWrite(V_PRESS_PISCINA, readPressure(PRESS_PISCINA));


  if (firstNotifyPressureApa && readPressure(PRESS_APA) < 3) {
    Blynk.notify(UNIT_NAME ": water pressure low! " + String(readPressure(PRESS_APA)) + "bar");
    firstNotifyPressureApa = false;

    terminal.println(getTime() + UNIT_NAME ": water pressure low! " + String(readPressure(PRESS_APA)) + "bar");
    terminal.flush();
  }

  if (firstNotifyPressurePiscina && readPressure(PRESS_PISCINA) > 1) {
    Blynk.notify(UNIT_NAME ": pool pressure high! " + String(readPressure(PRESS_PISCINA)) + "bar");
    firstNotifyPressurePiscina = false;

    terminal.println(getTime() + UNIT_NAME ": pool pressure high! " + String(readPressure(PRESS_PISCINA)) + "bar");
    terminal.flush();
  }

  for (byte sens = 0; sens < TOTAL_DS18; sens++) {
    Blynk.virtualWrite(50 + sens, DS18All[sens]);

    if (DS18All[sens] == -127 && firstNotifyDS18[sens]) {
      firstNotifyDS18[sens] = false;

      Blynk.notify(UNIT_NAME ": " + DS18byName[sens] + ": temp sensor error!");
      terminal.println(getTime() + UNIT_NAME + ": " + DS18byName[sens] + " temp sensor error!");
      terminal.flush();
    }
    else if (DS18All[sens] != -127) firstNotifyDS18[sens] = true;
  }

  LedAlimPost.setValue(digitalRead(IN_ALIM_POST) * 255);
  LedAlimRetea.setValue(digitalRead(IN_ALIM_RETEA) * 255);

  LedPPiscina.setValue(digitalRead(IN_P_PISCINA) * 255);
  LedHidro.setValue(!digitalRead(P_HIDROMASAJ) * 255);
  LedUscator.setValue(!digitalRead(P_USCATOR) * 255);

  //LedBoiler.setValue(!digitalRead(P_BOILER) * 255);
  LedEcoBoiler.setValue(priorityModeBoiler * 255);

  LedPc01.setValue(digitalRead(IN_PC_1)  * 255);
  LedPc02.setValue(digitalRead(IN_PC_2)  * 255);
  LedPc03.setValue(digitalRead(IN_PC_3)  * 255);
  LedPc04.setValue(digitalRead(IN_PC_4)  * 255);
  LedPc05.setValue(digitalRead(IN_PC_5)  * 255);
  LedPc06.setValue(digitalRead(IN_PC_6)  * 255);
  LedPc07.setValue(digitalRead(IN_PC_7)  * 255);
  LedPc08.setValue(digitalRead(IN_PC_8)  * 255);
  LedPc09.setValue(digitalRead(IN_PC_9)  * 255);
  LedPc10.setValue(digitalRead(IN_PC_10) * 255);

  if (!digitalRead(P_BOILER))   Blynk.setProperty(V_P_BOILER, "labels", "boiler: off", "auto / on",  "on");   // update segmented switch labels, according to relay state
  else                          Blynk.setProperty(V_P_BOILER, "labels", "boiler: off", "auto / off", "on");

  if (!digitalRead(P_CORP_A))   Blynk.setProperty(V_P_CORP_A, "labels", "corp a: off", "auto / on",  "on");
  else                          Blynk.setProperty(V_P_CORP_A, "labels", "corp a: off", "auto / off", "on");

  if (!digitalRead(P_CORP_B))   Blynk.setProperty(V_P_CORP_B, "labels", "corp b: off", "auto / on",  "on");
  else                          Blynk.setProperty(V_P_CORP_B, "labels", "corp b: off", "auto / off", "on");

  if (!digitalRead(P_CAMERE_B)) Blynk.setProperty(V_P_CAMERE_B, "labels", "camere b: off", "auto / on",  "on");
  else                          Blynk.setProperty(V_P_CAMERE_B, "labels", "camere b: off", "auto / off", "on");

  if (!digitalRead(P_CORP_C))   Blynk.setProperty(V_P_CORP_C, "labels", "corp c: off", "auto / on",  "on");
  else                          Blynk.setProperty(V_P_CORP_C, "labels", "corp c: off", "auto / off", "on");

  if (!digitalRead(P_CASUTA))   Blynk.setProperty(V_P_CASUTA, "labels", "casuta: off", "auto / on",  "on");
  else                          Blynk.setProperty(V_P_CASUTA, "labels", "casuta: off", "auto / off", "on");

  if (!digitalRead(P_PARDOSEA)) Blynk.setProperty(V_P_PARDOSEA, "labels", "pard: off", "auto / on",  "on");
  else                          Blynk.setProperty(V_P_PARDOSEA, "labels", "pard: off", "auto / off", "on");

  if (!digitalRead(P_PISCINA))  Blynk.setProperty(V_P_PISCINA, "labels", "piscina: off", "auto / on",  "on");
  else                          Blynk.setProperty(V_P_PISCINA, "labels", "piscina: off", "auto / off", "on");

  if (!digitalRead(P_SCHIURI))  Blynk.setProperty(V_P_SCHIURI, "labels", "schiuri: off", "auto / on",  "on");
  else                          Blynk.setProperty(V_P_SCHIURI, "labels", "schiuri: off", "auto / off", "on");

  if (!digitalRead(P_CENT_EL))  Blynk.setProperty(V_P_CENT_EL, "labels", "cent el: off", "auto / on",  "on");
  else                          Blynk.setProperty(V_P_CENT_EL, "labels", "cent el: off", "auto / off", "on");

  if (!digitalRead(P_CALD_1))   Blynk.setProperty(V_P_CALD_1, "labels", "pc g1: off", "auto / on",  "on");
  else                          Blynk.setProperty(V_P_CALD_1, "labels", "pc g1: off", "auto / off", "on");

  if (!digitalRead(P_CALD_2))   Blynk.setProperty(V_P_CALD_2, "labels", "pc g2: off", "auto / on",  "on");
  else                          Blynk.setProperty(V_P_CALD_2, "labels", "pc g2: off", "auto / off", "on");

  if (!digitalRead(P_CALD_3))   Blynk.setProperty(V_P_CALD_3, "labels", "pc g3: off", "auto / on",  "on");
  else                          Blynk.setProperty(V_P_CALD_3, "labels", "pc g3: off", "auto / off", "on");

  if (!digitalRead(P_CALD_4))   Blynk.setProperty(V_P_CALD_4, "labels", "pc g4: off", "auto / on",  "on");
  else                          Blynk.setProperty(V_P_CALD_4, "labels", "pc g4: off", "auto / off", "on");
}
