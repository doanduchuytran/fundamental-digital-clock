#include "max7219.h"

void init_MAX7219(void)
{
	// decoder MODE all led
	set_bit(gpioc_pcor, 15);
	LPSPI0_send_data(0x09FF);
	set_bit(gpioc_psor, 15);
	
	//brightness setting
	set_bit(gpioc_pcor, 15);
	LPSPI0_send_data(0x0A04);
	set_bit(gpioc_psor, 15);
	
	// scan limit
	set_bit(gpioc_pcor, 15);
	LPSPI0_send_data(0x0B07);
	set_bit(gpioc_psor, 15);
	
	// display test
	set_bit(gpioc_pcor, 15);
	LPSPI0_send_data(0x0F00);
	set_bit(gpioc_psor, 15);
	
	// shutdown MODE
	set_bit(gpioc_pcor, 15);
	LPSPI0_send_data(0x0C01);
	set_bit(gpioc_psor, 15);
}


void display_time(void)
{
	/********************************************
	DISPLAY HOUR
	********************************************/
	/*First digit*/
	set_bit(gpioc_pcor, 15);
	LPSPI0_send_data((0x08 << 8)|(hour / 10));
	set_bit(gpioc_psor, 15);
	/*Second digit*/
	set_bit(gpioc_pcor, 15);
	LPSPI0_send_data((0x07 << 8)|(hour % 10));
	set_bit(gpioc_psor, 15);
	/*- symbol*/
	set_bit(gpioc_pcor, 15);
	LPSPI0_send_data(0x060A);
	set_bit(gpioc_psor, 15);
	
	/********************************************
	DISPLAY MINUTE
	********************************************/
	/*First digit*/
	set_bit(gpioc_pcor, 15);
	LPSPI0_send_data((0x05 << 8)|(minute / 10));
	set_bit(gpioc_psor, 15);
	/*Second digit*/
	set_bit(gpioc_pcor, 15);
	LPSPI0_send_data((0x04 << 8)|(minute % 10));
	set_bit(gpioc_psor, 15);
	/*- symbol*/
	set_bit(gpioc_pcor, 15);
	LPSPI0_send_data(0x030A);
	set_bit(gpioc_psor, 15);
	
	/********************************************
	DISPLAY SECOND
	********************************************/
	/*First digit*/
	set_bit(gpioc_pcor, 15);
	LPSPI0_send_data((0x02 << 8)|(second / 10));
	set_bit(gpioc_psor, 15);
	/*Second digit*/
	set_bit(gpioc_pcor, 15);
	LPSPI0_send_data((0x01 << 8)|(second % 10));
	set_bit(gpioc_psor, 15);
}

void display_date(void)
{
	/********************************************
	DISPLAY DAY
	********************************************/
	/*First digit*/
	set_bit(gpioc_pcor, 15);
	LPSPI0_send_data((0x08 << 8)|(day / 10));
	set_bit(gpioc_psor, 15);
	/*Second digit*/
	set_bit(gpioc_pcor, 15);
	LPSPI0_send_data((0x07 << 8)|(day % 10)|(1 << 7));
	set_bit(gpioc_psor, 15);
	
	/********************************************
	DISPLAY MONTH
	********************************************/
	/*First digit*/
	set_bit(gpioc_pcor, 15);
	LPSPI0_send_data((0x06 << 8)|(month / 10));
	set_bit(gpioc_psor, 15);
	/*Second digit*/
	set_bit(gpioc_pcor, 15);
	LPSPI0_send_data((0x05 << 8)|(month % 10)|(1 << 7));
	set_bit(gpioc_psor, 15);
	
	
	/********************************************
	DISPLAY YEAR
	********************************************/
	/*1th digit*/
	set_bit(gpioc_pcor, 15);
	LPSPI0_send_data((0x04 << 8)|(year / 1000));
	set_bit(gpioc_psor, 15);
	/*2th digit*/
	set_bit(gpioc_pcor, 15);
	LPSPI0_send_data((0x03 << 8)|((year / 1000) /100));
	set_bit(gpioc_psor, 15);
	/*3th digit*/
	set_bit(gpioc_pcor, 15);
	LPSPI0_send_data((0x02 << 8)|(year % 1000 % 100 / 10));
	set_bit(gpioc_psor, 15);
	/*4th digit*/
	set_bit(gpioc_pcor, 15);
	LPSPI0_send_data((0x01 << 8)|(year % 1000 % 100 % 10));
	set_bit(gpioc_psor, 15);
}

void display_default(void)
{
	/********************************************
	DISPLAY HOUR
	********************************************/
	/*First digit*/
	set_bit(gpioc_pcor, 15);
	LPSPI0_send_data((0x08 << 8)|(0 / 10));
	set_bit(gpioc_psor, 15);
	/*Second digit*/
	set_bit(gpioc_pcor, 15);
	LPSPI0_send_data((0x07 << 8)|(0 % 10));
	set_bit(gpioc_psor, 15);
	/*- symbol*/
	set_bit(gpioc_pcor, 15);
	LPSPI0_send_data(0x060A);
	set_bit(gpioc_psor, 15);
	
	/********************************************
	DISPLAY MINUTE
	********************************************/
	/*First digit*/
	set_bit(gpioc_pcor, 15);
	LPSPI0_send_data((0x05 << 8)|(0 / 10));
	set_bit(gpioc_psor, 15);
	/*Second digit*/
	set_bit(gpioc_pcor, 15);
	LPSPI0_send_data((0x04 << 8)|(0 % 10));
	set_bit(gpioc_psor, 15);
	/*- symbol*/
	set_bit(gpioc_pcor, 15);
	LPSPI0_send_data(0x030A);
	set_bit(gpioc_psor, 15);
	
	/********************************************
	DISPLAY SECOND
	********************************************/
	/*First digit*/
	set_bit(gpioc_pcor, 15);
	LPSPI0_send_data((0x02 << 8)|(0 / 10));
	set_bit(gpioc_psor, 15);
	/*Second digit*/
	set_bit(gpioc_pcor, 15);
	LPSPI0_send_data((0x01 << 8)|(0 % 10));
	set_bit(gpioc_psor, 15);
}
