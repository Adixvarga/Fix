// FUNCTION PROTOTYPES
String getTime(bool tsShort = false);

#include "header.h"

// declare variables
bool debugMode          = false;
bool firstRun           = true;
bool priorityModeBoiler = false;
bool poolEnabled        = false;

bool hidroWeekdaySelected[8];
bool uscatorWeekdaySelected[8];

bool boilerNeedsHeat = true;

byte sp1Relay = SP_1;
byte sp2Relay = SP_2;
byte sp3Relay = SP_3;

byte boilerThreshold = 45;
byte boilerTarget = 60;

byte modeCorpA     = 2;  // segmented switches function mode (1 = manual off, 2 = auto, 3 = manual on)
byte modeCorpB     = 2;
byte modeCorpC     = 2;
byte modeCamereB   = 2;
byte modeCasuta    = 2;
byte modePardosea  = 2;
byte modePiscina   = 2;
byte modeSchiuri   = 2;
byte modeBoiler    = 2;
byte modeCentEl    = 2;

byte modePCG1      = 2;
byte modePCG2      = 2;
byte modePCG3      = 2;
byte modePCG4      = 2;

byte hidroStartH, hidroStartM, hidroStopH, hidroStopM;
byte uscatorStartH, uscatorStartM, uscatorStopH, uscatorStopM;

unsigned long toggleHidro;

float spThreshold = -12;
float poolTargetTemp = 29;

char auth[] = "dRPqeEyLFZj14QgBFqGvdOZ1rYpiwnbU";

// declare objects

byte arduino_mac[] = {0xFE, 0xBB, 0x8C, 0x94, 0x99, 0xDF};

IPAddress arduino_ip (192,168,  0,  100);
IPAddress dns_ip     (  8,  8,  8,  8);
IPAddress gateway_ip (192,168,  0,  1);
IPAddress subnet_mask(255,255,255,  0);

RTC_DS3231 rtc;
BlynkTimer timer;
WidgetRTC widgetRtc;
WidgetTerminal terminal(V_TERMINAL);

WidgetLED LedAlimPost(V70);
WidgetLED LedAlimRetea(V71);
WidgetLED LedBoiler(V83);
WidgetLED LedPPiscina(V72);
WidgetLED LedHidro(V15);
WidgetLED LedUscator(V16);
WidgetLED LedPc01(V73);
WidgetLED LedPc02(V74);
WidgetLED LedPc03(V75);
WidgetLED LedPc04(V76);
WidgetLED LedPc05(V77);
WidgetLED LedPc06(V78);
WidgetLED LedPc07(V79);
WidgetLED LedPc08(V80);
WidgetLED LedPc09(V81);
WidgetLED LedPc10(V82);
WidgetLED LedEcoBoiler(V84);

OneWire oneWire(ONE_WIRE_BUS);        // setup a onewire instance
DallasTemperature sensors(&oneWire);

DeviceAddress DS18boiler  = {0x28, 0xFF, 0x61, 0x36, 0xC0, 0x17, 0x01, 0x5A};  // 0
DeviceAddress DS18pool    = {0x28, 0xFF, 0xB9, 0x2E, 0xC0, 0x17, 0x02, 0xFC};  // 1
DeviceAddress DS18outside = {0x28, 0xFF, 0xC3, 0x4B, 0xC0, 0x17, 0x01, 0xDF};  // 2
DeviceAddress DS18agent   = {0x28, 0xFF, 0xD6, 0x5F, 0xC0, 0x17, 0x01, 0x47};  // 3
DeviceAddress DS18inside  = {0x28, 0xFF, 0x79, 0x4F, 0xC0, 0x17, 0x01, 0x23};  // 4
DeviceAddress DS18aux     = {0x28, 0xFF, 0x83, 0x4A, 0xC0, 0x17, 0x01, 0xB9};  // 5

float DS18All[TOTAL_DS18] = {-127.0};

void loop()
{
  blynkHandler();
  timer.run();
}
