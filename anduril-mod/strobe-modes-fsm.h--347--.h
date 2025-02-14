// strobe-modes-fsm.h: FSM config for strobe modes in Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later


///   ///   ///   ///   ///   ///   ///


#pragma once


// enable the random number generator if we need it
#if defined(USE_LIGHTNING_MODE) || defined(USE_CANDLE_MODE) || defined(USE_FIREWORK_MODE) ||defined(USE_BAD_FLUORESCENT_MODE)
#define USE_PSEUDO_RAND
#endif


// party strobe uses really short pulses
#ifdef USE_PARTY_STROBE_MODE
#define USE_DELAY_ZERO
#endif


// candle mode is basically a bunch of stacked random triangle waves
#if defined(USE_CANDLE_MODE)
#define USE_TRIANGLE_WAVE
#endif






///   ///   ///   ///   ///   ///   ///

///   starryalley   "strobe-modes-fsm.h--30--staryalley--.h" : 

///   // the presence of strobe mode(s) affects how many eeprom bytes we need,
///   // so it's relevant for FSM configuration
/*
#if defined(USE_CANDLE_MODE) || defined(USE_FIREWORK_MODE) || defined(USE_BIKE_FLASHER_MODE) || defined(USE_PARTY_STROBE_MODE) || defined(USE_TACTICAL_STROBE_MODE) || defined(USE_LIGHTNING_MODE)
#define USE_STROBE_STATE
#endif
 */


// the presence of strobe mode(s) affects how many eeprom bytes we need,
// so it's relevant for FSM configuration
#if defined(USE_CANDLE_MODE) || defined(USE_FIREWORK_MODE) || defined(USE_BIKE_FLASHER_MODE) || defined(USE_PARTY_STROBE_MODE) || defined(USE_TACTICAL_STROBE_MODE) || defined(USE_LIGHTNING_MODE)
#define USE_STROBE_STATE
#endif

///   ///   ///   ///   ///   ///   ///






///   ///   ///   ///   ///   ///   ///

// internal numbering for strobe modes
#ifdef USE_STROBE_STATE
typedef enum {

    #ifdef USE_PARTY_STROBE_MODE
    party_strobe_e,
    #endif

    #ifdef USE_TACTICAL_STROBE_MODE
    tactical_strobe_e,
    #endif



    #ifdef USE_POLICE_COLOR_STROBE_MODE
    police_color_strobe_e,
    #endif



    #ifdef USE_TINT_RAMPING
    tint_alternating_strobe_e,
    tint_smooth_ramp_e,
    #endif



    #ifdef USE_LIGHTNING_MODE
    lightning_storm_e,
    #endif

    #ifdef USE_CANDLE_MODE
    candle_mode_e,
    #endif



    #ifdef USE_FIREWORK_MODE
    firework_mode_e,
    #endif

    #ifdef USE_LIGHTHOUSE_MODE
    lighthouse_mode_e,
    #endif

    #ifdef USE_BAD_FLUORESCENT_MODE
    bad_fluorescent_mode_e,
    #endif



    #ifdef USE_BIKE_FLASHER_MODE
    bike_flasher_e,
    #endif
    strobe_mode_END

} strobe_mode_te;



//const int NUM_STROBES = strobe_mode_END;
#define NUM_STROBES strobe_mode_END
#endif



///   END   
