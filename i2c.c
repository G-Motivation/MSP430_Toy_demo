// if ( UCB0STAT & UCNACKIFG )   // 无应答 UCNACKIFG=1
#include <msp430.h>

//******************************************************************************
// I2C Interrupt ***************************************************************
//******************************************************************************
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = USCI_B0_VECTOR
__interrupt void USCI_B0_ISR(void)
#elif defined(__GNUC__)
void __attribute__((interrupt(USCI_B0_VECTOR))) USCI_B0_ISR(void)
#else
#error Compiler not supported!
#endif
{
    switch (__even_in_range(UCB0IV, USCI_I2C_UCBIT9IFG))
    {
    case USCI_NONE: // Vector 0: No interrupts
        break;
    case USCI_I2C_UCALIFG: // Vector 2: ALIFG
        break;
    case USCI_I2C_UCNACKIFG: // Vector 4: NACKIFG
        UCB0CTL1 |= UCTXSTP; // Send I2C stop condition
        UCB0IFG = 0;
        break;
    case USCI_I2C_UCSTTIFG: // Vector 6: STTIFG
        break;
    case USCI_I2C_UCSTPIFG: // Vector 8: STPIFG
        break;
    case USCI_I2C_UCRXIFG3: // Vector 10: RXIFG3
        break;
    case USCI_I2C_UCTXIFG3: // Vector 12: TXIFG3
        break;
    case USCI_I2C_UCRXIFG2: // Vector 14: RXIFG2
        break;
    case USCI_I2C_UCTXIFG2: // Vector 16: TXIFG2
        break;
    case USCI_I2C_UCRXIFG1: // Vector 18: RXIFG1
        break;
    case USCI_I2C_UCTXIFG1: // Vector 20: TXIFG1
        break;
    case USCI_I2C_UCRXIFG0: // Vector 22: RXIFG0
        rx_val = UCB0RXBUF;
        if (RXByteCtr)
        {
            ReceiveBuf[ReceiveIndex++] = rx_val;
            RXByteCtr--;
        }
        if (RXByteCtr == 1)
        {
            UCB0CTLW0 |= UCTXSTP;
        }
        else if (RXByteCtr == 0)
        {
            UCB0IE &= ~UCRXIE;
            MasterMode = IDLE_MODE;
            __bic_SR_register_on_exit(CPUOFF); // Exit LPM0
        }
        break;
    case USCI_I2C_UCTXIFG0: // Vector 24: TXIFG0
        switch (MasterMode)
        {
        case TX_REG_ADDRESS_MODE:
            UCB0TXBUF = TransmitRegAddr;
            if (RXByteCtr)
            {
                MasterMode = SWITCH_TO_RX_MODE; // Need to start receiving now
            }
            else
            {
                MasterMode = TX_DATA_MODE; // Continue to transmision with the data in Transmit Buffer
            }
            break;

        case SWITCH_TO_RX_MODE:
            UCB0IE |= UCRXIE;          // Enable RX interrupt
            UCB0IE &= ~UCTXIE;         // Disable TX interrupt
            UCB0CTLW0 &= ~UCTR;        // Switch to receiver
            MasterMode = RX_DATA_MODE; // State state is to receive data
            UCB0CTLW0 |= UCTXSTT;      // Send repeated start
            if (RXByteCtr == 1)
            {
                // Must send stop since this is the N-1 byte
                while ((UCB0CTLW0 & UCTXSTT))
                    ;
                UCB0CTLW0 |= UCTXSTP; // Send stop condition
            }
            break;

        case TX_DATA_MODE:
            if (TXByteCtr) // master要送到slave的長度
            {
                UCB0TXBUF = TransmitBuf[TransmitIndex++];
                // EUSCI_A_UART_transmitData(EUSCI_A3_BASE, UCB0TXBUF);
                TXByteCtr--;
            }
            else
            {
                // Done with transmission
                UCB0CTLW0 |= UCTXSTP; // Send stop condition
                MasterMode = IDLE_MODE;
                UCB0IE &= ~UCTXIE;                 // disable TX interrupt
                __bic_SR_register_on_exit(CPUOFF); // Exit LPM0
            }
            break;

        default:
            __no_operation();
            break;
        }
        break;
    default:
        break;
    }
}

