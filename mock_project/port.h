#ifndef _PORT_H_
#define _PORT_H_

#include "bit_manipulate.h"

/*Constants for enable clock for port*/
#define PCC_BASE_ADDRESS 		0x40065000u
#define PCC_PORTC_OFFSET		0x12Cu
#define PCC_PORTD_OFFSET		0x130u
#define PCC_PORTB_OFFSET		0x128u

void enable_clock_for_port(void);

#endif
