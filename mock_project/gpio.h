#ifndef _GPIO_H_
#define _GPIO_H_

#include "global.h"

/*Constant for configuring pin*/
#define PORTC_PCR_BASE_ADDRESS	0x4004B000u
#define PORT_PCR15_OFFSET	0x3Cu

/*Constants for configuring GPIO*/
#define GPIOC_BASE_ADDRESS	0x400FF080u
#define PDDR_OFFSET	0x14u		/* Port data direction register*/
#define PCOR_OFFSET 0x8u		/* Port clear output register*/
#define PSOR_OFFSET	0x4u		/* Port set output register*/
#define PDIR_OFFSET 0x10u		/* Port data input register*/

extern unsigned int* gpioc_psor;
extern unsigned int* gpioc_pcor;

void configure_gpio(void);

#endif
