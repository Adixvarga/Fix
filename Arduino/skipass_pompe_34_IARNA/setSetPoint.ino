void setSetPoint()
{
  float tOutside = DS18All[2];

  if (tOutside != -127) {
    if (tOutside > spThreshold + 2) {
      sp1Relay = SP_1;
      sp2Relay = SP_2;
      sp3Relay = SP_3;

      Blynk.setProperty(V_SP, "label", "ACTUAL SP:");
    }
    else if (tOutside <= spThreshold) {
      
      digitalWrite(sp1Relay, RELAY_ON);
      digitalWrite(sp2Relay, RELAY_OFF);
      digitalWrite(sp3Relay, RELAY_OFF);
      

      Blynk.setProperty(V_SP, "label", "ACTUAL SP: !!!");
    }
  }
}
