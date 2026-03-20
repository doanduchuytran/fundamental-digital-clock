#include "spi.h"

unsigned int* lpspi1_receive_data_register = (unsigned int*) (LPSPI1_BASE_ADDRESS + RDR_OFFSET);

void LPSPI0_send_char(char data)
{
	unsigned int* lpspi0_status_register = (unsigned int*) (LPSPI0_BASE_ADDRESS + SR_OFFSET);
	unsigned int* lpspi0_transmit_data_register = (unsigned int*) (LPSPI0_BASE_ADDRESS + TDR_OFFSET);
	
	while((*lpspi0_status_register & (1 << 0)) == 0); /*wait for the transmit buffer empty*/
	*lpspi0_transmit_data_register = data;
}

void LPSPI0_send_data(short data)
{
	unsigned int* lpspi0_status_register = (unsigned int*) (LPSPI0_BASE_ADDRESS + SR_OFFSET);
	unsigned int* lpspi0_transmit_data_register = (unsigned int*) (LPSPI0_BASE_ADDRESS + TDR_OFFSET);
	
	while((*lpspi0_status_register & (1 << 0)) == 0); /*wait for the transmit buffer empty*/
	*lpspi0_transmit_data_register = (unsigned int) data;
}


void LPSPI0_send_string(char* string)
{
	while(*string != '\0')
	{
		LPSPI0_send_char(*string);
		string++;
	}
}



/*Function to config LPSPI0 as master*/
void config_lpspi0(void)
{
	/*registers for configure lpspi0*/
	unsigned int* portb_pcr2 = (unsigned int*) (PORTB_PCR_BASE_ADDRESS + PORT_PCR2_OFFSET);	/*sck*/
	unsigned int* portb_pcr3 = (unsigned int*) (PORTB_PCR_BASE_ADDRESS + PORT_PCR3_OFFSET);	/*sin*/
	unsigned int* portb_pcr4 = (unsigned int*) (PORTB_PCR_BASE_ADDRESS + PORT_PCR4_OFFSET);	/*sout*/
	unsigned int* portb_pcr0 = (unsigned int*) (PORTB_PCR_BASE_ADDRESS + PORT_PCR0_OFFSET); /*pcs0*/
	/*register for configure clock for module lpspi*/
	unsigned int* pcc_lpspi0_register = (unsigned int*) (PCC_BASE_ADDRESS + LPSPI0_OFFSET);
	/*register for configure lpspi0*/
	unsigned int* lpspi0_transmit_command_register = (unsigned int*) (LPSPI0_BASE_ADDRESS + TCR_OFFSET);
	unsigned int* lpspi0_FIFO_control_register	= (unsigned int*) (LPSPI0_BASE_ADDRESS + FCR_OFFSET); 			/*FIFO control register*/
	unsigned int* lpspi0_configuration_register_1 = (unsigned int*) (LPSPI0_BASE_ADDRESS + CFGR1_OFFSET);
	unsigned int* lpspi0_control_register = (unsigned int*) (LPSPI0_BASE_ADDRESS + CR_OFFSET);
	
	/***************************************************************
	SETTING SCK/PCS/SIN/SOUT PIN
	***************************************************************/
	/*Enable clock for port is done in port.c*/
	/*Set alternate function pin*/
	/*sck*/
	set_bit(portb_pcr2, 8);
	set_bit(portb_pcr2, 9);
	/*sin*/
	set_bit(portb_pcr3, 8);
	set_bit(portb_pcr3, 9);
	/*sout*/
	set_bit(portb_pcr4, 8);
	set_bit(portb_pcr4, 9);
	/*pcs0*/
	set_bit(portb_pcr0, 8);
	set_bit(portb_pcr0, 9);
	
	/***************************************************************
	PERIPHERAL CLOCK SOURCE SELECT
	***************************************************************/
	/*peripheral clock source select*/
	set_bit(pcc_lpspi0_register, 24);
	set_bit(pcc_lpspi0_register, 25);
	/*Enable clock for LPSPI*/
	set_bit(pcc_lpspi0_register, 30);
	
	/***************************************************************
	SETTING CLOCK
	***************************************************************/
	/*Set prescaler value = 8 -> TCR[PRESCALE] = 011*/
	set_bit(lpspi0_transmit_command_register, 27);
	set_bit(lpspi0_transmit_command_register, 28);
	clear_bit(lpspi0_transmit_command_register, 29);
	
	/*Set divide ratio of the SCK pin*/
	
	/***************************************************************
	CONFIGURE CLOCK PHASE AND POLARITY
	***************************************************************/
	/*Set clock polarity*/
	clear_bit(lpspi0_transmit_command_register, 31);
	/*Set clock phase*/
	clear_bit(lpspi0_transmit_command_register, 30);
	
	/***************************************************************
	SETTING FRAME DATA
	***************************************************************/
	/*Set frame size: frame size = 16 -> FRAMESZ = 15*/
	set_bit(lpspi0_transmit_command_register, 0);
	set_bit(lpspi0_transmit_command_register, 1);
	set_bit(lpspi0_transmit_command_register, 2);
	set_bit(lpspi0_transmit_command_register, 3);
	/*Set type of transfer data: MSB fisrt*/
	clear_bit(lpspi0_transmit_command_register, 23);
	
	/***************************************************************
	CONFIGURE THE PERIPHERAL CHIP SELECT
	***************************************************************/
	/*Peripheral chip select: transfer using PCS0*/
	clear_bit(lpspi0_transmit_command_register, 24);
	clear_bit(lpspi0_transmit_command_register, 25);
	
	/***************************************************************
	SETTING TRANSMIT/RECEIVE FIFO
	***************************************************************/
//	/*Set Receive FIFO Watermark*/
//	set_bit(lpspi0_FIFO_control_register, 16);
	/*Set Transmit FIFO Watermark*/
	set_bit(lpspi0_FIFO_control_register, 0);
	set_bit(lpspi0_FIFO_control_register, 1);
	/*Set FIFO underrun*/
	set_bit(lpspi0_configuration_register_1, 3); /*transfer will not stall when the transmit FIFO is empty*/
	
	/***************************************************************
	CONFIGURE LPSPI MODE
	***************************************************************/
	/*lpspi0 is master mode*/
	set_bit(lpspi0_configuration_register_1, 0);
	/*Debug enable*/
	set_bit(lpspi0_control_register, 3);
	
	/***************************************************************
	ENABLE LPSPI MODULE
	***************************************************************/
	/*Enable LPSPI module*/
	set_bit(lpspi0_control_register, 0);
}


