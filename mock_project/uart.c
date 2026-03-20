#include "uart.h"

/****************************************************************************************
	VARIABLES DECLRATION AND INITIALIZATION
****************************************************************************************/
//	/*peripheral clock control register*/
//	static unsigned int* pcc_portc = (unsigned int*) (PCC_BASE_ADDRESS + PCC_PORTC_OFFSET);
/*config function for pin*/
static unsigned int* portc_pcr6 = (unsigned int*) (PORTC_PCR + PTC6_PCR_OFFSET);
static unsigned int* portc_pcr7 = (unsigned int*) (PORTC_PCR + PTC7_PCR_OFFSET);
/*config clock for UART*/
static unsigned int* pcc_lpuart1 = (unsigned int*) (PCC_BASE_ADDRESS + PCC_LPUART1_OFFSET);
/* Registers for configuring clock source fast irc*/
//	static unsigned int* fast_irc_control_status_register = (unsigned int*) 0x300u;
static unsigned int* fast_irc_devide_register = (unsigned int*) (SCG_BASE_ADDRESS + SCG_FIRCDIV_OFFSET);
/*config LPUART1*/
//static unsigned int* lpuar1_watermark_register = (unsigned int*) (LPUART1_BASE_ADDRESS + LPUART1_WATERMARK_OFFSET);
static unsigned int* lpuart1_baudrate_register = (unsigned int*) (LPUART1_BASE_ADDRESS + LPUART1_BAUDRATE_OFFSET);
	
	
//	unsigned int* lpuart1_status_register = (unsigned int*) (LPUART1_BASE_ADDRESS + LPUART1_STATUS_OFFSET);
	
/*Variables for config interrupt for module LPUART1*/
static unsigned int* nvic_iser1 = (unsigned int*) NVIC_ISER1;
unsigned int* lpuart1_data_register = (unsigned int*) (LPUART1_BASE_ADDRESS + LPUART1_DATA_OFFSET);
unsigned int* lpuart1_status_register = (unsigned int*) (LPUART1_BASE_ADDRESS + LPUART1_STATUS_OFFSET);
unsigned int* lpuart1_control_register = (unsigned int*) (LPUART1_BASE_ADDRESS + LPUART1_CONTROL_OFFSET);
//static unsigned int* lpuart1_fifo_register = (unsigned int*) (LPUART1_BASE_ADDRESS + LPUART1_FIFO_OFFSET);
//static unsigned int* lpuart1_wartermark_register = (unsigned int*) (LPUART1_BASE_ADDRESS + LPUART1_WATERMARK_OFFSET);

/*Variable to store data received frome LPUART1*/
char receive_data = 0;
char string_of_data[RECEIVE_DATA_BUFFER_SIZE];
unsigned int end_of_receive_flag = 0;
unsigned int i = 0;


