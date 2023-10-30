// set short or long timestamp
String getTime(bool tsShort = false)
{
  String timestamp;

  if (tsShort) timestamp = String("<") + hour() + "." + minute() + "." + second() + "> ";
  else timestamp = String("<") + year() + "." + month() + "." + day() + "-" + hour() + "." + minute() + "." + second() + "> ";

  return timestamp;
}
