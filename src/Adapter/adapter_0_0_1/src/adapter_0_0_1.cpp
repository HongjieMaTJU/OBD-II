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
#include "chip.h"
#include "board_configure.h"
#include "timer.h"
#include "led.h"
#include "usart.h"
#include "kwp_usart.h"

// TODO: insert other definitions and declarations here



#define _8N1 0x01                 // define uart configuration parameter

/*******************************************************
 ***************** Global Variable *********************
 ***************** *************************************/
/* Configuration parameter for KWP UART */
static UART_CONFIG_T KWP_UART_CFG  =
{
  14976000, // uart common clock
  10400,    // baud rate
  _8N1,     // 8 data length, no parity, 1 stop
  0,        // Asynchronous Mode
  NO_ERR_EN // Enable No Errors
};


/* Configuration parameter for bluetooth UART */
static UART_CONFIG_T BLUE_TOOTH__UART_CFG  =
{
  14976000, // uart common clock
  115200,    // baud rate
  _8N1,     // 8 data length, no parity, 1 stop
  0,        // Asynchronous Mode
  NO_ERR_EN // Enable No Errors
};

//static rx buffer values ;
const int MAX_RX_LENGTH = 256;
static char rx_buffer[MAX_RX_LENGTH];
static int rx_index = 0;
//static bool rx_ready = false;
//static bool rx_message_too_long = false;
static char str[] = "Message is too long, please resend in a shorter length!";





/*******************************************************
 ***************** Global Funtion **********************
 ***************** *************************************/
/* bluetooth initialize */
void Init_Bluetooth();

/* callback for bluetooth uart rx processing */
void Bluetooth_Rx_Callback(char ch);

/* callback for Longtimer */
void LongTimer_Callback();


/* bluetooth resource handle */
UART *pBluetoothUart;

/* led resource handle */
Led *pLed;

/* LongTimer resource handle*/
LongTimer *pLongtimer;

Timer *pDelaytimer;


int main(void)
{

    // TODO: insert code here

	 /* Board_Init(); */
     Board_Configure::instance()->Configure();

    /* for getting system main clock */
    //uint32_t MianClock = Board_Configure::instance()->Get_MainClockRate();


    /* Initialize bluetooth uart resource and return handle of it*/
    pBluetoothUart = UART::Instance(LPC_UART0_CHANNEL);
    /* Initialize Led resource and return handle of it*/
    pLed = Led::instance();
    /* Initialize timer source and return handle of it */
    pLongtimer = LongTimer::Instance(LongTimer_Callback);


    pDelaytimer = Timer::Instance(Timer0);



    /* configure and initialize bluetooth uart instance */
    pBluetoothUart->Uart_Init(&BLUE_TOOTH__UART_CFG);

   // RingBuffer_Init(&ring_buffer,rx_buffer,1,64);
    pBluetoothUart->Set_RX_Callback(Bluetooth_Rx_Callback);


    /* delya for 10ms to complete Uart setting */
    pDelaytimer->Start_Millisecond(1000);
    while(!pDelaytimer->IsExpired());

    KWP_UART * hKwp_Uart =  KWP_UART::Instance();


    /* initialize the bluetooth */
   // Init_Bluetooth();


    // Force the counter to be placed into memory*/
	volatile static uint32_t i = 0 ;



	/* the MRT timer can maximum delay the timer for 233ms */
	//led_blink_timer->Start_Millisecond(200);
	/* start the LongTimer */

	pLongtimer->Start_Millisecond(1000);
	// Enter an infinite loop, just incrementing a counter
    while(1)
    {
    	/*if(rx_message_too_long || rx_ready)
    	{
    		if(rx_message_too_long)
    		{
				rx_index = 0;
				rx_message_too_long = false;
    		}
    		else
    		{


    		}
    	}*/

    	/*if(pLongtimer->IsExpired())
    	{

    	}*/

    	i++;
    }
    return 0 ;
}

/* Long timer call back */
void LongTimer_Callback()
{
	//pBluetoothUart->Send("AT",2);
//	pBluetoothUart->Send("AT+AUTH1",8);
	//pBluetoothUart->Send("Topon-Edison!\n",14);
	pLongtimer->Start_Millisecond(1000);
	pLed->Blink_Led_RX();
	pLed->Blink_Led_TX();
}


void Bluetooth_Rx_Callback(char ch)
{
	if(rx_index >= MAX_RX_LENGTH - 1)// received message is longer than rx_buffer length
	{
		//rx_message_too_long = true;
	//	pBluetoothUart->Send(str,55);
		rx_index = 0;
		return;
	}
	rx_buffer[rx_index++] = ch;
	//rx_buffer[rx_index] =  0;
	//if(ch == '0')//ch == 't')
	//{
		// echo back message
	//	pBluetoothUart->Send(rx_buffer,rx_index);
	//	rx_index = 0;
	//}
}

void Init_Bluetooth()
{
    char ch[] = "AT";

	while(rx_buffer[0]!= 'O' && rx_buffer[1] != 'K')
	{
		//Chip_UART_Send(LPC_USART0,ch,2);
		Chip_UART_SendByte(LPC_USART0,'A');
		Chip_UART_SendByte(LPC_USART0,'T');
	}
	rx_index  = 0;
	char * temp_str;
	temp_str = rx_buffer;

	char ch1[] = "AT+AUTH1";
	while(str != "OK+Set:1")
	{
		Chip_UART_Send(LPC_USART0,ch1,2);
	}
	//while(rx_buffer != "OK+Set:1");
	//pBluetoothUart->Send("AT+RESET",8);
}
