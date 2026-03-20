#include "main_system.h"

/*Variables to be displayed*/
char string_of_time[9];
char string_of_date[11];
unsigned int hour = 4;
unsigned int minute = 4;
unsigned int second = 4;

unsigned int day = 0;
unsigned int month = 0;
unsigned int year = 0;

static MAIN_SYSTEM_STATUS main_system_status = MAIN_SYSTEM_INIT;

void main_system(void)
{
	switch(main_system_status)
	{
		case MAIN_SYSTEM_INIT:
			display_default();
			if(isButtonPressed_2() == 1)
			{
				main_system_status = SETTING_TIME;
			}
			break;
		case DISPLAY_TIME:
			display_time();
			if(isButtonPressed_3() == 1)
			{
				main_system_status = DISPLAY_DATE;
			}
			if(isButtonPressed_2() == 1)
			{
				main_system_status = OFF_1;
			}
			break;
		case DISPLAY_DATE:
			display_date();
			if(isButtonPressed_3() == 1)
			{
				main_system_status = DISPLAY_TIME;
			}
			if(isButtonPressed_2() == 1)
			{
				main_system_status = OFF_2;
			}
			break;
		case SETTING_TIME:
			display_time();
			get_value_time();
			if(isButtonPressed_2() == 1)
			{
				memset(string_of_data, 0, RECEIVE_DATA_BUFFER_SIZE);
				i = 0;
				main_system_status = SETTING_DATE;
			}
			break;
		case SETTING_DATE:
			display_date();
			get_value_date();
			if(isButtonPressed_2() == 1)
			{
				memset(string_of_data, 0, RECEIVE_DATA_BUFFER_SIZE);
				i = 0;
				main_system_status = DISPLAY_TIME;
			}
			break;
		case OFF_1:
			/*Turn off*/
			display_default();
			if(isButtonPressed_2() == 1)
			{
				main_system_status = DISPLAY_TIME;
			}
			break;
		case OFF_2:
			/*Turn off*/
			display_default();
			if(isButtonPressed_2() == 1)
			{
				main_system_status = DISPLAY_DATE;
			}
			break;
	}
}

void get_value_time(void)
{
    char string_of_hour[3];
    char string_of_minute[3];
    char string_of_second[3];

    strncpy(string_of_hour, string_of_time + 0, 2);
    hour = (unsigned int) atoi(string_of_hour);

    strncpy(string_of_minute, string_of_time + 3, 2);
    minute = (unsigned int) atoi(string_of_minute);

    strncpy(string_of_second, string_of_time + 6, 2);
    second = (unsigned int) atoi(string_of_second);
}

void get_value_date(void)
{
    char string_of_day[3];
    char string_of_month[3];
    char string_of_year[5];

    strncpy(string_of_day, string_of_date + 0, 2);
    day = (unsigned char) atoi(string_of_day);

    strncpy(string_of_month, string_of_date + 3, 2);
    month = (unsigned char) atoi(string_of_month);

    strncpy(string_of_year, string_of_date + 6, 4);
    year = (unsigned char) atoi(string_of_year);
}

void update_value_time_date(void)
{
	if(timer2_flag == 1)
	{
		setTimer2(1000);
		second++;
		if(second == 60)
		{
			minute++;
			second = 0;
		}
		if(minute == 60)
		{
			hour++;
			minute = 0;
		}
		if(hour == 24)
		{
			day++;
			hour = 0;
		}
		if(day == 31)
		{
			month++;
			day = 0;
		}
		if(month == 12)
		{
			year++;
			month = 0;
		}
	}
}
