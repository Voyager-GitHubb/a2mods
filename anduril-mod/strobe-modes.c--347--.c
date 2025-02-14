// strobe-modes.c: Strobe modes for Anduril.
// Copyright (C) 2017-2023 Selene ToyKeeper
// SPDX-License-Identifier: GPL-3.0-or-later


/////////////////////////////////////////////////////////////


#pragma once


#include "anduril/strobe-modes.h"


#ifdef USE_STROBE_STATE


uint8_t strobe_state(Event event, uint16_t arg) {
    static int8_t ramp_direction = 1;

    // 'st' reduces ROM size slightly
    strobe_mode_te st = current_strobe_type;




    #if defined(USE_MOMENTARY_MODE) || defined(USE_TACTICAL_MODE)
    momentary_mode = 1;  // 0 = ramping, 1 = strobes
    #endif



    #ifdef USE_CANDLE_MODE
    // pass all events to candle mode, when it's active
    // (the code is in its own pseudo-state to keep things cleaner)
    if (st == candle_mode_e) {
        candle_mode_state(event, arg);
    }
    #endif




    if (0) {}  // placeholder
    // init anything which needs to be initialized
    else if (event == EV_enter_state) {
        current_strobe_type = cfg.strobe_type;
        ramp_direction = 1;
        return EVENT_HANDLED;
    }




    // 1 click: off
    else if (event == EV_1click) {
        set_state(off_state, 0);
        return EVENT_HANDLED;
    }




    // 2 clicks: rotate through strobe/flasher modes
    else if (event == EV_2clicks) {
        current_strobe_type = cfg.strobe_type = (st + 1) % NUM_STROBES;
        save_config();
        return EVENT_HANDLED;
    }
    #if (NUM_CHANNEL_MODES > 1) && defined(USE_CHANNEL_PER_STROBE)






/// OG :   // 3 clicks: rotate through channel modes for the current strobe
///        else if (event == EV_3clicks) {
///
/// MOD : USE 7C INSTEAD OF 3C
/// // 7 clicks: rotate through channel modes for the current strobe
    else if (event == EV_7clicks) {
        // TODO: maybe skip aux modes?
        set_channel_mode((channel_mode + 1) % NUM_CHANNEL_MODES);
        cfg.strobe_channels[st] = channel_mode;
        save_config();
        return EVENT_HANDLED;
    }
    #endif






/// OG : // 4 clicks: rotate back through strobe/flasher modes
///      else if (event == EV_4clicks) {
///
/// MOD : USE 3C INSTEAD OF 4C
/// // 3 clicks: rotate back through strobe/flasher modes
    else if (event == EV_3clicks) {
        current_strobe_type = cfg.strobe_type = (st - 1 + NUM_STROBES) % NUM_STROBES;
        save_config();
        return EVENT_HANDLED;
    }





    // hold: change speed (go faster)
    //       or change brightness (brighter)
    else if (event == EV_click1_hold) {
        if (0) {}  // placeholder

        // party / tactical strobe faster
        #if defined(USE_PARTY_STROBE_MODE) || defined(USE_TACTICAL_STROBE_MODE)
        #ifdef USE_TACTICAL_STROBE_MODE
        else if (st <= tactical_strobe_e) {
        #else
        else if (st == party_strobe_e) {
        #endif
            if ((arg & 1) == 0) {
                uint8_t d = cfg.strobe_delays[st];
                d -= ramp_direction;
                if (d < 8) d = 8;
                else if (d > 254) d = 254;
                cfg.strobe_delays[st] = d;
            }
        }
        #endif



        // lightning has no adjustments
        //else if (st == lightning_storm_e) {}



        // biking mode brighter
        #ifdef USE_BIKE_FLASHER_MODE
        else if (st == bike_flasher_e) {
            cfg.bike_flasher_brightness += ramp_direction;
            if (cfg.bike_flasher_brightness < 2) cfg.bike_flasher_brightness = 2;
            else if (cfg.bike_flasher_brightness > MAX_BIKING_LEVEL) cfg.bike_flasher_brightness = MAX_BIKING_LEVEL;
            set_level(cfg.bike_flasher_brightness);
        }
        #endif



/// MOD ?
/// 
/// NEW STROBE MODES ?
/// 
/// BAD_FLUORESCENT_MODE ?
/// 
/// TINT_RAMPING ?



        return EVENT_HANDLED;
    }





    // reverse ramp direction on hold release
    // ... and save new strobe settings
    else if (event == EV_click1_hold_release) {
        ramp_direction = -ramp_direction;
        save_config();
        return EVENT_HANDLED;
    }





    // click, hold: change speed (go slower)
    //       or change brightness (dimmer)
    else if (event == EV_click2_hold) {
        ramp_direction = 1;

        if (0) {}  // placeholder

        // party / tactical strobe slower
        #if defined(USE_PARTY_STROBE_MODE) || defined(USE_TACTICAL_STROBE_MODE)
        #ifdef USE_TACTICAL_STROBE_MODE
        else if (st <= tactical_strobe_e) {
        #else
        else if (st == party_strobe_e) {
        #endif
            if ((arg & 1) == 0) {
                if (cfg.strobe_delays[st] < 255) cfg.strobe_delays[st] ++;
            }
        }
        #endif



        // lightning has no adjustments
        //else if (st == lightning_storm_e) {}



        // biking mode dimmer
        #ifdef USE_BIKE_FLASHER_MODE
        else if (st == bike_flasher_e) {
            if (cfg.bike_flasher_brightness > 2)
                cfg.bike_flasher_brightness --;
            set_level(cfg.bike_flasher_brightness);
        }
        #endif

        return EVENT_HANDLED;
    }





    // release hold: save new strobe settings
    else if (event == EV_click2_hold_release) {
        save_config();
        return EVENT_HANDLED;
    }





/// MOD : USE 8C INSTEAD OF 5C
    #ifdef USE_MOMENTARY_MODE
/// OG :   // 5 clicks: go to momentary mode (momentary strobe)
///        else if (event == EV_5clicks) {

/// Mod : use 8C instead of 5C
/// // 8 clicks: go to momentary mode (momentary strobe)
    else if (event == EV_8clicks) {
        set_state(momentary_state, 0);
        set_level(0);
        return EVENT_HANDLED;
    }
    #endif
    #if defined(USE_LIGHTNING_MODE) || defined(USE_CANDLE_MODE)
    // clock tick: bump the random seed
    else if (event == EV_tick) {
        // un-reverse after 1 second
        if (arg == AUTO_REVERSE_TIME) ramp_direction = 1;

        pseudo_rand_seed += arg;
        return EVENT_HANDLED;
    }



/////////////////////////////////////////////////////////////


///   BIG MODS, MORE STROBE MODES
///   BIG MODS, MORE ADJUSTMENTS FOR THE STROBE MODES


    // 4C: turning down busy factor (less busy) of lightning mode,
    //  or turning down firework brightness by 12,
    //  or decrease tint alternating interval by 0.5 second
    //  or decrease lighthouse delay by 1 sec
    else if (event == EV_4clicks) {
        if (0) {}  // placeholder



        #ifdef USE_LIGHTNING_MODE
        else if (st == lightning_storm_e) {
            lightning_busy_factor++;
            if (lightning_busy_factor > LIGHTNING_BUSY_FACTOR_MAX)
                lightning_busy_factor = LIGHTNING_BUSY_FACTOR_MAX;
            save_config();
            blink_once();
        }
        #endif



        #ifdef USE_FIREWORK_MODE
        else if (st == firework_mode_e) {
            firework_brightness -= 12;
            if (firework_brightness < MIN_FIREWORK_LEVEL)
                firework_brightness = MIN_FIREWORK_LEVEL;
            save_config();
            blink_once();
        }
        #endif



        #ifdef USE_LIGHTHOUSE_MODE
        else if (st == lighthouse_mode_e) {
            if (lighthouse_delay > LIGHTHOUSE_MIN_DELAY)
                lighthouse_delay--;
            save_config();
            blink_once();
        }
        #endif



        #ifdef USE_TINT_RAMPING
        else if (st == tint_alternating_strobe_e) {
            if (tint_alt_interval > TINT_ALT_MIN_INTERVAL)
                tint_alt_interval--;
            save_config();
            blink_once();
        }
        else if (st == tint_smooth_ramp_e) {
            if (tint_smooth_pause > TINT_SMOOTH_MIN_PAUSE)
                tint_smooth_pause -= 2;
            save_config();
            blink_once();
        }
        #endif

        return EVENT_HANDLED;
    }






    // 5C: turning up busy factor (busier) of lightning mode,
    //  or turning up firework brightness by 12,
    //  or increasing tint alternating interval by 0.5 second
    //  or increasing lighthouse delay by 1 sec
    else if (event == EV_5clicks) {
        if (0) {}  // placeholder



        #ifdef USE_LIGHTNING_MODE
        else if (st == lightning_storm_e) {
            lightning_busy_factor--;
            if (lightning_busy_factor < LIGHTNING_BUSY_FACTOR_MIN)
                lightning_busy_factor = LIGHTNING_BUSY_FACTOR_MIN;
            save_config();
            blink_once();
        }
        #endif



        #ifdef USE_FIREWORK_MODE
        else if (st == firework_mode_e) {
            firework_brightness += 12;
            if (firework_brightness > MAX_LEVEL)
                firework_brightness = MAX_LEVEL;
            save_config();
            blink_once();
        }
        #endif



        #ifdef USE_LIGHTHOUSE_MODE
        else if (st == lighthouse_mode_e) {
            if (lighthouse_delay < LIGHTHOUSE_MAX_DELAY)
                lighthouse_delay++;
            save_config();
            blink_once();
        }
        #endif



        #ifdef USE_TINT_RAMPING
        else if (st == tint_alternating_strobe_e) {
            if (tint_alt_interval < TINT_ALT_MAX_INTERVAL)
                tint_alt_interval++;
            save_config();
            blink_once();
        }
        else if (st == tint_smooth_ramp_e) {
            if (tint_smooth_pause < TINT_SMOOTH_MAX_PAUSE)
                tint_smooth_pause += 2;
            save_config();
            blink_once();
        }
        #endif

        return EVENT_HANDLED;
    }






    // 6C: reset lightning busy factor to default,
    //  or reset firework brightness to default
    //  or reset lighthouse delay to default
    else if (event == EV_6clicks) {
        if (0) {}  // placeholder



        #ifdef USE_LIGHTNING_MODE
        else if (st == lightning_storm_e) {
            lightning_busy_factor = LIGHTNING_BUSY_FACTOR;
            save_config();
            blink_once();
        }
        #endif



        #ifdef USE_FIREWORK_MODE
        else if (st == firework_mode_e) {
            firework_brightness = RAMP_SMOOTH_CEIL;
        }
        #endif



        #ifdef USE_LIGHTHOUSE_MODE
        else if (st == lighthouse_mode_e) {
            lighthouse_delay = LIGHTHOUSE_DELAY_DEFAULT;
        }
        #endif

        return EVENT_HANDLED;

    }
    #endif

    return EVENT_NOT_HANDLED;
}






/////////////////////////////////////////////////////////////






// runs repeatedly in FSM loop() whenever UI is in strobe_state or momentary strobe
inline void strobe_state_iter() {
    uint8_t st = current_strobe_type;  // can't use switch() on an enum



    #if (NUM_CHANNEL_MODES > 1) && defined(USE_CHANNEL_PER_STROBE)
        // remember channel mode for each strobe
        channel_mode = cfg.strobe_channels[st];
    #endif



    switch(st) {


        #if defined(USE_PARTY_STROBE_MODE) || defined(USE_TACTICAL_STROBE_MODE)
        #ifdef USE_PARTY_STROBE_MODE
        case party_strobe_e:
        #endif


        #ifdef USE_TACTICAL_STROBE_MODE
        case tactical_strobe_e:
        #endif
            party_tactical_strobe_mode_iter(st);
            break;
        #endif


        #ifdef USE_POLICE_COLOR_STROBE_MODE
        case police_color_strobe_e:
            police_color_strobe_iter();
            break;
        #endif


        #ifdef USE_LIGHTNING_MODE
        case lightning_storm_e:
            lightning_storm_iter();
            break;
        #endif


        #ifdef USE_BIKE_FLASHER_MODE
        case bike_flasher_e:
            bike_flasher_iter();
            break;
        #endif




///   BIG MODS, MORE STROBE MODES


        #ifdef USE_FIREWORK_MODE
        case firework_mode_e:
            firework_iter();
            break;
        #endif


        #ifdef USE_LIGHTHOUSE_MODE
        case lighthouse_mode_e:
            lighthouse_iter();
            break;
        #endif


        #ifdef USE_BAD_FLUORESCENT_MODE
        case bad_fluorescent_mode_e:
            bad_fluorescent_iter();
            break;
        #endif


        #ifdef USE_TINT_RAMPING
        case tint_alternating_strobe_e:
            tint_alt_iter();
            break;


        case tint_smooth_ramp_e:
            tint_smooth_ramp_iter();
        #endif

   
    }
}
#endif  // ifdef USE_STROBE_STATE






#if defined(USE_PARTY_STROBE_MODE) || defined(USE_TACTICAL_STROBE_MODE)

inline void party_tactical_strobe_mode_iter(uint8_t st) {
    // one iteration of main loop()
    uint8_t del = cfg.strobe_delays[st];  ///  ///  ///  ///  ///  ///  
    // TODO: make tac strobe brightness configurable?
    set_level(STROBE_BRIGHTNESS);


    if (0) {}  // placeholder


    #ifdef USE_PARTY_STROBE_MODE
    else if (st == party_strobe_e) {  // party strobe
        #ifdef PARTY_STROBE_ONTIME
        nice_delay_ms(PARTY_STROBE_ONTIME);
        #else
        if (del < 42) delay_zero();
        else nice_delay_ms(1);
        #endif
    }
    #endif


    #ifdef USE_TACTICAL_STROBE_MODE
    else {  //tactical strobe
        nice_delay_ms(del >> 1);
    }
    #endif


    set_level(STROBE_OFF_LEVEL);
    nice_delay_ms(del);  // no return check necessary on final delay

}
#endif






#ifdef USE_POLICE_COLOR_STROBE_MODE
inline void police_color_strobe_iter() {
    // one iteration of main loop()
    uint8_t del = 66;
    // TODO: make police strobe brightness configurable
    uint8_t bright = memorized_level;
    //uint8_t channel = channel_mode;

    for (uint8_t i=0; i<10; i++) {
        if (0 == i) set_channel_mode(POLICE_COLOR_STROBE_CH1);
        else if (5 == i) set_channel_mode(POLICE_COLOR_STROBE_CH2);
        set_level(bright);
        nice_delay_ms(del >> 1);
        set_level(STROBE_OFF_LEVEL);
        nice_delay_ms(del);
    }

    // restore the channel when done
    //set_channel_mode(channel);
    channel_mode = cfg.channel_mode;
}
#endif






#ifdef USE_LIGHTNING_MODE
inline void lightning_storm_iter() {
    // one iteration of main loop()
    int16_t brightness;
    uint16_t rand_time;

    // turn the emitter on at a random level,
    // for a random amount of time between 1ms and 32ms
    //rand_time = 1 << (pseudo_rand() % 7);
    rand_time = pseudo_rand() & 63;
    brightness = 1 << (pseudo_rand() % 7);  // 1, 2, 4, 8, 16, 32, 64
    brightness += 1 << (pseudo_rand() % 5);  // 2 to 80 now
    brightness += pseudo_rand() % brightness;  // 2 to 159 now (w/ low bias)
    if (brightness > MAX_LEVEL) brightness = MAX_LEVEL;
    set_level(brightness);
    nice_delay_ms(rand_time);

    // decrease the brightness somewhat more gradually, like lightning
    uint8_t stepdown = brightness >> 3;
    if (stepdown < 1) stepdown = 1;
    while(brightness > 1) {
        nice_delay_ms(rand_time);
        brightness -= stepdown;
        if (brightness < 0) brightness = 0;
        set_level(brightness);
        /*
           if ((brightness < MAX_LEVEL/2) && (! (pseudo_rand() & 15))) {
           brightness <<= 1;
           set_level(brightness);
           }
           */
        if (! (pseudo_rand() & 3)) {
            nice_delay_ms(rand_time);
            set_level(brightness>>1);
        }
    }

    // turn the emitter off,
    // for a random amount of time between 1ms and 8192ms
    // (with a low bias)
    rand_time = 1 << (pseudo_rand() % 13);
    rand_time += pseudo_rand() % rand_time;
    set_level(0);
    nice_delay_ms(rand_time);  // no return check necessary on final delay
}
#endif






#ifdef USE_BIKE_FLASHER_MODE
#ifndef BIKE_STROBE_ONTIME
#define BIKE_STROBE_ONTIME 0
#endif
inline void bike_flasher_iter() {

    // one iteration of main loop()

    uint8_t burst = cfg.bike_flasher_brightness << 1;  ///  ///  ///

    if (burst > MAX_LEVEL) burst = MAX_LEVEL;

    for(uint8_t i=0; i<4; i++) {

        set_level(burst);

        nice_delay_ms(5 + BIKE_STROBE_ONTIME);  ///  ///  ///

        set_level(cfg.bike_flasher_brightness);  ///  ///  ///

        nice_delay_ms(65);
    }

    nice_delay_ms(720);  // no return check necessary on final delay
    set_level(0);
}
#endif






/////////////////////////////////////////////////////////////






#ifdef USE_FIREWORK_MODE

#define FIREWORK_DEFAULT_STAGE_COUNT 64

#define FIREWORK_DEFAULT_INTERVAL (2500/FIREWORK_DEFAULT_STAGE_COUNT)

uint8_t firework_stage = 0;

uint8_t firework_stage_count = FIREWORK_DEFAULT_STAGE_COUNT;

uint8_t step_interval = FIREWORK_DEFAULT_INTERVAL;



#ifdef USE_TINT_RAMPING

uint8_t tint_mode = 0; // 0: alternate, 1: channel 1 only, 2: channel 2 only, 3: random tint

uint8_t chosen_tint = 127; // for tint_mode = 3

#endif



inline static void update_firework_tint(uint8_t stage) {

    #ifdef USE_TINT_RAMPING

    if (tint_locked) return;


    switch (tint_mode) {

    // alternate both channels
    case 0:
        if (stage % 5 == 0)
            tint = (tint == 1) ? 254 : 1; 
        break;

    // channel 1 only
    case 1:
        tint = 1;
        break;

    // channel 2 only
    case 2:
        tint = 254;
        break;

    // random tint
    case 3:
        tint = chosen_tint;
        break;

    }
    #endif

}



// code is copied and modified from factory-reset.c
inline void firework_iter() {

    if (firework_stage == firework_stage_count) {        

        // explode, and reset stage
        firework_stage = 0;

        for (uint8_t brightness = firework_brightness; brightness > 0; brightness--) {
            update_firework_tint(firework_stage);
            set_level(brightness);
            nice_delay_ms(step_interval/4);
            set_level((uint16_t)brightness*7/8);
            nice_delay_ms(step_interval/(1+(pseudo_rand()%5)));
        }

        // off for 1 to 5 seconds
        set_level(0);
        nice_delay_ms(1000 + (pseudo_rand() % 5) * 1000);
        #ifdef USE_TINT_RAMPING

        // randomly set a tint mode for the next firework show
        tint_mode = pseudo_rand() % 4;
        if (tint_mode == 3) chosen_tint = pseudo_rand() % 254 + 1;
        update_firework_tint(firework_stage);
        #endif

        // set next stage count (16 to 64 in increment of 8)
        firework_stage_count = 16 + 8 * (pseudo_rand() % 7);
        return;
    }


    // wind up to explode
    set_level(firework_stage);
    nice_delay_ms(step_interval/3);
    set_level((uint16_t)firework_stage*2/3);
    nice_delay_ms(step_interval/3);
    firework_stage++;

    // we've reached our max brightness for firework mode, let's explode in the next iteration
    if (firework_stage > firework_brightness)
        firework_stage = firework_stage_count;

}
#endif






#ifdef USE_LIGHTHOUSE_MODE

// phase is between 0~255, returns MAX_LEVEL at 128 and 1 at both ends

uint8_t lighthouse_intensity(uint8_t phase) {

    if (phase > 127)
        phase = 256 - phase;

    const uint64_t maxOutput = MAX_LEVEL - 1;

    // power of 4 (quartic function)

    return (uint8_t)(maxOutput * phase / 128 * phase / 128 * phase / 128 * phase / 128) + 1;
}



inline void lighthouse_iter() {

    uint8_t brightness = lighthouse_intensity(lighthouse_phase++);

    set_level(brightness);
    

    if (lighthouse_phase == 0) {
        set_level(0);
        nice_delay_ms(1000 * lighthouse_delay);
    } else
        nice_delay_ms(10 + lighthouse_delay);

}
#endif






#ifdef USE_BAD_FLUORESCENT_MODE

inline void bad_fluorescent_iter() {

    // broken fluorescent
    // even index: light off, odd index: light on
    // unit: 10ms or -1 means random number (10~500ms) generated at boot

    static const int8_t fluorescent_pattern[] = {1,4, -1,2, 5,3, -1,5, 7,27, 1,5, 3,10, -1,20, 3,-1, 2,-1, 10,-1, -1,-1, 1};


    fluoresent_ramp_up_increment++;

    if ((fluorescent_pattern[fluoresent_flicker_index] == -1 && fluoresent_ramp_up_increment == fluoresent_flicker_random) ||
        (fluorescent_pattern[fluoresent_flicker_index] == fluoresent_ramp_up_increment)) {

        fluoresent_flicker_index++;

        fluoresent_ramp_up_increment = 0;

        set_level(fluoresent_flicker_index & 1 ? fluoresent_brightness >> (pseudo_rand()&1): 0);
    }


    if (fluoresent_flicker_index == sizeof(fluorescent_pattern)) {

        fluoresent_flicker_index = 0;

        fluoresent_flicker_random = pseudo_rand()%50 + 1;
    }

    nice_delay_ms(10);
}
#endif






#ifdef USE_TINT_RAMPING

inline void tint_alt_iter() {

    if (tint_locked) return;

    tint = (tint == 1) ? 254 : 1; 
    set_level(tint_alt_brightness);
    nice_delay_ms(500 * tint_alt_interval);
}



inline void tint_smooth_ramp_iter() {

    if (tint_locked) return;
    
    static uint8_t tint_step = 1;

    if (tint == 254) tint_step = -1;

    else if (tint == 1) tint_step = 1;

    tint += tint_step;

    set_level(tint_smooth_brightness);

    nice_delay_ms(tint_smooth_pause);

}
#endif



/////////////////////////////////////////////////////////////



#ifdef USE_CANDLE_MODE
#include "anduril/candle-mode.c"
#endif




#ifdef USE_BORING_STROBE_STATE
#include "anduril/ff-strobe-modes.c"
#endif



///   END   
