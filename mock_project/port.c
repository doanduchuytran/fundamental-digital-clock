#include "port.h"

void enable_clock_for_port(void)
{
	/*Variable to enable clock for port*/
	unsigned int* pcc_portc = (unsigned int*) (PCC_BASE_ADDRESS + PCC_PORTC_OFFSET);
	unsigned int* pcc_portd = (unsigned int*) (PCC_BASE_ADDRESS + PCC_PORTD_OFFSET);
	unsigned int* pcc_portb = (unsigned int*) (PCC_BASE_ADDRESS + PCC_PORTB_OFFSET);

	/* Enable clock for port*/
	set_bit(pcc_portc, 30);				/* Enable clock for port C*/
	set_bit(pcc_portd, 30);				/* Enable clock for port D*/
	set_bit(pcc_portb, 30);				/* Enable clock for port B*/
}
