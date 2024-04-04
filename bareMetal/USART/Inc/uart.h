#ifndef UART_H_
#define UART_H_

#define USARTDIV        0x341//				    9600 baud rate
#define USART_CR1_UE    ( 0x1UL << 13U )
#define USART_CR1_M     ( 0x1UL << 12U )
#define USART_CR1_TE    ( 0x1UL <<  3U )
#define USART_CR2_STOP  ( 0x3UL << 12U )
#define USART_SR_TXE    ( 0x1UL <<  7U )

void USER_USART1_Init( void );
void USER_USART1_Transmit( uint8_t *pData, uint16_t size );

#endif /* UART_H_ */
