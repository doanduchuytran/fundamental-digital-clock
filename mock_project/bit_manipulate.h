#ifndef _BIT_MANIPULATE_H_
#define _BIT_MANIPULATE_H_

/* Fucntion to clear a bit of a variable*/
void clear_bit(unsigned int* address_of_variable, unsigned char position);
/* Function to set a bit of a variable*/
void set_bit(unsigned int* address_of_variable, unsigned char position);
/* Function to toggle a bit of a variable*/
void toggle_bit(unsigned int* address_of_variable, unsigned char position);

#endif
