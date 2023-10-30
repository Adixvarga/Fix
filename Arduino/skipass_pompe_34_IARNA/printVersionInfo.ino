void printVersionInfo()
{
  Serial.println(F("***********************************"));
  Serial.print("IDE version: ");
  Serial.println(ARDUINO);
  Serial.print("FW  version: ");
  Serial.println(VERSION);
  Serial.println("compiled at: " __DATE__ ", " __TIME__);
  Serial.print("hardware RTC time is:");
  Serial.println(getTime());
  Serial.println("");
  Serial.println(F("by mgbiker3@gmail.com"));
  Serial.println(F("***********************************"));
  Serial.println("");
}
