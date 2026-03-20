#ifndef _MAIN_SYSTEM_H_
#define _MAIN_SYSTEM_H_

#include "global.h"

/*Variables to be displayed*/
extern char string_of_time[];
extern char string_of_date[];
extern unsigned int hour;
extern unsigned int minute;
extern unsigned int second;
extern unsigned int day;
extern unsigned int month;
extern unsigned int year;

typedef enum
{
	MAIN_SYSTEM_INIT,
	DISPLAY_TIME,
	DISPLAY_DATE,
	SETTING_TIME,
	SETTING_DATE,
	OFF_1,
	OFF_2
}MAIN_SYSTEM_STATUS;

/*This the main fsm for the main system*/
void main_system(void);

/*Function to get value of time from uart*/
void get_value_time(void);

/*Function to get value of date from uart*/
void get_value_date(void);

/*Function to update value of time and date*/
void update_value_time_date(void);

/*Function to get sting of time*/
void get_string_time(void);

/*Function to get string of date*/
void get_string_date(void);


#endif
