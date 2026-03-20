#ifndef _LED_H_
#define _LED_H_

#include "global.h"

#define PORTD_PCR_BASE_ADDRESS	0X4004C000u

#define PORT_PCR15_OFFSET	0x3Cu

#define GPIOD_BASE_ADDRESS 	0x400FF0C0u


#define PDDR_OFFSET	0x14u		/* Port data direction register*/
#define PCOR_OFFSET 0x8u		/* Port clear output register*/
#define PSOR_OFFSET	0x4u		/* Port set output register*/
#define PDIR_OFFSET 0x10u		/* Port data input register*/

typedef enum
{
	INIT,
	ON,
	OFF
}BLINK_LED_STATUS;

extern unsigned int* gpiod_psor;
extern unsigned int* gpiod_pcor;

extern BLINK_LED_STATUS blink_led_status;

void config_led(void);

void blink_led(void);

#endif