//******************************************************************************
// I2C Interrupt ***************************************************************
//******************************************************************************
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = USCI_B1_VECTOR
__interrupt void USCI_B1_ISR(void)
#elif defined(__GNUC__)
void __attribute__((interrupt(USCI_B1_VECTOR))) USCI_B1_ISR(void)
#else
#error Compiler not supported!
#endif
{
    switch (__even_in_range(UCB1IV, USCI_I2C_UCBIT9IFG))
    {
    case USCI_NONE: // Vector 0: No interrupts
        break;
    case USCI_I2C_UCALIFG: // Vector 2: ALIFG
        break;
    case USCI_I2C_UCNACKIFG: // Vector 4: NACKIFG
        UCB1CTL1 |= UCTXSTP; // Send I2C stop condition
        UCB1IFG = 0;
        break;
    case USCI_I2C_UCSTTIFG: // Vector 6: STTIFG
        break;
    case USCI_I2C_UCSTPIFG: // Vector 8: STPIFG
        break;
    case USCI_I2C_UCRXIFG3: // Vector 10: RXIFG3
        break;
    case USCI_I2C_UCTXIFG3: // Vector 12: TXIFG3
        break;
    case USCI_I2C_UCRXIFG2: // Vector 14: RXIFG2
        break;
    case USCI_I2C_UCTXIFG2: // Vector 16: TXIFG2
        break;
    case USCI_I2C_UCRXIFG1: // Vector 18: RXIFG1
        break;
    case USCI_I2C_UCTXIFG1: // Vector 20: TXIFG1
        break;
    case USCI_I2C_UCRXIFG0: // Vector 22: RXIFG0
        rx_val = UCB1RXBUF;
        if (RXByteCtr)
        {
            ReceiveBuf[ReceiveIndex++] = rx_val;
            RXByteCtr--;
        }
        if (RXByteCtr == 1)
        {
            UCB1CTLW0 |= UCTXSTP;
        }
        else if (RXByteCtr == 0)
        {
            UCB1IE &= ~UCRXIE;
            MasterMode = IDLE_MODE;
            __bic_SR_register_on_exit(CPUOFF); // Exit LPM0
        }
        break;
    case USCI_I2C_UCTXIFG0: // Vector 24: TXIFG0
        switch (MasterMode)
        {
        case TX_REG_ADDRESS_MODE:
            UCB1TXBUF = TransmitRegAddr;
            if (RXByteCtr)
            {
                MasterMode = SWITCH_TO_RX_MODE; // Need to start receiving now
            }
            else
            {
                MasterMode = TX_DATA_MODE; // Continue to transmision with the data in Transmit Buffer
            }
            break;

        case SWITCH_TO_RX_MODE:
            UCB1IE |= UCRXIE;          // Enable RX interrupt
            UCB1IE &= ~UCTXIE;         // Disable TX interrupt
            UCB1CTLW0 &= ~UCTR;        // Switch to receiver
            MasterMode = RX_DATA_MODE; // State state is to receive data
            UCB1CTLW0 |= UCTXSTT;      // Send repeated start
            if (RXByteCtr == 1)
            {
                // Must send stop since this is the N-1 byte
                while ((UCB1CTLW0 & UCTXSTT))
                    ;
                UCB1CTLW0 |= UCTXSTP; // Send stop condition
            }
            break;

        case TX_DATA_MODE:
            if (TXByteCtr)
            {
                UCB1TXBUF = TransmitBuf[TransmitIndex++];
                // EUSCI_A_UART_transmitData(EUSCI_A3_BASE, UCB0TXBUF);
                TXByteCtr--;
            }
            else
            {
                // Done with transmission
                UCB1CTLW0 |= UCTXSTP; // Send stop condition
                MasterMode = IDLE_MODE;
                UCB1IE &= ~UCTXIE;                 // disable TX interrupt
                __bic_SR_register_on_exit(CPUOFF); // Exit LPM0
            }
            break;

        default:
            __no_operation();
            break;
        }
        break;
    default:
        break;
    }
}

