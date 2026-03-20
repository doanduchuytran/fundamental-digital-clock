#include "button.h"

/********************************************************
GLOBAL VARIABLE
********************************************************/
int button3_flag = 0;
int button2_flag = 0;
unsigned int* gpioc_pdir = (unsigned int*) (GPIOC_BASE_ADDRESS + PDIR_OFFSET);

void config_button(void)
{
	/*Variables to config function of pin*/
	unsigned int* portc_pcr13 = (unsigned int*) (PORTC_PCR_BASE_ADDRESS + PCR13_OFFSET);	/* PORTC_PCR13 register*/
	unsigned int* portc_pcr12 = (unsigned int*) (PORTC_PCR_BASE_ADDRESS + PCR12_OFFSET); 	/* PORTC_PCR12 register*/
	/*Variables to config GPIO*/
	unsigned int* gpioc_pddr = (unsigned int*) (GPIOC_BASE_ADDRESS + PDDR_OFFSET);
	/*Variables to config interrupt for port*/
//	static unsigned int* nvic_iser1 = (unsigned int*) NVIC_ISER1;
	
	/* Config button 3 - PTC13*/
	set_bit(portc_pcr13, 8);			/* Set PTC13 as GPIO*/
//	set_bit(portc_pcr13, 1);			/* Enable pullup/pulldown registor*/
//	clear_bit(portc_pcr13, 0);		/* Select pull down registor*/
//	set_bit(portc_pcr13, 17);			/* IQRQ = 1010 -> interrupt on falling edge*/
//	set_bit(portc_pcr13, 19);			/* IQRQ = 1010 -> interrupt on falling edge*/
	clear_bit(gpioc_pddr, 13);		/* Set PTC13 as input*/
	
	/* Config button 2 - PTC12*/
	set_bit(portc_pcr12, 8);			/* Set PTC13 as GPIO*/
//	set_bit(portc_pcr12, 1);			/* Enable pullup/pulldown registor*/
//	clear_bit(portc_pcr12, 0);		/* Select pull down registor*/
//	set_bit(portc_pcr12, 17);			/* IQRQ = 1010 -> interrupt on falling edge*/
//	set_bit(portc_pcr12, 19);			/* IQRQ = 1010 -> interrupt on falling edge*/
	clear_bit(gpioc_pddr, 12);		/* Set PTC13 as input*/
	
//	/* Enable interrupt for port c*/
//	set_bit(nvic_iser1, 27);			/* Enable interrupt for port A*/
//	set_bit(nvic_iser1, 28); 			/* Enable interrupt for port B*/
//	set_bit(nvic_iser1, 29);			/* Enable interrupt for port C*/
}

int isButtonPressed_3(void)
{
	if(*gpioc_pdir & (1 << 13))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int isButtonPressed_2(void)
{
	if(*gpioc_pdir & (1 << 12))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


