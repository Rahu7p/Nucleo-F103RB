#include <stdint.h>
#include "main.h"
#include "uart.h"
#include <stddef.h>
#include <stdio.h>              /* This ert_main.c example uses printf/fflush */
#include "EngTrModel.h"         /* Model's header file */
#include "rtwtypes.h"

#define USER_B1		( GPIOC->IDR & ( 0x1UL << 13U ))

void USER_RCC_Init(void);
void USER_GPIO_Init(void);

int main(void)
{
  	USER_RCC_Init();
	USER_GPIO_Init();
  	USER_USART2_Init();
	EngTrModel_initialize();
  for(;;)
	{
		if(!USER_B1){
      			USER_TIM_Delay();//  10ms
      			if(!USER_B1){
        			EngTrModel_U.Throttle = 1.3;
			  	EngTrModel_U.BrakeTorque = 100.0;
        		while(!USER_B1);
        		USER_TIM_Delay();//  10ms
      			}
		}
		else{
			EngTrModel_U.Throttle = 50.0;
			EngTrModel_U.BrakeTorque = 0.0;
		}
		EngTrModel_step();
		printf("Vehicle Speed: %f\r\n", EngTrModel_Y.VehicleSpeed);
		printf("Engine Speed: %f\r\n", EngTrModel_Y.EngineSpeed);
		printf("Gear: %f\r\n", EngTrModel_Y.Gear);
		USER_TIM_Delay();//  40ms
	}
}

void USER_RCC_Init(void){}
void USER_GPIO_Init(void){}