//******************************************************************************
// I2C Interrupt ***************************************************************
//******************************************************************************
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = USCI_B2_VECTOR
__interrupt void USCI_B2_ISR(void)
#elif defined(__GNUC__)
void __attribute__((interrupt(USCI_B2_VECTOR))) USCI_B2_ISR(void)
#else
#error Compiler not supported!
#endif
{
    switch (__even_in_range(UCB2IV, USCI_I2C_UCBIT9IFG))
    {
    case USCI_NONE: // Vector 0: No interrupts
        break;
    case USCI_I2C_UCALIFG: // Vector 2: ALIFG
        break;
    case USCI_I2C_UCNACKIFG: // Vector 4: NACKIFG
        UCB2CTL1 |= UCTXSTP; // Send I2C stop condition
        UCB2IFG = 0;
        break;
    case USCI_I2C_UCSTTIFG: // Vector 6: STTIFG
        break;
    case USCI_I2C_UCSTPIFG: // Vector 8: STPIFG
        break;
    case USCI_I2C_UCRXIFG3: // Vector 10: RXIFG3
        break;
    case USCI_I2C_UCTXIFG3: // Vector 12: TXIFG3
        break;
    case USCI_I2C_UCRXIFG2: // Vector 14: RXIFG2
        break;
    case USCI_I2C_UCTXIFG2: // Vector 16: TXIFG2
        break;
    case USCI_I2C_UCRXIFG1: // Vector 18: RXIFG1
        break;
    case USCI_I2C_UCTXIFG1: // Vector 20: TXIFG1
        break;
    case USCI_I2C_UCRXIFG0: // Vector 22: RXIFG0
        rx_val = UCB2RXBUF;
        if (RXByteCtr)
        {
            ReceiveBuf[ReceiveIndex++] = rx_val;
            RXByteCtr--;
        }
        if (RXByteCtr == 1)
        {
            UCB2CTLW0 |= UCTXSTP;
        }
        else if (RXByteCtr == 0)
        {
            UCB2IE &= ~UCRXIE;
            MasterMode = IDLE_MODE;
            __bic_SR_register_on_exit(CPUOFF); // Exit LPM0
        }
        break;
    case USCI_I2C_UCTXIFG0: // Vector 24: TXIFG0
        switch (MasterMode)
        {
        case TX_REG_ADDRESS_MODE:
            UCB2TXBUF = TransmitRegAddr;
            if (RXByteCtr)
            {
                MasterMode = SWITCH_TO_RX_MODE; // Need to start receiving now
            }
            else
            {
                MasterMode = TX_DATA_MODE; // Continue to transmision with the data in Transmit Buffer
            }
            break;

        case SWITCH_TO_RX_MODE:
            UCB2IE |= UCRXIE;          // Enable RX interrupt
            UCB2IE &= ~UCTXIE;         // Disable TX interrupt
            UCB2CTLW0 &= ~UCTR;        // Switch to receiver
            MasterMode = RX_DATA_MODE; // State state is to receive data
            UCB2CTLW0 |= UCTXSTT;      // Send repeated start
            if (RXByteCtr == 1)
            {
                // Must send stop since this is the N-1 byte
                while ((UCB2CTLW0 & UCTXSTT))
                    ;
                UCB2CTLW0 |= UCTXSTP; // Send stop condition
            }
            break;

        case TX_DATA_MODE:
            if (TXByteCtr)
            {
                UCB2TXBUF = TransmitBuf[TransmitIndex++];
                // EUSCI_A_UART_transmitData(EUSCI_A3_BASE, UCB0TXBUF);
                TXByteCtr--;
            }
            else
            {
                // Done with transmission
                UCB2CTLW0 |= UCTXSTP; // Send stop condition
                MasterMode = IDLE_MODE;
                UCB2IE &= ~UCTXIE;                 // disable TX interrupt
                __bic_SR_register_on_exit(CPUOFF); // Exit LPM0
            }
            break;

        default:
            __no_operation();
            break;
        }
        break;
    default:
        break;
    }
}
