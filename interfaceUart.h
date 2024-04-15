/*
 * pcu_uart.h
 *
 *  Created on: Jul 20, 2023
 *      Author: bensh
 */

#ifndef INTERFACEUART_H_
#define INTERFACEUART_H_

//*****************************************************************************
// List of Includes
//*****************************************************************************
//#include <global.h>
#include <stdint.h>
#include <stdio.h>

//*****************************************************************************
// Function result.
// @brief This enumeration specifies the possible results of the UART functions
//*****************************************************************************
typedef enum {
    FAIL = 0,
    SUCCESS = 1,
} uart_result_t;

//*****************************************************************************
// UART Interface
// @brief This enumeration specifies all selectable UART ports.
//*****************************************************************************
typedef enum {
    A0_uart = 0,
    A1_uart = 1,
    A2_uart = 2,
    A3_uart = 3,
} uart_Base_Address_t;

//*****************************************************************************
// UART Baudrate
// @brief This enumeration specifies all selectable UART baudrate speeds.
//
// For baudrate calculation, use the following link
// https://software-dl.ti.com/msp430/msp430_public_sw/mcu/msp430/MSP430BaudRateConverter/index.html
//*****************************************************************************
typedef enum {
    BAUDRATE_9600 = 0,
    BAUDRATE_19200 = 1,
    BAUDRATE_38400 = 2,
    BAUDRATE_57600 = 3,
    BAUDRATE_115200 = 4,
} uart_Baudrate_Value_t;

//*****************************************************************************
// UART Parity
// @brief This enumeration specifies all selectable UART ports.
//*****************************************************************************
typedef enum {
    NO_PARITY = 0,
    ODD_PARITY = 1,
    EVEN_PARITY = 2,
} uart_parity_mode_t;

//*****************************************************************************
// UART Stop Bits
// @brief This enumeration specifies all selectable UART ports.
//*****************************************************************************
typedef enum {
    ONE_STOP_BIT = 0,
    TWO_STOP_BITS = 1,
} uart_stop_bits_t;

//*****************************************************************************
// UART Initialization
//
// @brief This function initializes the target UART interface. The initialization
// configures baudrate speed, parity mode and number of stop bits.
// @param uartBaseAddress The board has four possible choices (uart_Base_Address_t)
// @param uartBaudrate The baudrate speed (uart_Baudrate_Value_t)
// @param uartParity The parity mode (uart_parity_mode_t)
// @oaram uartNumberStopBits (uart_stop_bits_t)
// @return TBD
//*****************************************************************************
int uartInit
(
    uint8_t uartBaseAddress,
    uint8_t uartBaudrate,
    uint8_t uartParity,
    uint8_t uartNumberStopBits
);

//*****************************************************************************
// Print on the Console port
//
// @brief Print a message on the Console port.
// @param str The target data
// @return TBD
//*****************************************************************************
int printk
(
    const char *str
);

//*****************************************************************************
// Transmit Data
//
// @brief Transmit an array through the target UART interface.
// @param uartBaseAddress The board has four possible choices (uart_Base_Address_t)
// @param buf The data to be transmitted
// @param size The size of data.
// @return TBD
//*****************************************************************************
void uartTransmitData
(
    uint16_t baseAddress,
    uint8_t *buf,
    uint8_t size
);

//*****************************************************************************
// Receive Data
//
// @brief Transmit an array through the target UART interface.
// @param uartBaseAddress The board has four possible choices (uart_Base_Address_t)
// @param buf The data to be transmitted
// @param size The size of data.
// @return TBD
//*****************************************************************************
uint8_t uartReceiveData
(
    uint8_t *buf,
    uint8_t size
);

#endif /* INTERFACEUART_H_ */
