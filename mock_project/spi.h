#ifndef _SPI_H_
#define _SPI_H_

#include "bit_manipulate.h"

/*Constants for configuring pin*/
#define PORTA_PCR_BASE_ADDRESS	0x40049000u
#define PORTB_PCR_BASE_ADDRESS	0x4004A000u
#define PORTC_PCR_BASE_ADDRESS	0X4004B000u
#define PORTD_PCR_BASE_ADDRESS	0X4004C000u

#define PORT_PCR0_OFFSET	0x0u
#define PORT_PCR1_OFFSET	0x4u
#define PORT_PCR2_OFFSET	0x8u
#define PORT_PCR3_OFFSET	0xCu
#define PORT_PCR4_OFFSET	0x10u
#define PORT_PCR5_OFFSET	0x14u
#define PORT_PCR6_OFFSET	0x18u
#define PORT_PCR7_OFFSET	0x1Cu
#define PORT_PCR8_OFFSET	0x20u
#define PORT_PCR9_OFFSET	0x24u
#define PORT_PCR10_OFFSET	0x28u
#define PORT_PCR11_OFFSET	0x2Cu
#define PORT_PCR12_OFFSET	0x30u
#define PORT_PCR13_OFFSET	0x34u
#define PORT_PCR14_OFFSET	0x38u
#define PORT_PCR15_OFFSET	0x3Cu
#define PORT_PCR16_OFFSET	0x40u
#define PORT_PCR17_OFFSET	0x44u
#define PORT_PCR18_OFFSET	0x48u
#define PORT_PCR19_OFFSET	0x4Cu
#define PORT_PCR20_OFFSET	0x50u
#define PORT_PCR21_OFFSET	0x54u
#define PORT_PCR22_OFFSET	0x58u
#define PORT_PCR23_OFFSET	0x5Cu
#define PORT_PCR24_OFFSET	0x60u
#define PORT_PCR25_OFFSET	0x64u
#define PORT_PCR26_OFFSET	0x68u
#define PORT_PCR27_OFFSET	0x6Cu
#define PORT_PCR28_OFFSET	0x70u
#define PORT_PCR29_OFFSET	0x74u
#define PORT_PCR30_OFFSET	0x78u
#define PORT_PCR31_OFFSET	0x7Cu

/*Constants for configuring clock for module LPSPI*/
#define PCC_BASE_ADDRESS	0x40065000u
#define LPSPI0_OFFSET			0xB0u
#define LPSPI1_OFFSET			0xB4u
#define LPSPI2_OFFSET			0xB8u

/*Constants for config module LPSPI*/
#define LPSPI0_BASE_ADDRESS	0x4002C000u
#define LPSPI1_BASE_ADDRESS	0x4002D000u
#define LPSPI2_BASE_ADDRESS	0x4002E000u

#define FCR_OFFSET		0x58u		/*FIFO Control Register*/
#define TCR_OFFSET		0x60u		/*Transmit Command Register*/
#define CFGR1_OFFSET	0x24u		/*Configuration register 1*/
#define CR_OFFSET			0x10u		/*control register*/
#define TDR_OFFSET		0x64u		/*Transmit Data Register*/
#define SR_OFFSET			0x14u		/*Status Register*/
#define RDR_OFFSET		0x74u		/*receive data register offset*/

extern unsigned int* lpspi1_receive_data_register;			/*register to store the received data of lpspi1*/

/*Function to config LPSPI0 as master*/
void config_lpspi0(void);

/*Function to config LPSPI1 as slave*/
void config_lpspi1(void);

/*Function to send a character use LPSPI0*/
void LPSPI0_send_char(char data);

/*Function to send a string use LPSPI0*/
void LPSPI0_send_string(char* string);

/*Function to send a 16-bit data using SPI*/
void LPSPI0_send_data(short data);

#endif
