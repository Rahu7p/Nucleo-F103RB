/**
 ******************************************************************************
 * @file           : main.c
 * @author         : rahu7p
 * @board          : NUCLEO-F103RB
 ******************************************************************************
 *
 * C code to transmit the Hello World! string using the serial port (USART2) 
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
	USER_USART2_Init( );

    	/* Repetitive block */
    	for(;;){
    		USER_USART2_Transmit( msg, sizeof( msg ));
    	}
}

void USER_RCC_ClockEnable( void ){
	RCC->APB2ENR	|=	 ( 0x1UL <<  2U );//	IO port A clock enable
	RCC->APB1ENR	|=   	 ( 0x1UL << 17U );//	USART 2 clock enable
}
void USER_GPIO_Init( void ){
	//pin PA2 (USART2_TX) as alternate function output push-pull, max speed 10MHz
	GPIOA->CRL	&=	~( 0x1UL << 10U )
			&	~( 0x2UL <<  8U );
	GPIOA->CRL	|=	 ( 0x2UL << 10U )
			|	 ( 0x1UL <<  8U );
}
