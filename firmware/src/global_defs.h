/* 
 * File:   global_defs.h
 * Author: Mike
 *
 * Created on March 15, 2023
 */

#ifndef GLOBAL_DEFS_H
#define	GLOBAL_DEFS_H

#ifdef	__cplusplus
extern "C" {
#endif

//Stuff for 8 bit processors
//#pragma warning disable 520  // Turns off the Function Not Called Warning
//#pragma warning disable 2053  // Turns off the Function Not Called Warning - Inline functions
    
//#include "mcc_generated_files/system/system.h"
//#include <xc.h>
    
    
    
#include <stdint.h>
#include <stdbool.h>
    
#define TRUE 1
#define FALSE 0

    
#define HEARTBEAT_INTERVAL  (0.01)  // seconds for interrupt from systick timer
#define LED_HEARTBEAT_INTERVAL 20  // Interval for heartbeat tick - 50 = 500ms @ 10ms tick
#define RGB_LED_HEARTBEAT_INTERVAL 110 // Interval for the RGB LEDs
#define BUTTON_DEBOUNCE_INTERVAL   4  // Debouce time 4=40ms
#define BUTTON_DEBOUNCE_MASK (0b00001111)  // This goes with above number
#define BUTTON_INTERVAL_CHECK   1 // How often to check the button, this goes with the above define to set the debounce time

    //LED Flash times
#define FLASH_ON_TIME   10  // In increments of 10ms SysTicks -10 = 100ms
#define FLASH_OFF_TIME  10  // In increments of 10ms SysTicks -10 = 100ms

#define GRN_LED_OFF  GRN_LED_SetLow()
#define GRN_LED_ON   GRN_LED_SetHigh()

#ifdef	__cplusplus
}
#endif

#endif	/* GLOBAL_DEFS_H */

