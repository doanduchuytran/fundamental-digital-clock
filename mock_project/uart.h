#ifndef _UART_H_
#define _UART_H_

#include "global.h"

/*Config clock for PORTC*/
#define PCC_BASE_ADDRESS	0x40065000u
#define PCC_PORTC_OFFSET	0x12Cu
/*for config function of pin&*/
#define PORTC_PCR	0x4004B000u
#define PTC6_PCR_OFFSET		0x18u
#define PTC7_PCR_OFFSET 	0x1Cu
#define PTC13_PCR_OFFSET	0x34u
/* System Clock Generator*/
#define SCG_BASE_ADDRESS			0x40064000u
#define SCG_FIRCDIV_OFFSET		0x304u
/*config clock for LPUART*/
#define PCC_LPUART1_OFFSET	0x1ACu
/*config Low Power UART*/
#define LPUART1_BASE_ADDRESS				0x4006B000u
#define LPUART1_BAUDRATE_OFFSET			0x10u
#define LPUART1_STATUS_OFFSET				0x14u
#define LPUART1_CONTROL_OFFSET			0x18u
#define LPUART1_DATA_OFFSET					0x1Cu
#define LPUART1_FIFO_OFFSET					0x28u
#define LPUART1_WATERMARK_OFFSET		0x2Cu

#define RECEIVE_DATA_BUFFER_SIZE	1024
/* Constants to config interrupt for port*/
#define NVIC_ISER1	0xE000E104 /*address of NVIC_ISER1*/

extern unsigned int* lpuart1_status_register;
extern unsigned int* lpuart1_data_register;
extern unsigned int* lpuart1_control_register;

extern char receive_data;
extern char string_of_data[RECEIVE_DATA_BUFFER_SIZE];
extern unsigned int end_of_receive_flag;
extern unsigned int i;

void ConfigUart(void);

void ConfigInterruptUart(void);

void LPUART1_transmit_char(char data);

void LPUART1_transmit_string(char* s);

void LPUART1_interrupt_receive_char(void);

unsigned int isEndOfReceive(void);

void LPUART1_interrupt_receive_string(void);

/*Function to handle LPUART1 Transmit / Receive  Interrupt*/
void LPUART1_RxTx_IRQHandler(void); 

#endif
