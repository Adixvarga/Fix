float readPressure(byte analogPin)
{
  float offset = 0.49;
  
  float V = analogRead(analogPin) * 5.00 / 1023.0;     // Sensor output voltage
  float P = (V - offset) * 2.5;                        // Calculate water pressure in bar

  if (P < 0.0) P = 0;

  //Serial.println(P);

  return P;
}
