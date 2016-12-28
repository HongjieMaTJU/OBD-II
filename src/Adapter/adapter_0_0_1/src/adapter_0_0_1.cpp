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
//#include <cstdint>

// TODO: insert other include files here
#include  "chip.h"
#include "board_configure.h"
#include "timer.h"
#include "led.h"
#include "usart.h"

// TODO: insert other definitions and declarations here

#define _8N1 0x01

void LongTimer_Callback();

static UART_CONFIG_T KWP_UART_CFG  =
{
  14976000, // uart common clock
  10400,    // baud rate
  _8N1,     // 8 data length, no parity, 1 stop
  0,        // Asynchronous Mode
  NO_ERR_EN // Enable No Errors
};


static UART_CONFIG_T BLUE_TOOTH__UART_CFG  =
{
  14976000, // uart common clock
  115200,    // baud rate
  _8N1,     // 8 data length, no parity, 1 stop
  0,        // Asynchronous Mode
  NO_ERR_EN // Enable No Errors
};


char str[8] = "taopeng";

int main(void)
{

    // TODO: insert code here

	//Board_Init();
    Board_Configure::instance()->Configure();

    uint32_t MianClock = Board_Configure::instance()->Get_MainClockRate();

  //  Timer * pled_blink_timer = Timer::Instance(Timer0);
    UART *pBluetoothUart = UART::Instance(LPC_UART0_CHANNEL);
    pBluetoothUart->Uart_Init(&BLUE_TOOTH__UART_CFG);


    Led * pLed = Led::instance();
    LongTimer * pLongtimer = LongTimer::Instance(LongTimer_Callback);
    //LongTimer * longtimer = LongTimer::Instance(0);



    pLed->Lighten_Led_TX();
    pLed->Lighten_Led_RX();

    pLed->Off_Led_TX();
    //Led::instance()->Off_Led_RX();
    pLed->Toggle_Led_TX();
    pLed->Toggle_Led_RX();

    // Force the counter to be placed into memory*/
	volatile static uint32_t i = 0 ;

    // Enter an infinite loop, just incrementing a counter

	/* the MRT timer can maximum delay the timer for 233ms */
	//led_blink_timer->Start_Millisecond(200);

	pLongtimer->Start_Millisecond(1000);
    while(1)
    {

    	/*if(led_blink_timer->IsExpired())
    	{
    		i++ ;
    		led_blink_timer->Start_Millisecond(200);
    	}
    	if(i == 5)// 1 second
    	{
    		i = 0;
    		led->Toggle_Led_TX();
    		led->Toggle_Led_RX();
    	}*/
    	if(pLongtimer->IsExpired())
    	{
    		pBluetoothUart->Send(str,7);
    		//LongTimer_Callback();
    		pLongtimer->Start_Millisecond(1000);
    		pLed->Blink_Led_RX();
    		pLed->Blink_Led_TX();
    	}
    	i++;
    }
    return 0 ;
}


void LongTimer_Callback()
{
	Led * led = Led::instance();
	led->Toggle_Led_TX();
	led->Toggle_Led_RX();
}
