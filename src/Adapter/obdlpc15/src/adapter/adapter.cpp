/**
 * See the file LICENSE for redistribution information.
 *
 * Copyright (c) 2009-2016 ObdDiag.Net. All rights reserved.
 *
 */

#include <lstring.h>
#include <cctype>
#include <LPC15xx.h>
#include <Timer.h>
#include <GPIODrv.h>
#include <CmdUart.h>
#include <CanDriver.h>
#include <EcuUart.h>
#include <PwmDriver.h>
#include <AdcDriver.h>
#include <led.h>
#include <adaptertypes.h>

using namespace std;
using namespace util;

static string CmdBuffer(RX_CMD_LEN);
static BT_UART* bt_uart;

/**
 * Enable the clocks and peripherals, initialize the drivers
 */
static void SetAllRegisters()
{
    // Enable MRT timer
    LPC_SYSCON->SYSAHBCLKCTRL1 |= (1 << 0);
    LPC_SYSCON->PRESETCTRL1 &= ~(1 << 0);
    
    // Enable RIT timer
    LPC_SYSCON->SYSAHBCLKCTRL1 |= (1 << 1);
    LPC_SYSCON->PRESETCTRL1 &= ~(1 << 1);
    
    LPC_SYSCON->SYSAHBCLKCTRL0 |= (1 << 11); // MUX
    LPC_SYSCON->SYSAHBCLKCTRL0 |= (1 << 12); // SVM
    LPC_SYSCON->SYSAHBCLKCTRL0 |= (1 << 13); // IOCON
    
    // LPC I/O pins
    LPC_SYSCON->SYSAHBCLKCTRL0 |= (1 << 14); // PIO0
    
    BT_UART::configure();
    EcuUart::configure();
    CanDriver::configure();
    AdptLED::configure();
    //PwmDriver::configure();
   // AdcDriver::configure();
}

/**
 * Outer interface UART receive callback
 * @param[in] ch Character received from UART
 */
static bool UserUartRcvHandler(uint8_t ch)
{
    static string cmdBuffer(RX_BUFFER_LEN);
    bool ready = false;
    
    if (cmdBuffer.length() >= (RX_BUFFER_LEN - 1)) {
        cmdBuffer.resize(0); // Truncate it
    }

    if (AdapterConfig::instance()->getBoolProperty(PAR_ECHO) && ch != '\n') {
        bt_uart->send(ch);
        if (ch == '\r' && AdapterConfig::instance()->getBoolProperty(PAR_LINEFEED)) {
            bt_uart->send('\n');
        }
    }
    
    if (ch == '\r') { // Got cmd terminator
        CmdBuffer = cmdBuffer;
        cmdBuffer.resize(0);
        ready = true;
    }
    else if (isprint(ch)) { // this will skip '\n' as well
        cmdBuffer += ch;
    }
    
    return ready;
}

/**
 * Send string to UART
 * @param[in] str String to send
 */
void AdptSendString(const util::string& str)
{
    bt_uart->send(str);
}

const int UART_SPEED = 115200;

/**
 * Adapter main loop
 */
static void AdapterRun() 
{
    bt_uart = BT_UART::instance();
    bt_uart->init(UART_SPEED);
    bt_uart->handler(UserUartRcvHandler);
    AdptPowerModeConfigure();
    AdptDispatcherInit();

    for(;;) {    
        if (bt_uart->ready()) {
            bt_uart->ready(false);
            AdptOnCmd(CmdBuffer);
        }
        else {
            AdptCheckHeartBeat();
        }
        __WFI(); // goto sleep
    }
}

int main(void)
{
    SystemCoreClockUpdate();
    
    SetAllRegisters();
    AdapterRun();
}

