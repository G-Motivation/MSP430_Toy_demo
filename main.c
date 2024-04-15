#include <stdio.h>
#include <msp430.h>
#include <sysSetup.h>
#include <interfaceUart.h>

//  Vin= 1V-3V -----------------
//     |      |                 |
//    10K     |                 |
//     |      |                 |
//     |      |                 |
//     -------| A2=2/3Vin   P5.1|-> SPI Data Out (UCB1SOMI)
//     |      |                 |
//     10K    |             P5.0|<- SPI Data In (UCB1SIMO)
//     |      |             P5.2|-> SPI Serial Clock Out (UCB1CLK)
//     |      |             P5.3|<- SPI Slave Select (UCB1STE)
//     -------| A3=1/3Vin   P2.5|--> UART UCA1TXD
//     |      |             P2.6|--> UART UCA1RXD
//    10K     |             P1.0|-->LED
//     |      |                 |
//    GND
/**
 * hello.c
 */
#define GPIO // GPIO , LED, FIFO

/*
 * LPM0 等於  close MCLK
 */
int main(void)
{
    sysSetup();
    initClockTo16MHz();
    uartInit(A1_uart,
             BAUDRATE_9600,
             NO_PARITY,
             ONE_STOP_BIT);
    printk("Select Mode: LED(0x01),GPIO(0x02),FIFO(0x03)");

//    EUSCI_A_UART_transmitData(EUSCI_A1_BASE, 0xDE);


#ifdef LED
    sysSetup();
    // Lock CS registers

    printf("LED\n");

    while (1)
    {
        P1OUT ^= BIT0; // Toggle LED
        __delay_cycles(100000);
    }

    return 0;
#endif

#ifdef GPIO
//    sysSetup();
    // Lock CS registers

//    printf("GPIO!\n");

    while (1)
    {
//        printf("GPIO!\n");
        printk("SGPIO\n");

        P1OUT ^= BIT0; // Toggle LED
        __delay_cycles(100000);
    }

    return 0;
#endif

#ifdef FIFO
    sysSetup();
    // Lock CS registers

    printf("GPIO!\n");

    while (1)
    {
        P1OUT ^= BIT0; // Toggle LED
        __delay_cycles(100000);
    }

    return 0;
#endif
}

void initClockTo16MHz()
{
    // Configure one FRAM waitstate as required by the device datasheet for MCLK
    // operation beyond 8MHz _before_ configuring the clock system.
    FRCTL0 = FRCTLPW | NWAITS_1;

    // Clock System Setup
    CSCTL0_H = CSKEY_H;                     // Unlock CS registers
    CSCTL1 = DCOFSEL_0;                     // Set DCO to 1MHz

    // Set SMCLK = MCLK = DCO, ACLK = LFXTCLK (VLOCLK if unavailable)
    CSCTL2 = SELA__LFXTCLK | SELS__DCOCLK | SELM__DCOCLK;

    // Per Device Errata set divider to 4 before changing frequency to
    // prevent out of spec operation from overshoot transient
    CSCTL3 = DIVA__4 | DIVS__4 | DIVM__4;   // Set all corresponding clk sources to divide by 4 for errata
    CSCTL1 = DCOFSEL_4 | DCORSEL;           // Set DCO to 16MHz

    // Delay by ~10us to let DCO settle. 60 cycles = 20 cycles buffer + (10us / (1/4MHz))
    __delay_cycles(60);
    CSCTL3 = DIVA__1 | DIVS__1 | DIVM__1;   // Set all dividers to 1 for 16MHz operation
    CSCTL0_H = 0;                           // Lock CS registers
}