void ConfigUart(void)
{
	/****************************************************************************************
	SETTING TX/RX PIN
	****************************************************************************************/
	/*Enable clock for module PORTC is done in port.c*/
	/*set function for PTC6 as UART_Rx and PTC7 as UART_Tx*/
	set_bit(portc_pcr6, 9); /*function of pin is uart_tx -> alternative 2 -> mux = 010*/
	set_bit(portc_pcr7, 9); /*function of pin is uart_tx -> alternative 2 -> mux = 010*/
	
	
	/******************************************************************
	SELECT CLOCK SOURCE FOR LPUART MODULE
	******************************************************************/
	/*Module LPUART use clock source fast ICR and divisor for fast ICR = 1*/
	*fast_irc_devide_register = 0x100u;
	
	/*choose clock source fast irc for module lpuart -> PCS[26:24] = 011*/
	set_bit(pcc_lpuart1, 25);
	set_bit(pcc_lpuart1, 24);
	/* Enable clock for module lpuart*/
	set_bit(pcc_lpuart1, 30);
	
	
	/******************************************************************
	3) SETTING BAUDRATE
	******************************************************************/
//	/* Disable transmitter*/
//	clear_bit(lpuart1_control_register, 19); 
//	/* Disable receiver*/
//	clear_bit(lpuart1_control_register, 18);
	/*baudrate = 9600 -> oversampling ratio = 20 -> baud rate modulo divisor = 250*/
	/*baudrate modulo divisor = 250 -> SBR[12:0] = 250*/
	clear_bit(lpuart1_baudrate_register, 0);
	clear_bit(lpuart1_baudrate_register, 1);
	clear_bit(lpuart1_baudrate_register, 2);
	clear_bit(lpuart1_baudrate_register, 3);
	clear_bit(lpuart1_baudrate_register, 4);
	clear_bit(lpuart1_baudrate_register, 5);
	clear_bit(lpuart1_baudrate_register, 6);
	clear_bit(lpuart1_baudrate_register, 7);
	clear_bit(lpuart1_baudrate_register, 8);
	clear_bit(lpuart1_baudrate_register, 9);
	clear_bit(lpuart1_baudrate_register, 10);
	clear_bit(lpuart1_baudrate_register, 11);
	clear_bit(lpuart1_baudrate_register, 12);
	set_bit(lpuart1_baudrate_register, 1);
	set_bit(lpuart1_baudrate_register, 3);
	set_bit(lpuart1_baudrate_register, 4);
	set_bit(lpuart1_baudrate_register, 5);
	set_bit(lpuart1_baudrate_register, 6);
	set_bit(lpuart1_baudrate_register, 7);
	/*set oversampling ratio = 20 -> OSR[28:24] = 10011*/
	clear_bit(lpuart1_baudrate_register, 26);
	clear_bit(lpuart1_baudrate_register, 27);
	set_bit(lpuart1_baudrate_register, 24);
	set_bit(lpuart1_baudrate_register, 25);
	set_bit(lpuart1_baudrate_register, 28);
	
	
	/**************************************************************************************
	4) SETTING FRAME
	**************************************************************************************/
	/* Select number of stop bit*/
	clear_bit(lpuart1_baudrate_register, 13); /* 13th bit = 0 -> dataframe has only 1 stop bit*/
	/* Set the number of data character*/
	clear_bit(lpuart1_control_register, 4); /* 4th bit = 0 -> dataframe has 8-bit data*/
	/* Set parity bit*/
	clear_bit(lpuart1_control_register, 1); /* disable parity*/
		
	/**************************************************************************************
	5) ENABLE TRANSMITTER/RECEIVER
	**************************************************************************************/
	/* Enable transmitter*/
	set_bit(lpuart1_control_register, 19); 
	/* Enable receiver*/
	set_bit(lpuart1_control_register, 18);
}


