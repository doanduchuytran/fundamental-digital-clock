#ifndef _MAX7219_H_
#define _MAX7219_H_

#include "global.h"

/*Function to init MAX 7219*/
void init_MAX7219(void);

/*Function to display time on led*/
void display_time(void);

/*Function to display date on led*/
void display_date(void);

/*Display when in init and off state*/
void display_default(void);

#endif
