/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include <string.h>                     // for strlen
#include "definitions.h"
#include "misc.h"                // SYS function prototypes


uint32_t w_i;
size_t Status;
uint8_t WrBuffer[32];


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    
    // Start the timer for systick
    //w_i = SysTick; // This is for my testing
    TC0_TimerStart();
    
    // Start the SysTick System timer
    SYSTICK_TimerStart();
    
    
    // Register Timer Interrupt Callback
    TC0_TimerCallbackRegister( IncSysTick, (uintptr_t)NULL );
    
    // Register the SysTick Interrupt Callback
    SYSTICK_TimerCallbackSet( IncSecondSysTick, (uintptr_t) NULL );

    
    // Start with Green on, so they blink opposite
    //RGB_LED_GREEN_On();
    
  
        
    w_i = sprintf((char*)WrBuffer, "Hello World!\r\n");
    Status = SERCOM0_USART_Write(WrBuffer, w_i );
    
    // another way to write it out
    Status = SERCOM0_USART_Write((uint8_t*)"Another Hellow World...", sizeof("Another Hellow World...")-1); // Take off 1 - counts the null at end
        
    
    
    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
        DoHeartBeat();
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

