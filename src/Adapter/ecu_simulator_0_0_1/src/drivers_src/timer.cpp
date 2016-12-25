/*
 * timer.cpp
 *
 *  Created on: 2016年12月22日
 *      Author: Topon-Edison
 *
 *
 *
 */

#include "chip.h"
#include "timer.h"



/* The instance function of  the Timer singleton */
Timer * Timer::Instance(Timer_T timer_t)
{
	static Timer timer0(Timer0); // the Timer use MRT  channel 0
    static Timer timer1(Timer1); // the Timer use MRT  channel 1
    static Timer timer2(Timer2); // the Timer use MRT  channel 2
    switch (timer_t)
    {
    case Timer0:
    	return &timer0;
    case Timer1:
    	return &timer1;
    case Timer2:
    	return &timer2;
    default:
    	return 0;
    }

}

/**
 *   Constructor, according to the timer_t to assign the member timer_
 *  's value, and set the timer to one shot mode
 */
Timer::Timer(Timer_T timer_t):timer_tick_ms_(Chip_Clock_GetMainClockRate() / 1000),
		timer_tick_us_(timer_tick_ms_ / 1000),timer_type_(timer_t)
{

	switch(timer_t)
	{
	case Timer0:
		/* Set the timer point to the mrt channel one */
		timer_ = LPC_MRT_CH0;
		break;
	case Timer1:
		timer_ = LPC_MRT_CH1;
		break;
	case Timer2:
		timer_ = LPC_MRT_CH2;
		break;
	default : // Don't exist the type of timer;
		timer_ = 0;
		break;
	}

	/* If the timer_ isn't null,  set the timer work in one shot mode and
	 * and disable the channel's interrupt */
	if(timer_)
	{
		Chip_MRT_SetMode(timer_,MRT_MODE_ONESHOT);
		Chip_MRT_SetDisabled(timer_);
	}
}


/* Start the timer for interval millisecond
 * the maximum interval is 233ms */
void Timer::Start_Millisecond(uint32_t interval)
{

	/* Calculate the counter value*/
	uint32_t val = timer_tick_ms_ * interval;
	/* Clear the timer INTFLAG in STAT register */
	Chip_MRT_IntClear(timer_);
	/* Set the IVALUE in INVAL register and load the value to timer immidiately */
	 val |= 0x80000000UL;
	Chip_MRT_SetInterval_Immediately(timer_,val);

}



/* The timer STAT register's RUN bit is 1 for running state , 0 for idle state */
bool Timer::IsExpired()
{
	return (bool)(!Chip_MRT_Running(timer_));
}





