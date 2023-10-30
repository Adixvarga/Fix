void boiler()
{
  static bool firstNotify = true;
  static bool prevPumpStates[8];                                       // store pump state before activating boiler priority mode

  float tBoiler = DS18All[0];
  float tAgent  = DS18All[3];
  float activeBoilerTarget = boilerTarget;

  if (digitalRead(sp1Relay)) activeBoilerTarget = boilerTarget - 5.0;
  else activeBoilerTarget = boilerTarget;

  if (tBoiler != -127 && modeBoiler == 2) {                            // only if boiler temp valid, boiler mode is on auto
    firstNotify = true;
    byte i = 0;                                                        // used for indexing pumpstates array

    if (tBoiler > activeBoilerTarget) {                                //  1) if temp boiler is higher than target: turn off boiler pump, set flag false
      boilerNeedsHeat = false;
      digitalWrite(P_BOILER, RELAY_OFF);
    }
    else if (tBoiler <= activeBoilerTarget - 1) {                      // 2) if temp boiler is lower than target: set flag true
      boilerNeedsHeat = true;
      if (tBoiler <= tAgent + 5) digitalWrite(P_BOILER, RELAY_ON);     // 2.a) if temp agent is higher than temp boiler, turn on boiler pump
      if (tBoiler >= tAgent)     digitalWrite(P_BOILER, RELAY_OFF);    // 2.b) if temp agent is lower than temp boiler, turn off boiler pump
    }

    if (tBoiler > boilerThreshold + 2 && priorityModeBoiler) {         // boiler in auto mode, deactivate priority mode
      for (byte pin = 32; pin < 40; pin++) {
        digitalWrite(pin, prevPumpStates[i]);                          // restore relays to thier original state
        i++;
      }
      priorityModeBoiler = false;
    }
    else if (tBoiler <= boilerThreshold && !priorityModeBoiler) {      // boiler in auto mode, activate priority mode
      for (byte pin = 32; pin < 40; pin++) {
        prevPumpStates[i] = digitalRead(pin);                          // save pumps state to array
        i++;

        digitalWrite(pin, RELAY_OFF);                                  // turn off relays
      }
      priorityModeBoiler = true;
    }
  }
  else if (tBoiler == -127 && firstNotify) {
    firstNotify = false;

    Blynk.notify(UNIT_NAME ": boiler temp sensor error! Switching off until valid temp.");

    terminal.println(getTime() + UNIT_NAME + ": boiler temp sensor error! Switching off until valid temp.");
    terminal.flush();

    boilerNeedsHeat = false;
    digitalWrite(P_BOILER, RELAY_OFF);
  }
}
