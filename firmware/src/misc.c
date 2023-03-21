/* ************************************************************************** */
/** Misc Functions

  @Company
    SupraTech

  @File Name
    misc.c

  @Summary
    Misc functions - timers, etc.

  @Description
    Various button handling functions
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */


#include "definitions.h" 
#include "global_defs.h"



/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

/* ************************************************************************** */
/** Descriptive Data Item Name

  @Summary
    Brief one-line summary of the data item.
    
  @Description
    Full description, explaining the purpose and usage of data item.
    <p>
    Additional description in consecutive paragraphs separated by HTML 
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
    
  @Remarks
    Any additional remarks
 */
static uint16_t MySysTick = 0, FlashTick = 0, SecondSysTick = 0;
static uint16_t Heartbeat_tmr, Second_Heartbeat_tmr;
static uint8_t LED_Heartbeat_tmr;
static uint8_t HighVoltage_tmr = 0;
static uint8_t PWMDuty;
static uint8_t f_New_Sequence_Start;
static uint8_t Flash_Mode, st_Flash; 


enum FlashStates
{
    START = 0,
    FIRST_ON,
    FIRST_OFF,
    SECOND_ON,
    SECOND_OFF,
    FULL_ON
};

enum FlashModes
{
    FLASH_OFF = 0,
    FLASH_25,  // 25 percent full - 1 flash
    FLASH_50,
    FLASH_FULL
};

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

/* ************************************************************************** */

/** 
  @Function
    int ExampleLocalFunctionName ( int param1, int param2 ) 

  @Summary
    Brief one-line description of the function.

  @Description
    Full description, explaining the purpose and usage of the function.
    <p>
    Additional description in consecutive paragraphs separated by HTML 
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.

  @Precondition
    List and describe any required preconditions. If there are no preconditions,
    enter "None."

  @Parameters
    @param param1 Describe the first parameter to the function.
    
    @param param2 Describe the second parameter to the function.

  @Returns
    List (if feasible) and describe the return values of the function.
    <ul>
      <li>1   Indicates an error occurred
      <li>0   Indicates an error did not occur
    </ul>

  @Remarks
    Describe any special behavior not described above.
    <p>
    Any additional remarks.

  @Example
    @code
    if(ExampleFunctionName(1, 2) == 0)
    {
        return 3;
    }
 */
//static int ExampleLocalFunction(int param1, int param2) {
//    return 0;
//}








/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */


// *****************************************************************************

/** 
  @Function
    IncSysTick 

  @Summary
 Increments the System Tic

  @Remarks
 In SysTic
 */
//void IncSysTick(void)
void IncSysTick( TC_TIMER_STATUS callback, uintptr_t context )
{
    MySysTick++;
    FlashTick++;
}

void IncSecondSysTick(SYSTICK_CALLBACK callback, uintptr_t context)
{
    SecondSysTick++;
}

/** 
  @Function
    ClearSysTick 

  @Summary
 Clears the System Tic

  @Remarks
 Clear SysTic
 */
void ClearSysTick(void)
{
    MySysTick = 0;
}

// *****************************************************************************

/** 
  @Function
    GetSysTick 

  @Summary
    Gets the current SysTick

  @Remarks
    Get and return current SysTick
 */
uint16_t GetSysTick(void)
{
    //uint16_t retval;

    //PIE3bits.TMR0IE = 0; // Shut off interrupt
    //retval = MySysTick;
    //PIE3bits.TMR0IE = 1; // turn on interrupt
    return MySysTick;  // Is this atomic on this processor or do we have to disable interrupts
}


/** 
  @Function
    GetSecondSysTick 

  @Summary
    Gets the current Actual SysTick

  @Remarks
    Get and return current SysTick
 */
uint16_t GetSecondSysTick(void)
{
    //uint16_t retval;

    //PIE3bits.TMR0IE = 0; // Shut off interrupt
    //retval = MySysTick;
    //PIE3bits.TMR0IE = 1; // turn on interrupt
    return SecondSysTick;  // Is this atomic on this processor or do we have to disable interrupts
}
// *****************************************************************************

/** 
  @Function
    DoHeartBeat 

  @Summary
 * Does any heartbeat related tasks - blink LED, etc

  @Remarks
 *  Heartbeat Stuff
 */

void DoHeartBeat()
{
    static size_t counter = 0;
    
    // Heartbeat check - Also the Blink Status of the LED
    if((uint16_t)(GetSysTick() - Heartbeat_tmr) >= LED_HEARTBEAT_INTERVAL)
    {
        Heartbeat_tmr = GetSysTick(); // get new time val
        
        USER_LED_Toggle();  // Toggle the Blue LED
        //RGB_LED_BLUE_Toggle();
        
    } // End LED Beat
    
    // Second version doing it with SysTick
    if((uint16_t)(GetSecondSysTick() - Second_Heartbeat_tmr) >= RGB_LED_HEARTBEAT_INTERVAL)
    {
        Second_Heartbeat_tmr = GetSecondSysTick(); // get new time val
        switch(counter)
        {
            case 0:
            {
                RGB_LED_RED_On();
                RGB_LED_GREEN_Off();
                RGB_LED_BLUE_Off();
                counter = 1;
                break;
            }
            case 1:
            {
                RGB_LED_RED_On();
                RGB_LED_GREEN_On();
                RGB_LED_BLUE_Off();
                counter = 2;
                break;
            }
            case 2:
            {
                RGB_LED_RED_Off();
                RGB_LED_GREEN_On();
                RGB_LED_BLUE_Off();
                counter = 3;
                break;
            }
            case 3:
            {
                RGB_LED_RED_Off();
                RGB_LED_GREEN_On();
                RGB_LED_BLUE_On();
                counter = 4;
                break;
            }
            case 4:
            {
                RGB_LED_RED_Off();
                RGB_LED_GREEN_Off();
                RGB_LED_BLUE_On();
                counter = 5;
                break;
            }
            case 5:
            {
                RGB_LED_RED_On();
                RGB_LED_GREEN_Off();
                RGB_LED_BLUE_On();
                counter = 0;
                break;
            }
            default:
            {
                counter = 0;
                break;
            }
        }
        //RGB_LED_GREEN_Toggle();
        //RGB_LED_RED_Toggle();
        
    } // End LED Beat
    
}  // end heartbeat
    


/* *****************************************************************************
 End of File
 */
