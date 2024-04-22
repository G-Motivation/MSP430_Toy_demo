#include <stdio.h>
#include <msp430.h>
#include <sysSetup.h>
#include <interfaceUart.h>

// MAX7219 Register addresses
#define MAX_NOOP 0x00
#define MAX_DIGIT0 0x01
#define MAX_DIGIT1 0x02
#define MAX_DIGIT2 0x03
#define MAX_DIGIT3 0x04
#define MAX_DIGIT4 0x05
#define MAX_DIGIT5 0x06
#define MAX_DIGIT6 0x07
#define MAX_DIGIT7 0x08
#define MAX_DECODEMODE 0x09
#define MAX_INTENSITY 0x0A
#define MAX_SCANLIMIT 0x0B
#define MAX_SHUTDOWN 0x0C
#define MAX_DISPLAYTEST 0x0F

// Function prototypes
void spi_init();
void spi_max_transfer(unsigned char address, unsigned char data);

//主机初始化参数

const eUSCI_SPI_MasterConfig spiMasterConfig =

{

        EUSCI_B_SPI_CLOCKSOURCE_SMCLK,             // SMCLK Clock Source

        1000000,                                   // SMCLK = DCO = 3MHZ

        500000,                                    // SPICLK = 500khz

        EUSCI_A_SPI_MSB_FIRST,                     // MSB First

        EUSCI_A_SPI_PHASE_DATA_CHANGED_ONFIRST_CAPTURED_ON_NEXT,    // Phase

        EUSCI_A_SPI_CLOCKPOLARITY_INACTIVITY_HIGH, // High polarity

        EUSCI_A_SPI_3PIN                           // 3Wire SPI Mode

};

/**
 * hello.c
 */
#define GPIO // GPIO , LED, FIFO

/*
 * LPM0 等於  close MCLK
 */
int main(void)
{
    WDT_A_hold(WDT_A_BASE); // 停止看門狗
}

// Send 16 bits as: xxxxaaaadddddddd (ignore, address, data)
// and use active low Chip Select or active high Load pulse
// depending if the IC is a MAX7221 or MAX7219
void spi_max(uint8_t address, uint8_t data)
{
#ifdef USE_MAX7221
	P1OUT &= ~(SPI_CS);			// MAX7221 uses proper /CS
#endif
	UCA0TXBUF = address & 0b00001111;	// Send 4bit address as byte
	while (UCA0STAT & UCBUSY);		// Wait until done
	UCA0TXBUF = data;			// Send byte of data
	while (UCA0STAT & UCBUSY);
	P1OUT |= SPI_CS;			// /CS inactive or Load high
#ifndef USE_MAX7221
	P1OUT &= ~(SPI_CS);			// MAX7219 pulses Load high
#endif
}

// Enable harware SPI
void spi_init()
{
	UCA0CTL1 |= UCSWRST; 		// USCI in Reset State (for config)
	// Leading edge + MSB first + Master + Sync mode (spi)
	UCA0CTL0 = UCCKPH + UCMSB + UCMST + UCSYNC;
	UCA0CTL1 |= UCSSEL_2; 		// SMCLK as clock source
	UCA0BR0 |= 0x01; 		// SPI speed (same as SMCLK)
	UCA0BR1 = 0;
	P1SEL |= SPI_SIMO + SPI_CLK;	// Set port pins for USCI
	P1SEL2 |= SPI_SIMO + SPI_CLK;
	UCA0CTL1 &= ~UCSWRST; 		// Clear USCI Reset State
}

void initClockTo16MHz()
{
    // Configure one FRAM waitstate as required by the device datasheet for MCLK
    // operation beyond 8MHz _before_ configuring the clock system.
    FRCTL0 = FRCTLPW | NWAITS_1;

    // Clock System Setup
    CSCTL0_H = CSKEY_H; // Unlock CS registers
    CSCTL1 = DCOFSEL_0; // Set DCO to 1MHz

    // Set SMCLK = MCLK = DCO, ACLK = LFXTCLK (VLOCLK if unavailable)
    CSCTL2 = SELA__LFXTCLK | SELS__DCOCLK | SELM__DCOCLK;

    // Per Device Errata set divider to 4 before changing frequency to
    // prevent out of spec operation from overshoot transient
    CSCTL3 = DIVA__4 | DIVS__4 | DIVM__4; // Set all corresponding clk sources to divide by 4 for errata
    CSCTL1 = DCOFSEL_4 | DCORSEL;         // Set DCO to 16MHz

    // Delay by ~10us to let DCO settle. 60 cycles = 20 cycles buffer + (10us / (1/4MHz))
    __delay_cycles(60);
    CSCTL3 = DIVA__1 | DIVS__1 | DIVM__1; // Set all dividers to 1 for 16MHz operation
    CSCTL0_H = 0;                         // Lock CS registers
}
