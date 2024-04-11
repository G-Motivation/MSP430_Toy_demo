#include <stdio.h>
#include <msp430.h>
#include <sysSetup.h>


//  Vin= 1V-3V -----------------
//     |      |                 |
//    10K     |                 |
//     |      |                 |
//     |      |                 |
//     -------| A2=2/3Vin       |
//     |      |                 |
//     10K    |                 |
//     |      |                 |
//     -------| A3=1/3Vin       |
//     |      |                 |
//    10K     |             P1.0|-->LED
//     |      |                 |
//    GND
/**
 * hello.c
 */
int main(void)
{

    sysSetup();
                                            // Lock CS registers

    printf("Hello World!\n");

    while (1)
    {
        P1OUT ^= BIT0; // Toggle LED
        __delay_cycles(100000);
    }

    return 0;
}
