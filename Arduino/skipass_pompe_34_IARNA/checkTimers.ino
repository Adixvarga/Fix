void checkTimers()
{
  static unsigned long lastRun;

  if (startStopTimer(hidroStartH, hidroStartM, hidroStopH, hidroStopM, hidroWeekdaySelected)) {
    if (millis() > lastRun + toggleHidro && !digitalRead(P_HIDROMASAJ)) {
      lastRun = millis();
      digitalWrite(P_HIDROMASAJ, RELAY_OFF);
    }
    else if (millis() > lastRun + (600000 - toggleHidro) && digitalRead(P_HIDROMASAJ)) {
      lastRun = millis();
      digitalWrite(P_HIDROMASAJ, RELAY_ON);
    }
  }
  else digitalWrite(P_HIDROMASAJ, RELAY_OFF);
  
  if (startStopTimer(uscatorStartH, uscatorStartM, uscatorStopH, uscatorStopM, uscatorWeekdaySelected)) {
    digitalWrite(P_USCATOR, RELAY_ON);
  }
  else digitalWrite(P_USCATOR, RELAY_OFF);
}
