#ifndef _SOFTWARE_TIMER_H_
#define _SOFTWARE_TIMER_H_

#include "global.h"

/****************************************************************
INCLUDE LIBRARY
****************************************************************/
#include "bit_manipulate.h"

/****************************************************************
CONSTANT DECLARATION	
****************************************************************/
/*Constants for configuring the system tick timer*/
#define SYST_CSR_ADDRESS			0xE000E010u		/*Systick Control and Status Register*/
#define SYST_RVR_ADDRESS			0xE000E014u		/*Systick Reload Value Register*/
#define SYST_CVR_ADDRESS			0xE000E018u		/*Systick Current Value Register*/
#define SYST_CALIB_ADDRESS		0xE000E01Cu		/*Systick Calibration Value Register*/
#define NUMBER_OF_CLOCK_CYCLE	479999				/*The number of clock cycles to be counted by the systick timer*/

/*Constants for software_timer*/
#define TICK	10

/****************************************************************
FUNCTION PROTOTYPE
****************************************************************/
/* Function to config system tick timer*/
void config_systick_timer(void);

/* Function to handle systick timer exception*/
void SysTick_Handler(void);

/*Timer 1 for blinking red led*/
extern int timer1_counter;
extern int timer1_flag;

extern int timer2_counter;
extern int timer2_flag;

void setTimer1(int duration);

void setTimer2(int duration);

void timerRun(void);

#endif
