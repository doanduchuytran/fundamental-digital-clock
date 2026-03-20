#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "bit_manipulate.h"

/********************************************************
CONSTANT DECLARATION
********************************************************/
/*Constants for configuring pin*/
#define PORTC_PCR_BASE_ADDRESS	0x4004B000u
#define PCR12_OFFSET	0x30u
#define PCR13_OFFSET 	0x34u

/*Constants for configuring GPIO*/
#define GPIOC_BASE_ADDRESS	0x400FF080u
#define PDDR_OFFSET	0x14u		/* Port data direction register*/
#define PCOR_OFFSET 0x8u		/* Port clear output register*/
#define PSOR_OFFSET	0x4u		/* Port set output register*/
#define PDIR_OFFSET 0x10u		/* Port data input register*/

/* Constants to config interrupt for port*/
#define NVIC_ISER1	0xE000E104 /*address of NVIC_ISER1*/


/********************************************************
GLOBAL VARIABLE
********************************************************/
extern int button3_flag;
extern int button2_flag;
extern unsigned int* gpioc_pdir;

/********************************************************
FUNCTION PROTOTYPE
********************************************************/
/* Function to config button*/
void config_button(void);

/**/
int isButtonPressed_3(void);

/**/
int isButtonPressed_2(void);





#endif
