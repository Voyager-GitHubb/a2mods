/// wurkkos-ts10/anduril.h 


// Wurkkos TS10 (originally used Sofirn SP36-t1616 firmware) config options for Anduril using the Attiny1616
// Copyright (C) 2022-2023 (FIXME)
// SPDX-License-Identifier: GPL-3.0-or-later


#pragma once


// same as  the  BLF Q8 T1616, mostly (added Dynamic PWM)
#include "wurkkos-ts10/hwdef.h"

#include "wurkkos/anduril.h"


/*  /// 

 */


/*  /// RAMP_SIZE, PWM_LEVELS
/// position this RAMP_SIZE and PWM_LEVELS config etc. at the top of this config file ...
/// this is kinda fixed config, not customisable 
 */
#define RAMP_SIZE 150


#if 0  // 2022 version by SammysHP, smooth but only level 1/150 is underclocked
// level 1 by hand, for the rest
// level_calc.py 7.01 2 149 7135 3 0.5 125 FET 1 10 1200 --pwm dyn:63:2048:255
#define PWM1_LEVELS 1,3,3,4,5,6,7,8,9,10,12,13,14,16,17,19,20,22,24,25,27,29,31,33,35,37,40,42,44,47,49,52,54,57,59,62,64,67,70,72,75,77,80,82,85,87,89,91,93,95,96,98,99,100,100,101,100,100,99,97,95,93,90,86,82,87,91,96,100,106,111,116,122,128,134,141,147,155,162,169,177,186,194,203,213,222,232,243,254,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,0
#define PWM2_LEVELS 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,3,4,6,7,9,11,12,14,16,18,20,22,24,27,29,31,34,37,39,42,45,48,51,54,57,61,64,68,72,75,79,83,88,92,97,101,106,111,116,121,126,132,138,144,150,156,162,169,176,183,190,197,205,213,221,229,237,246,255
#define PWM_TOPS 2047,2047,1198,1322,1584,1676,1701,1691,1662,1622,1774,1703,1631,1692,1613,1639,1558,1564,1559,1478,1464,1444,1420,1392,1361,1329,1331,1293,1256,1246,1207,1192,1152,1133,1094,1074,1035,1013,991,954,932,897,875,842,820,790,760,731,704,678,646,622,593,566,534,510,478,452,423,393,364,338,310,280,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255
#define MAX_1x7135 90
#define HALFSPEED_LEVEL 2
#define QUARTERSPEED_LEVEL 2
#endif

// 7135 at 90/150
// level_calc.py 5.7895 2 150 7135 0 0.1 125.25 FET 1 10 1200 --pwm dyn:61:4096:255:2.5 --clock 5:11:2.0
// (with heavy manual tweaks up to ~15/150)
#define PWM1_LEVELS     1,   1,   2,   2,   3,   3,   4,   5,   6,   6,   8,   9,   9,  10,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  19,  20,  21,  22,  23, 23, 24, 25, 26, 26, 27, 27, 28, 28, 29, 29, 30, 30, 31, 31, 32, 32, 33, 33, 34, 35, 36, 37, 38, 40, 41, 43, 45, 47, 50, 53, 56, 60, 63, 67, 71, 75, 79, 84, 89, 94, 99,104,110,116,122,129,136,143,150,158,166,174,183,192,202,211,222,232,243,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,0
#define PWM2_LEVELS     0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  3,  5,  7,  8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 29, 31, 34, 37, 39, 42, 45, 48, 51, 54, 58, 61, 65, 68, 72, 76, 80, 84, 88, 93, 97,102,107,112,117,122,127,133,139,145,151,157,163,170,177,183,191,198,205,213,221,229,238,246,255
#define PWM_TOPS     4095,2893,3917,2806,3252,2703,2684,2660,2640,2370,3000,2900,2630,2549,2246,2193,2030,1961,1889,1716,1642,1569,1497,1428,1290,1232,1176,1122,1070,976,932,890,849,779,745,685,656,605,579,536,514,476,457,424,407,379,364,340,327,314,302,291,280,276,266,262,257,253,253,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255