/*Function to config LPSPI1 as slave*/
void config_lpspi1(void)
{
	/*register for configure lpspi1*/
	unsigned int* portb_pcr14 = (unsigned int*) (PORTB_PCR_BASE_ADDRESS + PORT_PCR14_OFFSET);	/*sck*/
	unsigned int* portb_pcr15 = (unsigned int*) (PORTB_PCR_BASE_ADDRESS + PORT_PCR15_OFFSET);	/*sin*/
	unsigned int* portb_pcr16 = (unsigned int*) (PORTB_PCR_BASE_ADDRESS + PORT_PCR16_OFFSET);	/*sout*/
	unsigned int* portd_pcr3 = (unsigned int*) (PORTD_PCR_BASE_ADDRESS + PORT_PCR3_OFFSET);		/*pcs0*/
	/*register for configure clock for module lpspi*/
	unsigned int* pcc_lpspi1_register = (unsigned int*) (PCC_BASE_ADDRESS + LPSPI1_OFFSET);
	/*register for configure lpspi1*/
	unsigned int* lpspi1_configuration_register_1 = (unsigned int*) (LPSPI1_BASE_ADDRESS + CFGR1_OFFSET);
	unsigned int* lpspi1_control_register = (unsigned int*) (LPSPI1_BASE_ADDRESS + CR_OFFSET);
	unsigned int* lpspi1_transmit_command_register = (unsigned int*) (LPSPI1_BASE_ADDRESS + TCR_OFFSET);
	
	/***************************************************************
	Setting SCK/PCS/SIN/SOUT pin
	***************************************************************/
	/*Enable clock for port is done in port.c*/
	/*Set alternate function pin*/
	/*sck*/
	set_bit(portb_pcr14, 8);
	set_bit(portb_pcr14, 9);
	/*sin*/
	set_bit(portb_pcr15, 8);
	set_bit(portb_pcr15, 9);
	/*sout*/
	set_bit(portb_pcr16, 8);
	set_bit(portb_pcr16, 9);
	/*pcs0*/
	set_bit(portd_pcr3, 8);
	set_bit(portd_pcr3, 9);
	
	/***************************************************************
	select source clock for lpspi
	***************************************************************/
	/*peripheral clock source select*/
	set_bit(pcc_lpspi1_register, 24);
	set_bit(pcc_lpspi1_register, 25);
	/*Enable clock for LPSPI*/
	set_bit(pcc_lpspi1_register, 30);
	
	/***************************************************************
	setting clock
	***************************************************************/
	/*Set prescaler value*/
	/*Set divide ratio of the SCK pin*/
	
	/***************************************************************
	Configures clock phase and polarity
	***************************************************************/
	/*set clock polarity*/
	clear_bit(lpspi1_transmit_command_register, 31);
	/*set clock phase*/
	clear_bit(lpspi1_transmit_command_register, 30);
	
	/***************************************************************
	Setting frame data
	***************************************************************/
	/*Set frame size: frame size = 8 -> FRAMESZ = 7*/
	set_bit(lpspi1_transmit_command_register, 0);
	set_bit(lpspi1_transmit_command_register, 1);
	set_bit(lpspi1_transmit_command_register, 2);
	/*Set type of transfer data: MSB fisrt*/
	clear_bit(lpspi1_transmit_command_register, 23);
	
	/***************************************************************
	Configures the peripheral chip select
	***************************************************************/
	/*Set peripheral chip select*/
	
	/***************************************************************
	Setting transmit/receive FIFO
	***************************************************************/
	/*Set receive FIFO watermark*/
	/*Set transmit FIFO watermark*/
	/*Set FIFO underrun*/
	set_bit(lpspi1_configuration_register_1, 3); /*transfer will not stall when the transmit FIFO is empty*/
	
	/***************************************************************
	Configures LPSPI mode
	***************************************************************/
	/*lpspi1 is slave mode*/
	clear_bit(lpspi1_configuration_register_1, 0);
	/*Debug enable*/
	set_bit(lpspi1_control_register, 3);
	
	/***************************************************************
	Enable LPSPI module
	***************************************************************/
	/*Enable LPSPI module*/
	set_bit(lpspi1_control_register, 0);
}
