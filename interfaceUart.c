#include <interfaceUart.h>
#include <tiDriver/driverlib.h>
#include <msp430.h>

#define CONSOLE_PORT A1_uart

//*****************************************************************************
// See lpdu_uart.h for details of how to use this function.
//*****************************************************************************
int uartInit(
    uint8_t uartBaseAddress,
    uint8_t uartBaudrate,
    uint8_t uartParity,
    uint8_t uartNumberStopBits)
{
    EUSCI_A_UART_initParam param = {0};
    uint8_t gpio_port;
    uint8_t gpio_pin;
    uint8_t gpio_function;
    uint16_t baseAddress;

    switch (uartBaseAddress)
    {
    case A0_uart:
        baseAddress = EUSCI_A0_BASE;
        gpio_port = GPIO_PORT_P2;
        gpio_pin = GPIO_PIN0 + GPIO_PIN1;
        gpio_function = GPIO_SECONDARY_MODULE_FUNCTION;
        break;
    case A1_uart:
        baseAddress = EUSCI_A1_BASE;
        gpio_port = GPIO_PORT_P2;
        gpio_pin = GPIO_PIN5 + GPIO_PIN6;
        gpio_function = GPIO_SECONDARY_MODULE_FUNCTION;
        break;
    case A2_uart:
        baseAddress = EUSCI_A2_BASE;
        gpio_port = GPIO_PORT_P5;
        gpio_pin = GPIO_PIN4 + GPIO_PIN5;
        gpio_function = GPIO_PRIMARY_MODULE_FUNCTION;
        break;
    case A3_uart:
        baseAddress = EUSCI_A3_BASE;
        gpio_port = GPIO_PORT_P6;
        gpio_pin = GPIO_PIN0 + GPIO_PIN1;
        gpio_function = GPIO_PRIMARY_MODULE_FUNCTION;
        break;
    default:
        break;
    }

    switch (uartBaudrate)
    {
    case BAUDRATE_9600:
        param.clockPrescalar = 104;
        param.firstModReg = 2;
        param.secondModReg = 182;
        param.overSampling = EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION;
        break;
    case BAUDRATE_19200:
        param.clockPrescalar = 52;
        param.firstModReg = 1;
        param.secondModReg = 73;
        param.overSampling = EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION;
        break;
    case BAUDRATE_38400:
        param.clockPrescalar = 26;
        param.firstModReg = 0;
        param.secondModReg = 214;
        param.overSampling = EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION;
        break;
    case BAUDRATE_57600:
        param.clockPrescalar = 17;
        param.firstModReg = 5;
        param.secondModReg = 221;
        param.overSampling = EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION;
        break;
    case BAUDRATE_115200:
        param.clockPrescalar = 8;
        param.firstModReg = 10;
        param.secondModReg = 247;
        param.overSampling = EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION;
        break;
    default:
        break;
    }

    switch (uartParity)
    {
    case NO_PARITY:
        param.parity = EUSCI_A_UART_NO_PARITY;
        break;
    case ODD_PARITY:
        param.parity = EUSCI_A_UART_ODD_PARITY;
        break;
    case EVEN_PARITY:
        param.parity = EUSCI_A_UART_EVEN_PARITY;
        break;
    default:
        break;
    }

    switch (uartNumberStopBits)
    {
    case ONE_STOP_BIT:
        param.numberofStopBits = EUSCI_A_UART_ONE_STOP_BIT;
        break;
    case TWO_STOP_BITS:
        param.numberofStopBits = EUSCI_A_UART_TWO_STOP_BITS;
        break;
    default:
        break;
    }

    param.selectClockSource = EUSCI_A_UART_CLOCKSOURCE_SMCLK;
    param.msborLsbFirst = EUSCI_A_UART_LSB_FIRST;
    param.uartMode = EUSCI_A_UART_MODE;

    if (STATUS_FAIL == EUSCI_A_UART_init(baseAddress, &param))
    {
        return FAIL;
    }

    GPIO_setAsPeripheralModuleFunctionInputPin(
        gpio_port,
        gpio_pin,
        gpio_function);

    // GPIO_setOutputLowOnPin( GPIO_PORT_P6, GPIO_PIN0 );
    // GPIO_setAsOutputPin( GPIO_PORT_P6, GPIO_PIN0 );
    // GPIO_setAsPeripheralModuleFunctionInputPin( GPIO_PORT_P6, GPIO_PIN1, GPIO_PRIMARY_MODULE_FUNCTION );
    // GPIO_setAsPeripheralModuleFunctionOutputPin( GPIO_PORT_P6, GPIO_PIN0, GPIO_PRIMARY_MODULE_FUNCTION );

    // EUSCI_A_UART_enableInterrupt(baseAddress, EUSCI_A_UART_RECEIVE_INTERRUPT);
    //__enable_interrupt();

    EUSCI_A_UART_enable(baseAddress);
    UCA0IE |= UCRXIE;
    __enable_interrupt();

    return SUCCESS;
}

int printk(
    const char *str)
{
    int status = FAIL;

    if (str != NULL)
    {
        status = SUCCESS;
        while (*str != '\0')
        {

            switch (CONSOLE_PORT)
            {
            case A0_uart:
                while (!(UCA0IFG & UCTXIFG))
                    ;
                UCA0TXBUF = *str;
                if (*str == '\n')
                {
                    while (!(UCA0IFG & UCTXIFG))
                        ;
                    UCA0TXBUF = '\r';
                }
                break;
            case A1_uart:
                while (!(UCA1IFG & UCTXIFG))
                    ;
                UCA1TXBUF = *str;
                if (*str == '\n')
                {
                    while (!(UCA1IFG & UCTXIFG))
                        ;
                    UCA1TXBUF = '\r';
                }
                break;
            case A2_uart:
                while (!(UCA2IFG & UCTXIFG))
                    ;
                UCA2TXBUF = *str;
                if (*str == '\n')
                {
                    while (!(UCA2IFG & UCTXIFG))
                        ;
                    UCA2TXBUF = '\r';
                }
                break;
            case A3_uart:
                while (!(UCA3IFG & UCTXIFG))
                    ;
                UCA3TXBUF = *str;
                if (*str == '\n')
                {
                    while (!(UCA3IFG & UCTXIFG))
                        ;
                    UCA3TXBUF = '\r';
                }
                break;
            }

            str++;
        }
    }
    return status;
}