#define MAX_1x7135 90

#define MIN_THERM_STEPDOWN 60

#define HALFSPEED_LEVEL 11
#define QUARTERSPEED_LEVEL 5

#define DEFAULT_LEVEL 50


/// SMOOTH RAMP FLOOR AND CEIL 
#define RAMP_SMOOTH_FLOOR    1
#define RAMP_SMOOTH_CEIL     130


/// STEPPED RAMP FLOOR, CEIL, STEPS 
// 10 30 50 70 [90] 110 130
#define RAMP_DISCRETE_FLOOR  10
#define RAMP_DISCRETE_CEIL   130
#define RAMP_DISCRETE_STEPS  7


/// Simple UI FLOOR, CEIL, STEPS 
// at Wurkkos's request, reduce the Simple UI ceiling a little bit
// (i.e. not 150; original config had it at 144/150, or DD FET 204/255)
// 10 30 50 70 [90] 110 130
#define SIMPLE_UI_FLOOR  10
#define SIMPLE_UI_CEIL   130
#define SIMPLE_UI_STEPS  7



/*  /// 

 */

/*  /// 

 */

/*  /// 

 */



// uses forward-facing aux LEDs
#define USE_INDICATOR_LED

// don't turn on the aux LEDs while main LEDs are on
#ifdef USE_INDICATOR_LED_WHILE_RAMPING
#undef USE_INDICATOR_LED_WHILE_RAMPING
#endif


/*  /// EXTENDED_INDICATOR_PATTERNS

/// NEW MOD. more-aux-patterns. by SammysHP

/// "Works for classic and RGB aux LEDs."

/// PATTERNS:
    // low nibble:  off state
    // high nibble: lockout state
    // modes are:
    //   0=off
    //   1=low
    //   2=high
    //   3=fancy blinking
    //   4=low blinking
    //   5=high blinking 



#define USE_EXTENDED_INDICATOR_PATTERNS

/// LOCKOUT: low (1) .  OFF-MODE: low blinking (4) 
#define INDICATOR_LED_DEFAULT_MODE ((1<<INDICATOR_LED_CFG_OFFSET) + 4)

 */ 
#define USE_EXTENDED_INDICATOR_PATTERNS
/// LOCKOUT: low (1) .  OFF-MODE: low blinking (4) 
#define INDICATOR_LED_DEFAULT_MODE ((1<<INDICATOR_LED_CFG_OFFSET) + 4)


// voltage readings were a little high with the Q8 value
#undef VOLTAGE_FUDGE_FACTOR
#define VOLTAGE_FUDGE_FACTOR 5  // add 0.25V, not 0.35V


// stop panicking at ~50% power
#define THERM_FASTER_LEVEL 130  // throttle back faster when high


// show each channel while it scroll by in the menu
#define USE_CONFIG_COLORS


// blink numbers on the aux LEDs by default
#define DEFAULT_BLINK_CHANNEL  CM_AUX


// the default of 26 looks a bit rough, so increase it to make it smoother
#define CANDLE_AMPLITUDE 33





/*  /// 

 */



/* /////    BLINKIES AND STROBES     /////  
///  from `config-default.h` : 

#define USE_SOS_MODE
#define USE_BEACON_MODE

// enable various strobe modes
#define USE_BIKE_FLASHER_MODE
#define USE_PARTY_STROBE_MODE
#define USE_TACTICAL_STROBE_MODE

#define USE_LIGHTNING_MODE
#define USE_CANDLE_MODE



///  from  `sofirn/anduril.h` :  
#define USE_FIREWORK_MODE
#define USE_LIGHTHOUSE_MODE
#define USE_BAD_FLUORESCENT_MODE


 */
/* /// DISABLE SOME BLINKIES ? 

#undef USE_SOS_MODE
#undef USE_BEACON_MODE

 */
