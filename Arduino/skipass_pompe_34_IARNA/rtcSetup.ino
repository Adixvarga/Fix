void widgetRtcSetup()
{
  Wire.begin();
  rtc.begin();

  //rtc.adjust(DateTime(__DATE__, __TIME__));  // set widgetRtc date and time to COMPILE time - DO NOT ENABLE!

  setSyncProvider(RTC.get);                                    // the function to get the time from the widgetRtc
}
