/// wurkkos-ts10-rgbaux/anduril.h  
/// many config are copied from wurkkos-ts25/anduril.h  


// Wurkkos TS10 (RGB aux version) config options for Anduril
// Copyright (C) 2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later


/*  /// OG Wurkkos TS10-RGB-AUX anduril.h: 


// Wurkkos TS10 (RGB aux version) config options for Anduril
// Copyright (C) 2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

// most things are the same as TS25
#include "wurkkos/ts25/anduril.h"


 */


#pragma once


#include "wurkkos-ts10-rgbaux/hwdef.h"


#include "wurkkos/anduril.h"


/*  /// 

 */


/*  /// RAMP_SIZE, PWM_LEVELS
/// position this RAMP_SIZE and PWM_LEVELS etc. at the top of this config file ...
/// this is kinda fixed config, not customisable 
 */
#define RAMP_SIZE 150


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
// 20 38 56 [75] 93 111 130
// 10 30 50 70 [90] 110 130
#define RAMP_DISCRETE_FLOOR  10
#define RAMP_DISCRETE_CEIL   130
#define RAMP_DISCRETE_STEPS  7


/// Simple UI FLOOR, CEIL, STEPS 
// at Wurkkos's request, reduce the Simple UI ceiling a little bit
// (i.e. not 150; original config had it at 144/150, or DD FET 204/255)
// 20 47 [75] 102 130
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



/*  /// copied from Wurkkos TS25 anduril.h, TOP SECTION:

// this light has three aux LED channels: R, G, B
#define USE_AUX_RGB_LEDS

// don't turn on the aux LEDs while main LEDs are on
#ifdef USE_INDICATOR_LED_WHILE_RAMPING
#undef USE_INDICATOR_LED_WHILE_RAMPING
#endif

// voltage readings were a little high with the Q8 value
#undef VOLTAGE_FUDGE_FACTOR
#define VOLTAGE_FUDGE_FACTOR 5  // add 0.25V, not 0.35V

 */
#define USE_AUX_RGB_LEDS

// don't turn on the aux LEDs while main LEDs are on
#ifdef USE_INDICATOR_LED_WHILE_RAMPING
#undef USE_INDICATOR_LED_WHILE_RAMPING
#endif


/*  /// EXTENDED_INDICATOR_PATTERNS   /// mod: xtra patterns 

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



/*  /// OG Wurkkos TS10 anduril.h, BOTTOM SECTION:

// stop panicking at ~50% power
#define THERM_FASTER_LEVEL 130  // throttle back faster when high

// show each channel while it scroll by in the menu
#define USE_CONFIG_COLORS

// blink numbers on the aux LEDs by default
#undef DEFAULT_BLINK_CHANNEL
#define DEFAULT_BLINK_CHANNEL  CM_AUXWHT

// the aux LEDs are pretty bright; set the high-mode threshold a bit higher
// (default is 15)
#define POST_OFF_VOLTAGE_BRIGHTNESS 25

// the default of 26 looks a bit rough, so increase it to make it smoother
#define CANDLE_AMPLITUDE 33

// don't blink mid-ramp
#ifdef BLINK_AT_RAMP_MIDDLE
#undef BLINK_AT_RAMP_MIDDLE
#endif

// enable factory reset on 13H without loosening tailcap (required)
#define USE_SOFT_FACTORY_RESET

 */
// stop panicking at ~50% power
#define THERM_FASTER_LEVEL 130  // throttle back faster when high


// show each channel while it scroll by in the menu
#define USE_CONFIG_COLORS


// blink numbers on the aux LEDs by default
#undef DEFAULT_BLINK_CHANNEL
#define DEFAULT_BLINK_CHANNEL  CM_AUXWHT


// the default of 26 looks a bit rough, so increase it to make it smoother
#define CANDLE_AMPLITUDE 33



/*  /// copied from Wurkkos TS25 anduril.h, BOTTOM SECTION:

// use aux red + aux blue for police strobe
#define USE_POLICE_COLOR_STROBE_MODE
#define POLICE_STROBE_USES_AUX
#define POLICE_COLOR_STROBE_CH1        CM_AUXRED
#define POLICE_COLOR_STROBE_CH2        CM_AUXBLU

 */
#define USE_POLICE_COLOR_STROBE_MODE
#define POLICE_STROBE_USES_AUX
#define POLICE_COLOR_STROBE_CH1        CM_AUXRED
#define POLICE_COLOR_STROBE_CH2        CM_AUXBLU



///   ///   ///   ///   ///   ///   ///   ///   ///   ///



/*  /// 

 */



/// wurkkos-ts10-rgbaux/anduril.h  



///   END   


