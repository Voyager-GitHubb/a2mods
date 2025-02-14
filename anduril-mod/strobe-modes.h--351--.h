// strobe-modes.h: Strobe modes for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later


/////////////////////////////////////////////////////////////


#pragma once


#ifdef USE_STROBE_STATE

strobe_mode_te current_strobe_type;


// which strobe mode is active?
#ifdef USE_CANDLE_MODE

    #define DEFAULT_STROBE candle_mode_e
#else
    #define DEFAULT_STROBE 0
#endif

#endif  // ifdef USE_STROBE_STATE


// full FET strobe can be a bit much...  use max regulated level instead,
// if there's a bright enough regulated level
#ifndef STROBE_BRIGHTNESS
#ifdef MAX_Nx7135
#define STROBE_BRIGHTNESS MAX_Nx7135
#else
#define STROBE_BRIGHTNESS MAX_LEVEL
#endif
#endif

// some drivers need to keep the regulator chip on between pulses,
// so set this to 1 to keep the light on at moon mode between pulses,
// and thus keep the regulator powered up for the next flash
#ifndef STROBE_OFF_LEVEL
#define STROBE_OFF_LEVEL 0
#endif






// party and tactical strobes
#ifdef USE_STROBE_STATE
uint8_t strobe_state(Event event, uint16_t arg);
inline void strobe_state_iter();
#endif



#if defined(USE_PARTY_STROBE_MODE) || defined(USE_TACTICAL_STROBE_MODE)
// party / tactical strobe timing

uint8_t strobe_delays[] = { 41, 67 };  // party strobe 24 Hz, tactical strobe 10 Hz

inline void party_tactical_strobe_mode_iter(uint8_t st);

#endif



#ifdef USE_POLICE_COLOR_STROBE_MODE
inline void police_color_strobe_iter();
#endif





#ifdef USE_LIGHTNING_MODE

#ifndef LIGHTNING_BUSY_FACTOR
#define LIGHTNING_BUSY_FACTOR 14 // max 16384ms (max ~16 sec interval)
#endif

uint8_t lightning_busy_factor = LIGHTNING_BUSY_FACTOR;

#define LIGHTNING_BUSY_FACTOR_MAX 16 // max 65536ms (max ~65 sec interval)

#define LIGHTNING_BUSY_FACTOR_MIN 12 // max 4096ms (max ~4 sec interval)

inline void lightning_storm_iter();
#endif





// bike mode config options
#ifdef USE_BIKE_FLASHER_MODE

    #if !defined(DEFAULT_BIKING_LEVEL)
        #define DEFAULT_BIKING_LEVEL  (RAMP_SIZE/3)

    #elif DEFAULT_BIKING_LEVEL > MAX_BIKING_LEVEL
        #undef DEFAULT_BIKING_LEVEL

        #define DEFAULT_BIKING_LEVEL  MAX_BIKING_LEVEL
    #endif

    #define MAX_BIKING_LEVEL 120  // should be 127 or less

    uint8_t bike_flasher_brightness = DEFAULT_LEVEL;

    inline void bike_flasher_iter();

#endif  // ifdef USE_BIKE_FLASHER_MODE






/////////////////////////////////////////////////////////////


#ifdef USE_FIREWORK_MODE

#define MIN_FIREWORK_LEVEL DEFAULT_LEVEL // max is always MAX_LEVEL

uint8_t firework_brightness = RAMP_SMOOTH_CEIL;

inline void firework_iter();

#endif


/////////////////////////////////////////////////////////////








#ifdef USE_LIGHTHOUSE_MODE

uint8_t lighthouse_phase = 0;

#define LIGHTHOUSE_MAX_DELAY 30
#define LIGHTHOUSE_MIN_DELAY 0
#define LIGHTHOUSE_DELAY_DEFAULT 5

uint8_t lighthouse_delay = LIGHTHOUSE_DELAY_DEFAULT;

inline void lighthouse_iter();

#endif





#ifdef USE_BAD_FLUORESCENT_MODE

uint8_t fluoresent_brightness = DEFAULT_LEVEL;

uint8_t fluoresent_flicker_random = 1;

uint8_t fluoresent_flicker_index = 0;

uint8_t fluoresent_ramp_up_increment = 0;

inline void bad_fluorescent_iter();

#endif





#ifdef USE_TINT_RAMPING

uint8_t tint_alt_brightness = DEFAULT_LEVEL;

uint8_t tint_alt_interval = 2; // unit is 500ms, so 2 == one second

#define TINT_ALT_MAX_INTERVAL 20 // 10s

#define TINT_ALT_MIN_INTERVAL 1  // 0.5s


inline void tint_alt_iter();

uint8_t tint_smooth_brightness = DEFAULT_LEVEL;

uint8_t tint_smooth_pause = 3; // unit is ms. Change tint 1 step after this pause

#define TINT_SMOOTH_MAX_PAUSE 30

#define TINT_SMOOTH_MIN_PAUSE 1

inline void tint_smooth_ramp_iter();

#endif








/// 2025-02-05 21:31
/// beacon in strobes group 
#ifdef USE_BEACON_STROBE_MODE

uint8_t beacon_strobe_brightness = DEFAULT_LEVEL;

inline void bracon_strobe_iter();

#endif


/*

inline void beacon_mode_iter() {
    // one iteration of main loop()
    if (! button_last_state) {
        set_level(memorized_level);
        nice_delay_ms(100);
        set_level(0);
        nice_delay_ms(((cfg.beacon_seconds) * 1000) - 100);
    }
}

 */



/*

    // hold: configure beacon timing
    else if (event == EV_click1_hold) {
        if (0 == (arg % TICKS_PER_SECOND)) {
            blink_once();
        }
        return EVENT_HANDLED;
    }


    // release hold: save new timing
    else if (event == EV_click1_hold_release) {
        cfg.beacon_seconds = 1 + (arg / TICKS_PER_SECOND);
        save_config();
        return EVENT_HANDLED;
    }

 */
















#ifdef USE_CANDLE_MODE
#include "anduril/candle-mode.h"
#endif



#if defined(USE_POLICE_STROBE_MODE) || defined(USE_SOS_MODE_IN_FF_GROUP)
#define USE_BORING_STROBE_STATE
#include "anduril/ff-strobe-modes.h"
#endif



///   END   
