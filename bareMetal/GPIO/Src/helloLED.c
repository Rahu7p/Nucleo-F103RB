/* **************** START *********************** */
/* Libraries, Definitions and Global Declarations */
#include <stdint.h>
#include "main.h"

void USER_SystemClock_Config( void );
void USER_GPIO_Init( void );
void USER_Delay( void );

/* Superloop structure */
int main(void)
{
	/* Declarations and Initializations */
	USER_SystemClock_Config( );
	USER_GPIO_Init( );
    /* Repetitive block */
    for(;;){
    	GPIOA->BSRR	=	( 0x1UL <<  5U );//	value to set pin5 of port A (Turn-ON LD2)
    	USER_Delay( );
        GPIOA->BRR	=	( 0x1UL <<  5U );//	value to reset pin5 of port A (Turn-OFF LD2)
        USER_Delay( );
    }
}

void USER_SystemClock_Config( void ){
	// ClockSource = 64 MHz
	FLASH->ACR	&=	~( 0x5UL <<  0U );//	two wait states latency, if SYSCLK > 48MHz
	FLASH->ACR	|=	 ( 0x2UL <<  0U );//	two wait states latency, if SYSCLK > 48MHz
	RCC->CFGR	&=	~( 0x1UL << 16U )//		PLL HSI oscillator clock /2 selected as PLL input clock
			&	~( 0x7UL << 11U )// 	APB2 prescaler /1
			&	~( 0x3UL <<  8U );// 	APB1 prescaler /2
	RCC->CFGR	|=	 ( 0xFUL << 18U )//		PLL input clock x 16 (PLLMUL bits)
			|	 ( 0x4UL <<  8U );//	APB1 prescaler /2
	RCC->CR		|=	 ( 0x1UL << 24U );//	PLL2 ON
	while( !(RCC->CR & ~( 0x1UL << 25U )));//	wait until PLL is locked
	RCC->CFGR	&=	~( 0x1UL << 0U  );//	PLL used as system clock (SW bits)
	RCC->CFGR	|=	 ( 0x2UL << 0U  );//	PLL used as system clock (SW bits)
	while( 0x8UL != ( RCC->CFGR & 0xCUL ));//	wait until PLL is switched
}
void USER_GPIO_Init( void ){
	// RCC_APB2ENR modified to IO port A clock enable
	RCC->APB2ENR	=	RCC->APB2ENR//		RCC_APB2ENR actual value
			|//					to set
			( 0x1UL << 2U );//	(mask) IOPAEN bit

	// GPIOx_BRR modified to reset pin 5 of port A (LD2 is connected to PA5)
	GPIOA->BRR	=	( 0x1UL << 5U );//	immediate value

	// GPIOx_CRL modified to configure pin5 as output
	GPIOA->CRL	=	GPIOA->CRL//		GPIOx_CRL actual value
			&//					to clear
			~( 0x3UL << 22U )//	(mask) CNF5[1:0] bits
			&//					to clear
			~( 0x2UL << 20U );//(mask) MODE5_1 bit

	// GPIOx_CRL modified to select pin5 max speed of 10MHz
	GPIOA->CRL	=	GPIOA->CRL//	GPIOx_CRL actual value
			|//					to set
			( 0x1UL << 20U );//	(mask) MODE5_0 bit
}
void USER_Delay( void ){
	__asm(" 	ldr r0, =7111111 	");
	__asm(" again:	sub r0, r0, #1		");
	__asm("		cmp r0, #0		");
	__asm("		bne again		");
	__asm("		nop			");
}
