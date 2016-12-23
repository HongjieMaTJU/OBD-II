/*
===============================================================================
 Name        : main.c
 Author      : $(author)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/


#include <cr_section_macros.h>
#include <cstdint>

// TODO: insert other include files here
#include "board_configure.h"
#include "led.h"


// TODO: insert other definitions and declarations here


int main(void)
{

    // TODO: insert code here

	//Board_Init();
    Board_Configure::instance()->Configure();

    Led::instance()->Lighten_Led_TX();
    Led::instance()->Lighten_Led_RX();

    Led::instance()->Off_Led_TX();
    //Led::instance()->Off_Led_RX();

    Led::instance()->Toggle_Led_TX();
    Led::instance()->Toggle_Led_RX();

    // Force the counter to be placed into memory

	volatile static uint32_t i = 0 ;

    //complex compx;
    //CAN->CANCNTL = 0x0;

    // Enter an infinite loop, just incrementing a counter

    while(1)
    {
    	if(i == 3600000)
    	{
    		i = 0;
    		Led::instance()->Toggle_Led_TX();
    		Led::instance()->Toggle_Led_RX();
    	}
    	//Chip_GPIO_SetPinToggle(LPC_GPIO,TX_LED_PORT,3);
    	//Chip_GPIO_SetPinToggle(LPC_GPIO,RX_LED_PORT,RX_LED_PIN);
        i++ ;
    }
    return 0 ;
}