void ConfigInterruptUart(void)
{
	/****************************************************************************************
	CONFIG INTERRUPT FOR MODULE LPUART
	****************************************************************************************/
	set_bit(nvic_iser1, 1);	/*Enable interrupt for module LPUART1*/
	
	/****************************************************************************************
	SETTING TX/RX PIN
	****************************************************************************************/
	/*Enable clock for module PORTC is done in port.c*/
	/*set function for PTC6 as UART_Rx and PTC7 as UART_Tx*/
	set_bit(portc_pcr6, 9); /*function of pin is uart_tx -> alternative 2 -> mux = 010*/
	set_bit(portc_pcr7, 9); /*function of pin is uart_tx -> alternative 2 -> mux = 010*/
	
	
	/******************************************************************
	SELECT CLOCK SOURCE FOR LPUART MODULE
	******************************************************************/
	/*Module LPUART use clock source fast ICR and divisor for fast ICR = 1*/
	*fast_irc_devide_register = 0x100u;
	
	/*choose clock source fast irc for module lpuart -> PCS[26:24] = 011*/
	set_bit(pcc_lpuart1, 25);
	set_bit(pcc_lpuart1, 24);
	/* Enable clock for module lpuart*/
	set_bit(pcc_lpuart1, 30);
	
	
	/******************************************************************
	SETTING BAUDRATE
	******************************************************************/
//	/* Disable transmitter*/
//	clear_bit(lpuart1_control_register, 19); 
//	/* Disable receiver*/
//	clear_bit(lpuart1_control_register, 18);
	/*baudrate = 9600 -> oversampling ratio = 20 -> baud rate modulo divisor = 250*/
	/*baudrate modulo divisor = 250 -> SBR[12:0] = 250*/
	clear_bit(lpuart1_baudrate_register, 0);
	clear_bit(lpuart1_baudrate_register, 1);
	clear_bit(lpuart1_baudrate_register, 2);
	clear_bit(lpuart1_baudrate_register, 3);
	clear_bit(lpuart1_baudrate_register, 4);
	clear_bit(lpuart1_baudrate_register, 5);
	clear_bit(lpuart1_baudrate_register, 6);
	clear_bit(lpuart1_baudrate_register, 7);
	clear_bit(lpuart1_baudrate_register, 8);
	clear_bit(lpuart1_baudrate_register, 9);
	clear_bit(lpuart1_baudrate_register, 10);
	clear_bit(lpuart1_baudrate_register, 11);
	clear_bit(lpuart1_baudrate_register, 12);
	set_bit(lpuart1_baudrate_register, 1);
	set_bit(lpuart1_baudrate_register, 3);
	set_bit(lpuart1_baudrate_register, 4);
	set_bit(lpuart1_baudrate_register, 5);
	set_bit(lpuart1_baudrate_register, 6);
	set_bit(lpuart1_baudrate_register, 7);
	/*set oversampling ratio = 20 -> OSR[28:24] = 10011*/
	clear_bit(lpuart1_baudrate_register, 26);
	clear_bit(lpuart1_baudrate_register, 27);
	set_bit(lpuart1_baudrate_register, 24);
	set_bit(lpuart1_baudrate_register, 25);
	set_bit(lpuart1_baudrate_register, 28);
	
	/**************************************************************************************
	SETTING DATAFRAME
	**************************************************************************************/
	/* Select number of stop bit*/
	clear_bit(lpuart1_baudrate_register, 13); /* 13th bit = 0 -> dataframe has only 1 stop bit*/
	/* Set the number of data character*/
	clear_bit(lpuart1_control_register, 4); /* 4th bit = 0 -> dataframe has 8-bit data*/
	/* Set parity bit*/
	clear_bit(lpuart1_control_register, 1); /* disable parity*/
	
	/**************************************************************************************
	ENABLE RECEIVER INTERRUPT
	**************************************************************************************/
	set_bit(lpuart1_control_register, 21);
	
//	/**************************************************************************************
//	SETTING LPUART FIFO REGISTER
//	**************************************************************************************/
//	set_bit(lpuart1_fifo_register, 0);	/*FIFO[RXFIFOSIZE] = 001 -> size = 4 datawords*/
//	set_bit(lpuart1_fifo_register, 3); 	/*Enable Receive FIFO*/
//	
//	/**************************************************************************************
//	SETTING LPUART WATERMARK REGISTER
//	**************************************************************************************/
//	set_bit(lpuart1_wartermark_register, 16);
//	set_bit(lpuart1_wartermark_register, 17);
	
	/**************************************************************************************
	ENABLE TRANSMITTER/RECEIVER
	**************************************************************************************/
	/* Enable transmitter*/
	set_bit(lpuart1_control_register, 19); 
	/* Enable receiver*/
	set_bit(lpuart1_control_register, 18);
}

void LPUART1_transmit_char(char data)
{
	/*Wait for transmit data buffer empty*/
	while((*lpuart1_status_register & (1 << 23)) == 0);
	/*Send data*/
	*lpuart1_data_register = data;
}

void LPUART1_transmit_string(char string[])
{
	unsigned int i_transmit_string = 0;
	while(string[i_transmit_string] != '\0')
	{
		LPUART1_transmit_char(string[i_transmit_string]);
		i_transmit_string++;
		set_bit(lpuart1_status_register, 23);
	}
}

void LPUART1_interrupt_receive_char(void)
{
	/*Store character that is received from lpuart1 rx*/
	receive_data = (char) *lpuart1_data_register;
}

unsigned int isEndOfReceive(void)
{
	if(end_of_receive_flag == 1)
	{
		end_of_receive_flag = 0;
		return 1;
	}
	else{
		return 0;
	}
}

void LPUART1_interrupt_receive_string(void)
{
	string_of_data[i] = (char) *lpuart1_data_register;
	i++;
}
/*
This function is called when RDRF flag = 1 (data buffer is full)
RDRF is clear when read the LPUART1 Data register
*/
void LPUART1_RxTx_IRQHandler(void)
{
	LPUART1_interrupt_receive_string();
}
