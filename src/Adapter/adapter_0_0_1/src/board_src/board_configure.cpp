/*
 * adapter_configure.cpp
 *
 *  Created on: 2016年12月23日
 *      Author: cheri
 */
#include "adapter_board.h"
#include "board_configure.h"

bool Board_Configure::IsConfigured = false;


/* Factory of the Board_Configure, and only return the instance when not configure */
Board_Configure * Board_Configure::instance()
{
	static Board_Configure ins;
	if(!IsConfigured)
	{
		return &ins;
	}
	return 0;
}

/* The configure function */
void Board_Configure::Configure()
{
	Board_Init();
	IsConfigured = true;
}


/* Constructor */
Board_Configure::Board_Configure()
{
   IsConfigured = false;
}


/* The destructor */
Board_Configure::~Board_Configure()
{
	Board_Deinit();
	IsConfigured = false;
}

