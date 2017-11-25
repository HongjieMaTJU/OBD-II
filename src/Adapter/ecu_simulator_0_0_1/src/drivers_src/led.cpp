/*
 * led.cpp
 *
 *  Created on: 2016年12月22日
 *      Author: Topon-Edison
 */



#include "ecu_board.h"
#include "led.h"
#include "timer.h"


using namespace std;



volatile uint32_t Led::tx_count_ = 0;
volatile uint32_t Led::rx_count_ = 0;

/* Factory of the Led */
Led* Led::instance()
{
	static Led ins;
	return (&ins);
}



/* Lighten the led indicating TX signal */
void Led::Lighten_Led_TX()
{
	Board_Lighten_TX_LED();
}

/* Lighten the led indicating RX signal */
void Led::Lighten_Led_RX()
{
	Board_Lighten_RX_LED();
}


/* Lighten the led for gap_num * minimum_gap */
void Led::Blink_Led_TX()
{
	tx_count_ = gap_num;
	Board_Lighten_TX_LED();
}


/* Lighten the led for gap_num * minimum_gap */
void Led::Blink_Led_RX()
{
	rx_count_ = gap_num;
	Board_Lighten_RX_LED();
}
/* Off the led indicating TX signal */
void Led::Off_Led_TX()
{

	Board_Off_TX_LED();
}

/* Off the led indicating RX signal */
void Led::Off_Led_RX()
{
	Board_Off_RX_LED();
}



/* Toggle the led indicating TX signal */
void Led::Toggle_Led_TX()
{
	Board_Toggle_TX_LED();
}

/* Toggle the led indicating RX signal */
void Led::Toggle_Led_RX()
{
	Board_Toggle_RX_LED();
}



/* Constructor */
Led::Led()
{
   led_timer_ = LedTimer::Instance(Led_Callback);
   Start_Timer();
}

/* Destructor */
Led::~Led()
{

}



void Led::Start_Timer()
{
	led_timer_ ->Start_Millisecond(lighten_minimum_gap);
}


void Led::Stop_Timer()
{
	led_timer_->Stop();
}


void Led::Led_Callback()
{
    Led * pLed = instance();
	if(tx_count_ && (--tx_count_ == 0))
	{
		 pLed->Off_Led_TX();
	}

	if(rx_count_ &&(--rx_count_ == 0))
	{
		pLed->Off_Led_RX();

	}
}

