#include "gpio.h"

unsigned int* gpioc_psor = (unsigned int*) (GPIOC_BASE_ADDRESS + PSOR_OFFSET);
unsigned int* gpioc_pcor = (unsigned int*) (GPIOC_BASE_ADDRESS + PCOR_OFFSET);

void configure_gpio(void)
{
	static unsigned int* portc_pcr15 = (unsigned int*) (PORTC_PCR_BASE_ADDRESS + PORT_PCR15_OFFSET);
	static unsigned int* gpioc_pddr = (unsigned int*) (GPIOC_BASE_ADDRESS + PDDR_OFFSET);
	/**/
	set_bit(portc_pcr15, 8); 			/* Set PTC15 as GPIO*/
	set_bit(gpioc_pddr, 15); 			/* set PTC15 as output*/
	clear_bit(portc_pcr15, 1);  	/* Disable pullup/pulldown resistor of PTD15*/
}
