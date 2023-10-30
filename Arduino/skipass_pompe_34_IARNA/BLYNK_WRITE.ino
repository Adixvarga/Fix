// get incoming data from blynk server

BLYNK_CONNECTED()
{
  Blynk.syncAll();
  widgetRtc.begin();
}


BLYNK_WRITE(V_RESTART)                  // remote restart
{
  if (param.asInt()) {
    Blynk.virtualWrite(V_MESSAGE, getTime() + "REMOTE RESTART...");
    terminal.println(getTime() + UNIT_NAME + ": REMOTE RESTART INIT...");
    terminal.flush();

    blynkHandler();

    WDTreset();
  }
}


BLYNK_WRITE(V_SP_THS)
{
  spThreshold = param.asInt();
  setSetPoint();
  timeTable();
}

BLYNK_WRITE(V_T_BOILER_TARGET)
{
  boilerTarget = param.asInt();
}

BLYNK_WRITE(V_T_BOILER_THS)
{
  boilerThreshold = param.asInt();
}

BLYNK_WRITE(V_TARGET_POOL)
{
  poolTargetTemp = param.asFloat();
}


// segmetned switches:

BLYNK_WRITE(V_P_CENT_EL)
{
  modeCentEl = param.asInt();

  if      (modeCentEl == 1) digitalWrite(P_CENT_EL, RELAY_OFF);
  else if (modeCentEl == 3) digitalWrite(P_CENT_EL, RELAY_ON);
}


BLYNK_WRITE(V_P_BOILER)
{
  modeBoiler = param.asInt();

  if      (modeBoiler == 1) digitalWrite(P_BOILER, RELAY_OFF);
  else if (modeBoiler == 3) digitalWrite(P_BOILER, RELAY_ON);
}

BLYNK_WRITE(V_P_CORP_A)
{
  modeCorpA = param.asInt();

  if      (modeCorpA == 1) digitalWrite(P_CORP_A, RELAY_OFF);
  else if (modeCorpA == 3) digitalWrite(P_CORP_A, RELAY_ON);
}

BLYNK_WRITE(V_P_CORP_B)
{
  modeCorpB = param.asInt();

  if      (modeCorpB == 1) digitalWrite(P_CORP_B, RELAY_OFF);
  else if (modeCorpB == 3) digitalWrite(P_CORP_B, RELAY_ON);
}

BLYNK_WRITE(V_P_CORP_C)
{
  modeCorpC = param.asInt();

  if      (modeCorpC == 1) digitalWrite(P_CORP_C, RELAY_OFF);
  else if (modeCorpC == 3) digitalWrite(P_CORP_C, RELAY_ON);
}

BLYNK_WRITE(V_P_CAMERE_B)
{
  modeCamereB = param.asInt();

  if      (modeCamereB == 1) digitalWrite(P_CAMERE_B, RELAY_OFF);
  else if (modeCamereB == 3) digitalWrite(P_CAMERE_B, RELAY_ON);
}

BLYNK_WRITE(V_P_CASUTA)
{
  modeCasuta = param.asInt();

  if      (modeCasuta == 1) digitalWrite(P_CASUTA, RELAY_OFF);
  else if (modeCasuta == 3) digitalWrite(P_CASUTA, RELAY_ON);
}

BLYNK_WRITE(V_P_PARDOSEA)
{
  modePardosea = param.asInt();

  if      (modePardosea == 1) digitalWrite(P_PARDOSEA, RELAY_OFF);
  else if (modePardosea == 3) digitalWrite(P_PARDOSEA, RELAY_ON);
}

BLYNK_WRITE(V_P_PISCINA)
{
  modePiscina = param.asInt();

  if      (modePiscina == 1) {
    digitalWrite(P_PISCINA, RELAY_OFF);
    poolEnabled = false;
  }
  else if (modePiscina == 2) {
    poolEnabled = true;
    piscina();
  }
  else if (modePiscina == 3) {
    digitalWrite(P_PISCINA, RELAY_ON);
    poolEnabled = true;
  }
}

BLYNK_WRITE(V_P_SCHIURI)
{
  modeSchiuri = param.asInt();

  if      (modeSchiuri == 1) digitalWrite(P_SCHIURI, RELAY_OFF);
  else if (modeSchiuri == 3) digitalWrite(P_SCHIURI, RELAY_ON);
}

BLYNK_WRITE(V_P_CALD_1)
{
  modePCG1 = param.asInt();

  if      (modePCG1 == 1) digitalWrite(P_CALD_1, RELAY_OFF);
  else if (modePCG1 == 3) digitalWrite(P_CALD_1, RELAY_ON);
}

BLYNK_WRITE(V_P_CALD_2)
{
  modePCG2 = param.asInt();

  if      (modePCG2 == 1) digitalWrite(P_CALD_2, RELAY_OFF);
  else if (modePCG2 == 3) digitalWrite(P_CALD_2, RELAY_ON);
}

BLYNK_WRITE(V_P_CALD_3)
{
  modePCG3 = param.asInt();

  if      (modePCG3 == 1) digitalWrite(P_CALD_3, RELAY_OFF);
  else if (modePCG3 == 3) digitalWrite(P_CALD_3, RELAY_ON);
}

BLYNK_WRITE(V_P_CALD_4)
{
  modePCG4 = param.asInt();

  if      (modePCG4 == 1) digitalWrite(P_CALD_4, RELAY_OFF);
  else if (modePCG4 == 3) digitalWrite(P_CALD_4, RELAY_ON);
}

BLYNK_WRITE(V_TOGGLE_HIDRO)
{
  toggleHidro = param.asInt() * 60000;
}

BLYNK_WRITE(V_DEBUG_EN)
{
  debugMode = param.asInt();
}

BLYNK_WRITE(V_TIMETABLE_HIDRO)
{
  TimeInputParam t(param);

  if (t.hasStartTime()) {                            // Process start time
    hidroStartH = t.getStartHour();
    hidroStartM = t.getStartMinute();
  }
  else if (t.isStartSunrise()) {}
  else if (t.isStartSunset())  {}

  if (t.hasStopTime()) {                             // Process stop time
    hidroStopH = t.getStopHour();
    hidroStopM = t.getStopMinute();
  }
  else if (t.isStopSunrise()) {}
  else if (t.isStopSunset())  {}

  for (byte i = 1; i <= 7; i++) {                    // Process weekdays (1. Mon, 2. Tue, 3. Wed)
    if (t.isWeekdaySelected(i)) hidroWeekdaySelected[i] = true;
    else hidroWeekdaySelected[i] = false;
  }
}

BLYNK_WRITE(V_TIMETABLE_USCATOR)
{
  TimeInputParam t(param);

  if (t.hasStartTime()) {                            // Process start time
    uscatorStartH = t.getStartHour();
    uscatorStartM = t.getStartMinute();
  }
  else if (t.isStartSunrise()) {}
  else if (t.isStartSunset())  {}

  if (t.hasStopTime()) {                             // Process stop time
    uscatorStopH = t.getStopHour();
    uscatorStopM = t.getStopMinute();
  }
  else if (t.isStopSunrise()) {}
  else if (t.isStopSunset())  {}

  for (byte i = 1; i <= 7; i++) {                    // Process weekdays (1. Mon, 2. Tue, 3. Wed)
    if (t.isWeekdaySelected(i)) uscatorWeekdaySelected[i] = true;
    else uscatorWeekdaySelected[i] = false;
  }
}
