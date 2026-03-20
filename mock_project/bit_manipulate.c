#include "bit_manipulate.h"

/* Fucntion to clear a bit of a variable*/
void clear_bit(unsigned int* address_of_variable, unsigned char position)
{
	*address_of_variable = *address_of_variable & ~(1 << position);
}
/* Function to set a bit of a variable*/
void set_bit(unsigned int* address_of_variable, unsigned char position)
{
	*address_of_variable = *address_of_variable | (1 << position);
}
/* Function to toggle a bit of a variable*/
void toggle_bit(unsigned int* address_of_variable, unsigned char position)
{
	*address_of_variable = *address_of_variable ^ (1 << position);
}
