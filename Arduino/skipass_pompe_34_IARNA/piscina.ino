void piscina()
{
  static bool firstNotify = true;
  float tPool = DS18All[1];

  if (tPool != -127 && modePiscina == 2 && poolEnabled) {
    firstNotify = true;

    if (tPool > poolTargetTemp)              digitalWrite(P_PISCINA, RELAY_OFF);
    else if (tPool <= poolTargetTemp - 0.50) digitalWrite(P_PISCINA, RELAY_ON);
  }
  else if (tPool == -127 && firstNotify) {
    firstNotify = false;

    Blynk.notify(UNIT_NAME ": pool temp sensor error! Switching off until valid temp.");

    terminal.println(getTime() + UNIT_NAME + ": pool temp sensor error! Switching off until valid temp.");
    terminal.flush();

    digitalWrite(P_PISCINA, RELAY_OFF);
    //Blynk.virtualWrite(V_P_PISCINA, 1);
  }
  else if (!poolEnabled) digitalWrite(P_PISCINA, RELAY_OFF);
}
