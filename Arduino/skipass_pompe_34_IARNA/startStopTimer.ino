bool startStopTimer(byte StartH, byte StartM, byte StopH, byte StopM, bool weekdaySelected[])
{
  bool armedMode = false;
  byte today = getToday();

  if (weekdaySelected[today]) {
    unsigned long StartSecond = (StartH * 3600) + (StartM * 60);                    // calculate start second of the day
    unsigned long StopSecond  = (StopH  * 3600) + (StopM  * 60);                    // calculate stop  second of the day
    unsigned long currentSecond  = ((hour() * 3600) + (minute() * 60) + second());  // calculate current second

    if ((  StartSecond <  StopSecond  &&
           currentSecond >= StartSecond &&
           currentSecond <= StopSecond) ||

        (   StartSecond >  StopSecond  &&
            (currentSecond >= StartSecond ||
             currentSecond <= StopSecond))) {

      armedMode = true;
    }
    else armedMode = false;
  }

  return armedMode;
}
