#ifndef _CLOCK_H_
#define _CLOCK_H_

#include "global.h"

#define SCG_BASE_ADDRESS	0x40064000u

#define FIRDIV_OFFSET			0x304u

/*Function to enable clock FIRCDIV_2*/
void clock_init(void);

#endif
