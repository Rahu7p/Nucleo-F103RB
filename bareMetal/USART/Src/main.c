/**
 ******************************************************************************
 * @file           : main.c
 * @author         : rahu7p
 * @board          : NUCLEO-F103RB
 ******************************************************************************
 *
 * C code to transmit the Hello World! string using the serial port (USART1) 
 * in bare metal
 *
 ******************************************************************************
 */

/* Libraries, Definitions and Global Declarations */
#include <stdint.h>
#include "main.h"
#include "uart.h"

uint8_t msg[] = "Hello World!\r\n";

/* Function prototypes */
void USER_RCC_ClockEnable( void );
void USER_GPIO_Init( void );

/* Superloop structure */
int main(void)
{
	/* Declarations and Initializations */
	USER_RCC_ClockEnable( );
	USER_GPIO_Init( );
	USER_USART1_Init( );

    	/* Repetitive block */
    	for(;;){
    		USER_USART1_Transmit( msg, sizeof( msg ));
    	}
}

void USER_RCC_ClockEnable( void ){
	RCC->APB2ENR	|=	 ( 0x1UL <<  2U )//	IO port A clock enable
			|	 ( 0x1UL << 14U );//	USART 1 clock enable
}
void USER_GPIO_Init( void ){
	//pin PA9 (USART1_TX) as alternate function output push-pull, max speed 10MHz
	GPIOA->CRH	&=	~( 0x1UL <<  6U )
			&	~( 0x2UL <<  4U );
	GPIOA->CRH	|=	 ( 0x2UL <<  6U )
			|	 ( 0x1UL <<  4U );
}
