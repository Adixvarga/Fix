byte getToday()
{
  byte today;

  if (weekday() == 1) today = 7;
  else today = weekday() - 1;

  return today;
}
