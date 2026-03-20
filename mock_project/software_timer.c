#include "software_timer.h"

int timer1_counter = 0;
int timer1_flag = 0;

int timer2_counter = 0;
int timer2_flag = 0;

void config_systick_timer(void)
{
	/*Variables to Config the Systick Timer*/
	static unsigned int* systick_control_status_register = (unsigned int*) SYST_CSR_ADDRESS; 				/*systick control and status register*/
	static unsigned int* systick_reload_value_register = (unsigned int*) SYST_RVR_ADDRESS;					/*systick reload value register*/
	static unsigned int* systick_current_value_register = (unsigned int*) SYST_CVR_ADDRESS;					/*systick current value register*/
	static unsigned int* systick_calibration_value_register = (unsigned int*) SYST_CALIB_ADDRESS;		/*systick calibration value register*/
	
	/*Config systick timer*/
	clear_bit(systick_control_status_register, 0);																/*disable counter*/
	*systick_reload_value_register = (unsigned int) (NUMBER_OF_CLOCK_CYCLE - 1);	/*prgram reload value*/
	*systick_current_value_register = (unsigned int) 0; 													/*clear the current value*/
	set_bit(systick_calibration_value_register, 31);															/*no reference clock provided*/
	set_bit(systick_control_status_register, 2);																	/*choose the clock source*/
	set_bit(systick_control_status_register, 1); 																	/*enable systick exception request*/
	set_bit(systick_control_status_register, 0);
}

/* Function to handle systick timer exception, called every 10ms*/
void SysTick_Handler(void)
{
	timerRun();
}

void setTimer1(int duration)
{
	timer1_counter = duration/TICK;
	timer1_flag = 0;
}

void setTimer2(int duration)
{
	timer2_counter = duration/TICK;
	timer2_flag = 0;
}

void timerRun(void)
{
	if(timer1_counter > 0)
	{
		timer1_counter--;
		if(timer1_counter <= 0)
		{
			timer1_flag = 1;
		}
	}
}
