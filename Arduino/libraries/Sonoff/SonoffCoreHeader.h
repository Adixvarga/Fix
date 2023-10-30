

//#define BLYNK_DEBUG // Optional, this enables lots of prints
//#define BLYNK_PRINT Serial

#define VC        "2.4.2-64"          // set core version here
/*
	V52
	- re-implementing eeprom for type, name, auth
	- redirect serial debug data to terminal widget (experimental)
	
	V53
	- added vcc status
	- added free ram status
	- added extra restart cause info
	- added lib version & hw info
	- added low memory, critical voltage, critical dBm notifications
	
	V54
	- added gateway mac, gateway ip, local ip info
	- reduced critical warning levels
	
	V55 - 2018 feb 10
	- switched server: from freeclimb.ro to mrbinmanager
	- esp core updated to 2.4.0
	- blynk lib updated to 0.5.1
	- moved adc_mode right after #includes, into core header (because of compile error in blynk)
	
	V56 - 2018 march 5
	- downgraded to esp core 2.4.0-rc2 (the newest core caused hard crashes - possibly wrong settings?)
	
	V57 - 2018 april 6
	- introducing sonoff basic and slampher (uses DOUT, NOT COMPATIBLE WITH THxx SERIES!!!)
	- sonoff basic and slampher == type 2. implemented case for OTI, with filename 266DOUT.bin"
	- reduced OTI max random delay from 500 to 100 ms
	- added writeDevicePin and readDevicePin (write / read to ANY blynk device)
	
	V58 - 2018 june 24
	- changes in BLYNK_WRITE(V_RELAY_x_STATE) algorithyms, trying to fix "app button out of sync" bug
	- reduced "syncBlynk" timer from 103 to 53
	- introducing "BUTTON_PROTECTED_MODE": it allows on one active relay / device - not working!
	
	V59 - 2018 august ~
	- update to esp core 2.4.2
	
	V60 - 2019 june
	- added #ifdef WEMOS for built in led auto select
	- added #define COMP for vcc auto compensation (sonoff and wemos)
	
	V61 - 2019 october
	- no code changes, only added / removed some wifi ssid+pass
	
	V62 - 2019 december
	- replaced OTI link from hostinger to northbsd
	
	V63 - 2019 december
	- renamed the bin files for OTI (from "66.bin" to "ESP8266.bin", etc)
	- set short timestamp on OTI message, and removed the "FAIL" string
	- added verbose terminal logs to OTI function
	
	V64 - 2019 december
	- just for OTI testing :)
	
	
*/

// INPUTS
#define GPIO_02     2           // end user: S1 MUST BE HIGH DURING BOOT / RESTART / WAKEUP (not really?)
#define GPIO_04     4           // end user: S2 (jack ring 1 on th) !!!!!!!!!!!!!!!!!!!!!!
#define GPIO_14    14           // end user: S3 (jack tip on th)    !!!!!!!!!!!!!!!!!!!!!!
#define GPIO_16    16           // end user: S4

#define BUTTON_1    0           // MUST BE HIGH DURING BOOT / RESTART / WAKEUP !!!!!!!!!
#define BUTTON_2    9
#define BUTTON_3   10
#define BUTTON_4   14           // pin collision on sonoff 4ch      !!!!!!!!!!!!!!!!!!!!!!

// OUTPUTS
#define RELAY_1    12
#define RELAY_2     5
#define RELAY_3     4           // pin collision on sonoff 4ch      !!!!!!!!!!!!!!!!!!!!!!
#define RELAY_4    15           // MUST BE HIGH DURING BOOT / RESTART / WAKEUP !!!!!!!!!

#ifdef WEMOS
#define LED_BLUE    2
#else
#define LED_BLUE   13
#endif

// EEPROM
#define E_RELAY_1 311           // eeprom allocation for relay state
#define E_RELAY_2 312
#define E_RELAY_3 313
#define E_RELAY_4 314

// BLUE LED
#define ON        LOW
#define OFF       HIGH

