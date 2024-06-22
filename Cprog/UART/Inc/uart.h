#ifndef UART_H_
#define UART_H_

#include <stdio.h>

int _write(int file, char *ptr, int len);

#define PCLK1			32000000
#define BAUDRATE		115200
#define USARTDIV		0x116//				(PCLK1/(16*BAUDRATE))

void USER_USART2_Init( void );
void USER_USART2_Transmit( uint8_t *pData, uint16_t size );

#endif /* UART_H_ */
