/*
 * timer.h
 *
 *  Created on: 2016年12月22日
 *      Author:Topon-Edison
 */

#ifndef DRIVERS_INC_TIMER_H_
#define DRIVERS_INC_TIMER_H_



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


/*
 * @brief The Declaration of the MRT timer channel type
 *
 */
struct LPC_MRT_CH_T;

/*
 * @brief The Declaration of the MRT timer channel type
 *
 */
struct LPC_RIT_T;

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

class LongTimer
{
public:
	static LongTimer * Instance();

};


#endif /* DRIVERS_INC_TIMER_H_ */
