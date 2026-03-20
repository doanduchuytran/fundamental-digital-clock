#include "clock.h"

void clock_init(void)
{
	unsigned int* fastirc_divide_register = (unsigned int*) (SCG_BASE_ADDRESS + FIRDIV_OFFSET);
	
	/*divider for fircdiv_2 = 1*/
	set_bit(fastirc_divide_register, 8);
}
