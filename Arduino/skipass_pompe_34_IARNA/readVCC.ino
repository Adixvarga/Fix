float readVCC()
{
  float vcc = (4.86 * analogRead(A0)) / 1023.0;
  return vcc;
}
