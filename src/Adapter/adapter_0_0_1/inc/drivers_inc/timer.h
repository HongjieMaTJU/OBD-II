/*
 * timer.h
 *
 *  Created on: 2016年12月22日
 *      Author:Topon-Edison
 */

#ifndef DRIVERS_INC_TIMER_H_
#define DRIVERS_INC_TIMER_H_
//#include "chip.h"
#include <cstdint>

/*
 *@brief Definition to distinguish the timer channel of MRT,
 *       Timre0 is the channel zero and so on.
 */


typedef enum TimerNum
{
	Timer0 = 0,
	Timer1,
	Timer2,
}Timer_T;


/**
 * @brief The Declaration of the MRT timer channel type
 *
 */
struct LPC_MRT_CH_T;


/**
 * @brief The declaration of the Timer use the MRT timer in one shot mode
 *
 */
class Timer
{
public :
   static Timer* Instance(Timer_T );
   void Start_Millisecond(uint32_t interval);
  // void Stop();
   bool IsExpired();

private:
   Timer(Timer_T);
   LPC_MRT_CH_T * timer_; // timer channel pointer
   const uint32_t timer_tick_ms_;//time tick for millisecond
   const uint32_t timer_tick_us_;//time tick for microsecond
   Timer_T timer_type_;
};



/**
 * @brief The Declaration of the  LPC_RITIMER_T
 *
 */
struct LPC_RITIMER_T;
//typedef void (*RIT_CallBack_T)(void);
/**
 * @brief The declaration of the RIT timer,which has 48 bit counter, can
 */
class LongTimer
{
public:
	static LongTimer* Instance(); // factory
	void Start_Millisecond(uint64_t interval);// start the timer
	void Stop_NextCircle(); // stop counting of the next counting circle
	void SetExpired();       // when the timer is end, set the member
	bool IsExpired();// query the status of the timer, is counting end
private:
	LongTimer();
	bool is_expired_;
	LPC_RITIMER_T * timer_;
	uint64_t timer_tick_ms_; // tick for a millisecond
};





#endif /* DRIVERS_INC_TIMER_H_ */
