## Table of contents
* [General info](#general-info)
* [Connections](#connections)
* [Setup](#setup)

## General info
* To drive the LCD, perform the following:
	* Download the 'lcd.c' and 'lcd.h' files from this folder
	* Add the files into your STM32CubeIDE project. You can do this by the drag & drop feature.
 		* In your file browser select the files and drop them in the project window
			* Drop the 'lcd.h' file in the Inc/ folder
			* Drop the ‘lcd.c’ file in the Src/ folder 
	* The 'lcd.h' file contains all the function prototypes and pin definitions.
	* The 'lcd.c' file contains the functions needed to initialize and drive the LCD1602 (clear the display, move the cursor, write a character, write a string, etc.)
		* In this file, you will need to implement your own delays. Pay attention to the desired times.
	
## Connections
The LCD display needs +5V as power supply. The Nucleo-F103RB can supply this voltage via a +5V pin.

![alt text](https://microcontrollerslab.com/wp-content/uploads/2015/01/LCD-Interfacing-with-Pic-microcontroller-Connection-diagram.png)
	
## Setup
This is an example of usage. You will need to define your own delay and enable the TIM clock (RCC).

```
#include <stdint.h>
#include "main.h"
#include "lcd.h"

int main(void)
{
	uint8_t col = 16;
 	LCD_Init( );
    for(;;){
    	LCD_Clear( );
    	LCD_Set_Cursor( 1, 1 );
    	LCD_Put_Str( "TE" );
    	LCD_Put_Num( 2003 );
    	LCD_Put_Char( 'B' );
    	LCD_Put_Str( " SoC" );
    	LCD_Set_Cursor( 2, col-- );
    	LCD_Put_Str( "Prueba de LCD ");
    	LCD_BarGraphic( 0, 64 );
	USER_TIM_Delay( );// 200ms
    	if( col == 0 ){
    		USER_TIM_Delay( );// 500ms
    		col = 16;
    	}
    }
}
```
