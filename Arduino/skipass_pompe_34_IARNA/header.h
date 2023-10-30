#define VERSION     "1.27, #49"

// INPUTS
#define ONE_WIRE_BUS   22

#define DEBUG           2

#define IN_ALIM_POST    3
#define IN_ALIM_RETEA   5  // pin 4 is used by ethernet module
#define IN_P_PISCINA    6
#define IN_PC_1         7
#define IN_PC_2         8
#define IN_PC_3         9
#define IN_PC_4        10
#define IN_PC_5        11
#define IN_PC_6        12
#define IN_PC_7        14  // pin 13 is used by builtin led
#define IN_PC_8        15
#define IN_PC_9        16
#define IN_PC_10       17

#define PRESS_APA      A8
#define PRESS_PISCINA  A9

/*
 * relay map:
 * 
 * R01 = BOILER
 * R02 = CORP A
 * R03 = CORP B
 * R04 = CORP C
 * R05 = CASUTA
 * R06 = PARDOSEA
 * R07 = PISCINA
 * R08 = SCHIURI
 * R09 = USCATOR
 * R10 = PC-GRUP 01
 * R11 = PC-GRUP 02
 * R12 = PC-GRUP 03
 * R13 = PC-GRUP 04
 * R14 = SP 01
 * R15 = SP 02
 * R16 = SP 03
 * R17 = HIDROMASAJ
 * R18 = CENT. ELECTRICA
 * R19 = CAMERE B.
 */

// OUTPUTS
#define RELAY_ON  LOW
#define RELAY_OFF HIGH

#define P_HIDROMASAJ  27
#define P_CENT_EL     28  // boiler prority
#define P_CAMERE_B    30
#define P_BOILER      31

#define P_CORP_A      32  // boiler priroity
#define P_CORP_B      33  // boiler priroity
#define P_CORP_C      34  // boiler priroity
#define P_CASUTA      35  // boiler priroity
#define P_PARDOSEA    36  // boiler priroity
#define P_PISCINA     37  // boiler priroity
#define P_SCHIURI     38  // boiler priroity
#define P_USCATOR     39  // boiler priroity

#define P_CALD_1      40
#define P_CALD_2      41
#define P_CALD_3      42
#define P_CALD_4      43

#define SP_1          44
#define SP_2          45
#define SP_3          46

#define SDCARD_CS      4
#define W5100_CS      10  // also, pins: 50, 51, 52, 53 are reserved for SPI!

// BLYNK VIRTUAL PINS
// pump switch
#define V_P_BOILER          V1  // segmented
#define V_P_CORP_A          V2  // segmented
#define V_P_CORP_B          V3  // segmented
#define V_P_CORP_C          V4  // segmented
#define V_P_CASUTA          V5  // segmented
#define V_P_PARDOSEA        V6  // segmented
#define V_P_PISCINA         V7  // segmented
#define V_P_SCHIURI         V8  // segmented

#define V_P_CALD_1          V10
#define V_P_CALD_2          V11
#define V_P_CALD_3          V12
#define V_P_CALD_4          V13
#define V_SP                V14  // setpoint

#define V_SP_THS            V17  // setpoint
#define V_P_CENT_EL         V18  // segmented
#define V_P_CAMERE_B        V19  // segmented

// temperature sensors
#define V_T_BOILER          V50
#define V_T_PISCINA         V51
#define V_T_OUTSIDE         V52
#define V_T_AGENT           V53
#define V_T_INSIDE          V54
#define V_T_AUX             V55

// temperature settings
#define V_T_BOILER_THS      V56
#define V_TARGET_POOL       V57
#define V_T_BOILER_TARGET   V58

// pressure
#define V_PRESS_APA         V60
#define V_PRESS_PISCINA     V61

// time input
#define V_TIMETABLE_HIDRO   V100
#define V_TIMETABLE_USCATOR V101
#define V_TOGGLE_HIDRO      V102

// VIRTUAL PINS - ADMIN
#define V_UPTIME            V113
#define V_DEBUG_EN          V114
#define V_VCC               V115  // vcc in volts (n/a)
#define V_RAM               V116  // free ram (n/a)
#define V_SEND_widgetRtc    V119

#define V_RESTART           V121
#define V_TERMINAL          V123
#define V_MESSAGE           V127


// SYSTEM CONFIG
#define TOTAL_DS18            6        // set total number of ds18 on the bus
#define UNIT_NAME             "049"
#define BLYNK_WDT             300000L  // reset system if last connection > 5 minutes (300000 millis)
#define BLYNK_PRINT Serial
#define TEMPERATURE_PRECISION 11

// LIBRARIES
#include <avr/wdt.h>  // soft reset

// blynk
#include <SPI.h>
#include <Ethernet.h>
#include <BlynkSimpleEthernet.h>

// ds18
#include <OneWire.h>
#include <DallasTemperature.h>

// Rtc
#include <Wire.h>
#include <RTClibExtended.h>
#include <DS1307RTC.h>            // a basic DS1307 library that returns time as a time_t
#include <TimeLib.h>              // hw widgetRtc time
#include <WidgetRTC.h>            // blynk widgetRtc widget
