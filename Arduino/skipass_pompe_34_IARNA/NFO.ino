/*
   mgbiker3@gmail.com, 2019
   for arduino mega2560

   automatizare pt skipass pompe de caldura

  for ds18 ~20m: pull-up resistor value: ~2k

     Mode     Res.       Conversion time
      9 bits  0.5   °C    94 ms
     10 bits  0.25  °C   188 ms
     11 bits  0.125 °C   375 ms
     12 bits  0.0625°C   750 ms

  v27 - 2020 dec 21:
  - found bug with set point switch, added "special sp mode indicator !!!"
  - found bug with pool pump: poolEnabled status not updated when auto mode selected
  - implementing corp B button and timetable
  - other small bug fixes and improvements
*/
