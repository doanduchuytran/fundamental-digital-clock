#include "led.h"

unsigned int* gpiod_psor = (unsigned int*) (GPIOD_BASE_ADDRESS + PSOR_OFFSET);
unsigned int* gpiod_pcor = (unsigned int*) (GPIOD_BASE_ADDRESS + PCOR_OFFSET);

BLINK_LED_STATUS blink_led_status = INIT;

void config_led(void)
{
	static unsigned int* portd_pcr15 = (unsigned int*) (PORTD_PCR_BASE_ADDRESS + PORT_PCR15_OFFSET);
	static unsigned int* gpiod_pddr = (unsigned int*) (GPIOD_BASE_ADDRESS + PDDR_OFFSET);
	/**/
	set_bit(portd_pcr15, 8); 			/* Set PTD15 (led red) as GPIO*/
	set_bit(gpiod_pddr, 15); 			/* set PTD15 as output*/
	clear_bit(portd_pcr15, 1);  	/* Disable pullup/pulldown resistor of PTD15*/
}


void blink_led(void)
{
	switch(blink_led_status)
	{
		case INIT:
			set_bit(gpiod_psor, 15);	/*Turn off the red led*/
			blink_led_status = ON;
			setTimer1(1000);
			break;
		case ON:
			set_bit(gpiod_pcor, 15);
			if(timer1_flag == 1)
			{
				blink_led_status = OFF;
				setTimer1(1000);
			}
			break;
		case OFF:
			set_bit(gpiod_psor, 15);	/*Turn off the red led*/
			if(timer1_flag == 1)
			{
				blink_led_status = ON;
				setTimer1(1000);
			}
			break;
	}
}
