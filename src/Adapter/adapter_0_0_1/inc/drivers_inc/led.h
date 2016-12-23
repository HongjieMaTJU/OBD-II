/*
 *
 * led.h
 *
 *  Created on: 2016年12月22日
 *      Author: Topon-Edison
 *      */


/**
 * @brief The class for adapter's led which are
 * used for indicating the communication between
 * adapter and ECUS
 *
 */

#ifndef DRIVERS_INC_LED_H_
#define DRIVERS_INC_LED_H_


using namespace std;

class Led
{
public:
	Led();
	static Led* instance();
    void Lighten_Led_TX();
    void Lighten_Led_RX();
	void Off_Led_TX();
	void Off_Led_RX();
	void Toggle_Led_TX();
	void Toggle_Led_RX();
	~Led();
private:

	int tx_count;
	int rx_count;
};






#endif /* DRIVERS_INC_LED_H_ */
