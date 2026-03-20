#include "main.h"
#include "port.h"
#include "bit_manipulate.h"
#include "button.h"
#include "software_timer.h"
#include "led.h"
#include "string.h"
#include "stdlib.h"
#include "uart.h"
#include "clock.h"
#include "max7219.h"
#include "gpio.h"
#include "spi.h"

int main(void)
{
	enable_clock_for_port();
	config_led();
	config_button();
	config_systick_timer();
	ConfigInterruptUart();
	
	clock_init();
	config_lpspi0();
	configure_gpio();
	init_MAX7219();
	
	
	set_bit(gpiod_psor, 15); /*Turn off the red led*/
//	set_bit(gpiod_pcor, 15); /*Turn on the red led*/
	setTimer2(1000);
	while(1)
	{
//		update_value_time_date();
//		main_system();
//		display_date();
		display_time();
	}
}
