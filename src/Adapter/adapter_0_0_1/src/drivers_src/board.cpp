/*
 * board.cpp
 *
 *  Created on: 2016年12月20日
 *      Author: cheri
 */



#include "board.h"


/**
 *
 * @brief frequency of the different clock sources of the board
 *
 */
const uint32_t OscRateIn = 12000000;      /*!< The frequency of the external crystal 12MHZ */
const uint32_t RTCOscRateIn = 32768;      /*!< The frequency of the RTC internal oscillator 32.76KHZ */




/*****************************************************************************
 * Private functions
 ****************************************************************************/
/* Set up the main clock */
void Board_Configure_Main_Clock()
{
	/* Set main clock source to the system PLL. This will drive 72MHz
	for the main clock */
	Chip_Clock_SetMainClockSource(SYSCTL_MAINCLKSRC_SYSPLLOUT);

	/* Set system clock divider to 1 */
	Chip_Clock_SetSysClockDiv(1);

	/* Setup FLASH access timing for 72MHz */
	Chip_FMC_SetFLASHAccess(SYSCTL_FLASHTIM_72MHZ_CPU);
}

/* Setup the clock for all USART device */
void Board_Configure_USART_Clock()
{
	/* The rate 14976000 is the lowest common multiple(LCM)
	   of 1152000 and 10400(for KWP) */
	uint32_t usart_rate = 14976000;

	/* Set the USART fractional baud rate generator register, to get the frequency
	   14976000 */
	Chip_Clock_SetUARTBaseClockRate(usart_rate,true);
}


/*Setup the clock for can device */
void Board_Configure_CAN_Clock()
{

}



/* Set up the system PLL */
void Board_Setup_System_PLL()
{
    /* Set system PLL input to system oscillator */
	Chip_Clock_SetSystemPLLSource(SYSCTL_PLLCLKSRC_SYSOSC);

	/* Power down PLL to change the PLL divider ratio */
	Chip_SYSCTL_PowerDown(SYSCTL_POWERDOWN_SYSPLL_PD);

	/* Setup PLL for main oscillator rate (FCLKIN = 12MHz) * 6 = 72MHz
		MSEL = 5 (this is pre-decremented), PSEL = 1 (for P = 2)
		FCLKOUT = FCLKIN * (MSEL + 1) = 12MHz * 6 = 72MHz
		FCCO = FCLKOUT * 2 * P = 72MHz * 2 * 2 = 288MHz (within FCCO range) */
	Chip_Clock_SetupSystemPLL(5, 1);

	/* Power up system PLL */
	Chip_SYSCTL_PowerUp(SYSCTL_POWERDOWN_SYSPLL_PD);

	/* Wait for PLL to lock */
	while (!Chip_Clock_IsSystemPLLLocked()) {}
}


/* Setup USB PLL */
void Board_Setup_USB_PLL()
{
    /* Set USB PLL input to system oscillator */
	Chip_Clock_SetUSBPLLSource(SYSCTL_PLLCLKSRC_SYSOSC);

    /* Power down PLL to change the PLL divider ratio */
	Chip_SYSCTL_PowerDown(SYSCTL_POWERDOWN_USBPLL_PD);

    /* Setup PLL for main oscillator rate (FCLKIN = 12MHz) * 4 = 48MHz
	   MSEL = 3 (this is pre-decremented), PSEL = 1 (for P = 2)
	   FCLKOUT = FCLKIN * (MSEL + 1) = 12MHz * 4 = 48MHz
	   FCCO = FCLKOUT * 2 * 2 = 48MHz * 2 * 4 = 192MHz (within FCCO range) */
	Chip_Clock_SetupUSBPLL(3, 1);

    /* Power up USB PLL */
	Chip_SYSCTL_PowerUp(SYSCTL_POWERDOWN_USBPLL_PD);

    /* Wait for PLL to lock */
	while (!Chip_Clock_IsUSBPLLLocked()) {}

}


