/*
 * @brief Blinky example using timers and sysTick
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2013
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

#include "board.h"
#include <stdio.h>

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

#define TICKRATE_HZ1 (15)	/* 15 ticks per second */

uint32_t index = 0;

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/

/*****************************************************************************
 * Private functions
 ****************************************************************************/

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/**
 * @brief	Handle interrupt from SysTick timer
 * @return	Nothing
 */
void SysTick_Handler(void)
{

	switch(index)
	{
	case 0:
		{
			Board_LED_Set(0, true);
			Board_LED_Set(1, false);
			Board_LED_Set(2, false);
			break;
		}
	case 1:
		{
			Board_LED_Set(0, false);
			Board_LED_Set(1, true);
			Board_LED_Set(2, false);
			break;
		}
	case 2:
		{
			Board_LED_Set(0, false);
			Board_LED_Set(2, true);
			Board_LED_Set(1, false);
			break;
		}
	case 3:
		{
			Board_LED_Set(0, true);
			Board_LED_Set(1, true);
			Board_LED_Set(2, false);
			break;
		}
	case 4:
		{
			Board_LED_Set(0, false);
			Board_LED_Set(1, true);
			Board_LED_Set(2, true);
			break;
		}

	case 5:
		{
			Board_LED_Set(1, false);
			Board_LED_Set(0, true);
			Board_LED_Set(2, true);
			break;
		}

	case 6:
		{
			Board_LED_Set(1, true);
			Board_LED_Set(0, true);
			Board_LED_Set(2, true);
			break;
		}
	default:
		break;

	}
	//index++;
	if(++index == 7)
	{
		index = 0;
	}

}

/**
 * @brief	main routine for blinky example
 * @return	Function should not exit.
 */
int main(void)
{
	uint32_t sysTickRate;


	SystemCoreClockUpdate();
	Board_Init();
	Board_LED_Set(0, true);
	Board_LED_Set(1, false);
	Board_LED_Set(2, true);

	/* The sysTick counter only has 24 bits of precision, so it will
	   overflow quickly with a fast core clock. You can alter the
	   sysTick divider to generate slower sysTick clock rates. */
	Chip_Clock_SetSysTickClockDiv(1);

	/* A SysTick divider is present that scales the sysTick rate down
	   from the core clock. Using the SystemCoreClock variable as a
	   rate reference for the SysTick_Config() function won't work,
	   so get the sysTick rate by calling Chip_Clock_GetSysTickClockRate() */
	sysTickRate = Chip_Clock_GetSysTickClockRate();

	/* Enable and setup SysTick Timer at a periodic rate */
	SysTick_Config(sysTickRate / TICKRATE_HZ1);

	/* LEDs toggle in interrupt handlers */
	while (1) {
		__WFI();
	}

	return 0;
}
