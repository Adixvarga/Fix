void WDTreset()  // mcu reset
{
  wdt_enable(WDTO_1S);
  while(1) {}
}