/* Setup SCT PLL */
void Board_Setup_SCT_PLL()
{

    /* Set SCT PLL input to system oscillator */
	Chip_Clock_SetSCTPLLSource(SYSCTL_PLLCLKSRC_SYSOSC);

	/* Power down PLL to change the PLL divider ratio */
	Chip_SYSCTL_PowerDown(SYSCTL_POWERDOWN_SCTPLL_PD);

    /* Setup PLL for main oscillator rate (FCLKIN = 12MHz) * 6 = 72MHz
	   MSEL = 5 (this is pre-decremented), PSEL = 1 (for P = 2)
	   FCLKOUT = FCLKIN * (MSEL + 1) = 12MHz * 6 = 72MHz
	   FCCO = FCLKOUT * 2 * P = 72MHz * 2 * 2 = 288MHz (within FCCO range) */
	Chip_Clock_SetupSCTPLL(5, 1);

	/* Powerup SCT PLL */
	Chip_SYSCTL_PowerUp(SYSCTL_POWERDOWN_SCTPLL_PD);

	/* Wait for PLL to lock */
	while (!Chip_Clock_IsSCTPLLLocked()) {}

}


/* Setup the system oscillator */
void Board_Setup_System_Oscillator()
{
    volatile int i;
	/* Power down the system oscillator to configure it */
	Chip_SYSCTL_PowerDown(SYSCTL_POWERDOWN_SYSOSC_PD);

	/* Disable the system oscillator bypass bit and set
	 * the frequency range lower : 1MHZ - 20MHZ */
    Chip_Clock_Set_SYSOSCCTRL(false,false);

	/* Power up the system oscillator */
	Chip_SYSCTL_PowerUp(SYSCTL_POWERDOWN_SYSOSC_PD);

	/* Wait 200us for OSC to be stablized, no status
		indication, dummy wait. */
	for(i = 0; i < 0x200; ++i){}
}

/* Enable the clock for the device */
void Board_Enable_PeriphClock()
{
	/* Enable the peripheral clock */
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_ROM);
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_SRAM1);
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_SRAM2);
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_FLASH);
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_EEPROM);
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_SWM);
    Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_IOCON);
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_GPIO0);
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_GPIO1);
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_MRT);
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_RIT);
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_CAN);
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_UART0);
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_UART1);
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_UART2);
	Chip_Clock_EnablePeriphClock(SYSCTL_CLOCK_MUX);
}


/* Configure the bluetooth USART IO */
void Board_Configure_Bluetooth_USART_IO()
{

	Chip_SYSCTL_AssertPeriphReset(RESET_UART0);
	Chip_SYSCTL_DeassertPeriphReset(RESET_UART0);
}


/* Configure the KWP2000 USART IO */
void Board_Configure_KWP_USART_IO()
{
	Chip_SYSCTL_AssertPeriphReset(RESET_UART1);
	Chip_SYSCTL_DeassertPeriphReset(RESET_UART1);
}


/* Configure the CAN IO */
void Board_Configure_CAN_IO()
{
	Chip_SYSCTL_AssertPeriphReset(RESET_CAN);
	Chip_SYSCTL_DeassertPeriphReset(RESET_CAN);
}


/* Configure the LED IO */
void Board_Configure_LED_IO()
{

}


/* Configure IO for the board */
void Board_Configure_IO()
{
   Board_Configure_Bluetooth_USART_IO();
   Board_Configure_KWP_USART_IO();
   Board_Configure_CAN_IO();
   Board_Configure_LED_IO();
}

/*****************************************************************************
 * Public functions
 ****************************************************************************/

/* Initialize the board */
void Board_Init()
{
	/* Set up the system oscilltor */
	Board_Setup_System_Oscillator();

	/* Set up the system PLL */
	Board_Setup_System_PLL();

	/* Set up the USB PLL */
	Board_Setup_USB_PLL();

	/* Set up the SCT PLL */
	Board_Setup_SCT_PLL();

	/* Configure the system main clock */
	Board_Configure_Main_Clock();

	/* Configure board USART clock */
	Board_Configure_USART_Clock();

	/* Enable the peripheral clock */
	Board_Enable_PeriphClock();

	/* Configure the pin for the peripheral device */
	Board_Configure_IO();
}



