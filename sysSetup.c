// ****************************************************************************
// List of Includes
// ****************************************************************************
#include <sysSetup.h>
#include <msp430.h>

// ****************************************************************************
// See sysSetup.h for details of how to use this function.
// ****************************************************************************
void sysSetup(void)
{
    //  # Stop Watchdog Timer #  //
    WDTCTL = WDTPW | WDTHOLD; // Stop WDT

     // Configure GPIO
     P1OUT &= ~BIT0; // Clear P1.0 output latch for a defined power-on state
     P1DIR |= BIT0;  // Set P1.0 to output direction

     PM5CTL0 &= ~LOCKLPM5; // Disable the GPIO power-on default high-impedance mode
                           // to activate previously configured port settings
     CSCTL0_H = CSKEY_H;   // Unlock CS registers

     // 時鐘初始化
     //  CSCTL0_H = CSKEY_H; // 解鎖CS暫存器
     //  CSCTL1 = DCOFSEL_3; // 將 DCO 設定為 4MHz
     //  CSCTL2 = SELA__LFXTCLK | SELS__DCOCLK | SELM__DCOCLK；
     //  CSCTL3 = DIVA__8 | DIVS__1 | DIVM__1； // 設定所有分頻器
     //  CSCTL0_H = CSKEY_H; // 解鎖CS暫存器
     //  CSCTL4 &= ~LFXTOFF; // 啟用 LFXT

     // CSCTL4 &= ~LFXTOFF;                                           // Enable LFXT
     // CSCTL0_H = 0;
}