/*
 bin file for ota:
 
 c:\Users\wanek\AppData\Local\Temp\
 public_html/mrbin
*/

// SYSTEM CONFIG
#define OTA_PWD                       "lonyaL333-OTA"
#define OTI_ADDRESS                   "http://blynk.northbsd.org/static/17aF9zRpnxb1Rqki9umCPMWm37PowRg9LD/"
#define OPEN_WIFI                     ""   // open wifi password
#define BLYNK_WDT                 300000L  // reset system if last connection > 5 minutes (300000 millis)
#define SNOOZE_TIMEOUT           3600000L
#define SNOOZE_CHECK               60000L
#define WIFI_TIMEOUT               15000   // timeout for try to connect to wifi in setup
#define SERVER_TIMEOUT              5000   // timeout for try to connect to server in main loop
#define BLYNK_CONNECTION_INTERVAL  25000   // reconnect to blynk server try interval (will hang the system for SERVER_TIMEOUT)

#ifdef WEMOS
#define COMP  400  // vcc compensation in mv
#else
#define COMP -200
#endif

// VIRTUAL PINS
#define V_ALL_NOTIFY          V0  // turn on / off all notifications

#define V_RELAY_1_STATE       V1  // RELAY ON / OFF
#define V_RELAY_2_STATE       V2
#define V_RELAY_3_STATE       V3
#define V_RELAY_4_STATE       V4

#define V_GPIO_02_LED        V10  // LED s1
#define V_GPIO_04_LED        V11  //     s2
#define V_GPIO_14_LED        V12  //     s3
#define V_GPIO_16_LED        V13  //     s4

#define V_GPIO_02_NOTIFY     V14  // NOTIFICATION BUTTON ON / OFF FOR GIVEN INPUT PIN
#define V_GPIO_04_NOTIFY     V15
#define V_GPIO_14_NOTIFY     V16
#define V_GPIO_16_NOTIFY     V17

#define V_GPIO_02_SENS01     V20  // S1 SENSOR VALUE DISPLAY (DS18B20, DHT22, etc.)
#define V_GPIO_04_SENS01     V31  // S2 in between virtual pins are reserved for 10 X ds18 sensors on same bus 
#define V_GPIO_14_SENS01     V42  // S3 (jack tip)
#define V_GPIO_16_SENS01     V53  // S4 ds18 not working on this pin !!!

#define V_SNOOZE02_BUTTON    V54
#define V_SNOOZE04_BUTTON    V55
#define V_SNOOZE14_BUTTON    V56
#define V_SNOOZE16_BUTTON    V57

// VIRTUAL PINS - ADMIN
#define V_VCC               V115  // vcc in volts
#define V_RAM               V116  // free ram (heap)
#define V_DBM               V117  // wifi signal strength
#define V_SET_TYPE          V118
#define V_SEND_RTC          V119
#define V_RESTART_CAUSE     V120
#define V_RESTART           V121
#define V_MAC               V122
#define V_TERMINAL          V123
#define V_UPDATE_NAME       V124
#define V_UPDATE_TOKEN      V125
#define V_GET_UPDATE        V126  // OTI UPDATE
#define V_MESSAGE           V127

// LIBS
#include <ESP8266WiFi.h>          // wifi
#include <ESP8266WiFiMulti.h>     // Wi-Fi-Multi
#include <ESP8266mDNS.h>          // ota
#include <WiFiUdp.h>              // ota
#include <ArduinoOTA.h>           // ota
#include <ESP8266HTTPClient.h>    // http (blynk api, oti)
#include <ESP8266httpUpdate.h>    // http oti

#include <BlynkSimpleEsp8266.h>   // blynk library

#include <TimeLib.h>              // hw rtc time
#include <WidgetRTC.h>            // blynk rtc widget

#include <EEPROM.h>

#include <OneWire.h>
#include <DallasTemperature.h>

#include <DHT.h>

ADC_MODE(ADC_VCC);                // this line has to be "right after the #include lines"
