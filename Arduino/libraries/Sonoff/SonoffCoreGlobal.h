
// sonoff core global objects and variables

BlynkTimer timer;
WidgetRTC  rtc;
WidgetTerminal terminal(V_TERMINAL);

WidgetLED  gpio02LED(V_GPIO_02_LED);
WidgetLED  gpio04LED(V_GPIO_04_LED);
WidgetLED  gpio14LED(V_GPIO_14_LED);
WidgetLED  gpio16LED(V_GPIO_16_LED);

OneWire oneWireGpio02(GPIO_02);                   // set the digital port used by the onewire sensors
OneWire oneWireGpio04(GPIO_04);
OneWire oneWireGpio14(GPIO_14);

DallasTemperature devicesGpio02(&oneWireGpio02);  // pass the onewire reference to dallas temperature
DallasTemperature devicesGpio04(&oneWireGpio04);
DallasTemperature devicesGpio14(&oneWireGpio14);

DeviceAddress oneWireDevices[10];                 // value must be > total nb. of sensors

DHT dhtG02( 2, DHT22);                            // initialize DHT sensor object
DHT dhtG04( 4, DHT22);
DHT dhtG14(14, DHT22);

ESP8266WiFiMulti wifiMulti;

bool gpio02NotifyEnabled = false;
bool gpio04NotifyEnabled = false;
bool gpio14NotifyEnabled = false;
bool gpio16NotifyEnabled = false;
bool typeNotSet          = false;
bool firstRun            = true;

bool snooze02 = false;
bool snooze04 = false;
bool snooze14 = false;
bool snooze16 = false;

byte type;
byte channelToSync;

byte gpio02Devices;                    // ds18 device counter indicator
byte gpio04Devices;
byte gpio14Devices;
byte gpio16Devices;                    // not compatible with onewire devices

byte gpio14notifyCounter;              // for unit 27 - central heating system

int port = 8442;

int relay01Timeout;                    // relay timeout in minutes
int relay02Timeout;
int relay03Timeout;
int relay04Timeout;

float G02t = -900;                     // variables for dht/ds18 sensor data
float G02h = -900;
float G04t = -900;
float G04h = -900;
float G14t = -900;
float G14h = -900;

unsigned long gpio02Timestamp;
unsigned long gpio04Timestamp;
unsigned long gpio14Timestamp;
unsigned long gpio16Timestamp;

unsigned long snooze02Timeout;
unsigned long snooze04Timeout;
unsigned long snooze14Timeout;
unsigned long snooze16Timeout;

volatile unsigned long relay01Timestamp;
volatile unsigned long relay02Timestamp;
volatile unsigned long relay03Timestamp;
volatile unsigned long relay04Timestamp;

char auth[33];
char server[] = BLYNK_SERVER;

String s1Notif;
String s2Notif;
String s3Notif;
String s4Notif;
String unitName;
String mcuType;

