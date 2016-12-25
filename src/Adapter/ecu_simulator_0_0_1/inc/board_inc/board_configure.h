/*
 * ecu_configure.h
 *
 *  Created on: 2016年12月23日
 *      Author: Topon-Edison
 */

#ifndef DRIVERS_INC_BOARD_CONFIGURE_H_
#define DRIVERS_INC_BOARD_CONFIGURE_H_
#include <cstdint>
/* The class for configure the board, bring the board to a
 * appropriate state to start the operation
 */
class Board_Configure
{
public:
	static Board_Configure * instance(); // for singleton mode
	~Board_Configure();                  // Destructor
	void Configure();                    //  function used to configure the board
	uint32_t Get_MainClockRate();        // Get the main clock rate of the board
private:
	Board_Configure();                   // constructor
	static  bool IsConfigured;           // the variable indicates the ECU board whether configured or not
};



#endif /* DRIVERS_INC_BOARD_CONFIGURE_H_ */