#undef USE_SOS_MODE



/* /// DISABLE SOME STROBES ? 
#undef USE_BIKE_FLASHER_MODE
#undef USE_PARTY_STROBE_MODE
#undef USE_TACTICAL_STROBE_MODE

#undef USE_LIGHTNING_MODE


#undef USE_BAD_FLUORESCENT_MODE
#undef USE_FIREWORK_MODE
#undef USE_LIGHTHOUSE_MODE

 */

#undef USE_CANDLE_MODE




/// 2025-02-10: #define USE_BEACONN_MODE
/*  /// 2025-02-09: BEACONN_MODE in STROBE_GROUP 


/// 2025-02-07: BMISG
/// BEACON_MODE_ISG
/// USE_BEACON_MODE_IN_STROBE_GROUP 
/// #define USE_BEACON_MISG


/// 2025-02-09: BMISG
/// BEACON-MISG
/// USE_BEACON_MODE_ISG 
/// #define USE_BEACON_MODE_ISG
#define USE_BEACON_MODE_ISG


/// 2025-02-11: BEACONN_MODE
/// config integrated into strobe-modes files
/// works very well
/// 1H timing / interval adjustment works very well
#define USE_BEACONN_MODE


 */
#define USE_BEACONN_MODE





/*  /// "VER_CHECK_MODE" in the blinky group  
 * idea: "version-check"  in the blinky group? 
 * tested on the SC31 Pro t1616 
   additional line in the "sofirn/sc31-pro-t1616/anduril.h" :  
     #define USE_VER_CHECK_MODE		
 * additional lines in the "battcheck-mode.c" : 
     #elif defined(USE_VER_CHECK_MODE)
     set_state(ver_check_state, 0);
 */
/*  /// "USE_VER_CHECK_MODE" 
 * in "config-default.h" , for reference: 
     "include a function to blink out the firmware version" 
     "#define USE_VERSION_CHECK"

 * sc31-pro-t1616: "USE_VER_CHECK_MODE" 
 */
#define USE_VER_CHECK_MODE


/* /// DEFAULT_DONT_RAMP_AFTER_MOON
/// some settings are applied per flashlight  
/// adjusted for each flashlight 
/// tested on the  sc31-pro-t1616 
/// 1H = floor (moon). stay at moon, don't ramp up 
 */
#define DEFAULT_DONT_RAMP_AFTER_MOON 1


/* /// DEFAULT MANUAL MEMORY  
///   stepped ramp:   1  31  61  91   121 

 */
#define DEFAULT_MANUAL_MEMORY 30


/* /// TACTICAL MODE LEVELS

///   1H,  2H , 3H : 
///   HIGH , TACTICAL STROBE , LOW  
///     150 = turbo
///     (RAMP_SIZE+1) = party strobe
///     (RAMP_SIZE+2) = tactical strobe
///     (RAMP_SIZE+3) = bike flasher  


///example:
#define TACTICAL_LEVELS 129,(RAMP_SIZE+2),DEFAULT_MANUAL_MEMORY
#define TACTICAL_LEVELS RAMP_DISCRETE_CEIL,(RAMP_SIZE+2),DEFAULT_MANUAL_MEMORY


 */
#define TACTICAL_LEVELS RAMP_DISCRETE_CEIL,(RAMP_SIZE+2),DEFAULT_MANUAL_MEMORY



/* /// MORE MODS ? ..

#undef USE_RAMP_SPEED_CONFIG
#undef USE_RAMP_AFTER_MOON_CONFIG
#undef USE_2C_STYLE_CONFIG


#undef USE_POLICE_STROBE_MODE
#undef USE_CHANNEL_PER_STROBE

#undef USE_TACTICAL_MODE

#undef USE_SUNSET_TIMER

 */
#undef USE_SIMPLE_UI





///   ///   ///   ///   ///   ///   ///





/*  /// 

 */



/// wurkkos-ts10/anduril.h 



///   END   


