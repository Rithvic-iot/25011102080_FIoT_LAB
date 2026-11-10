/*
 * ============================================================================
 * Experiment: CAT 1 (Week 1)
 * Title: Commercial IoT Device Teardown & 8051 Toolchain Bring-Up
 * Hardware: AT89S52 Microcontroller (11.0592 MHz Crystal)
 * Description: Minimal bare-metal test routine verifying Keil C51 toolchain,
 *              ISP flash programming, and initial GPIO bring-up status.
 * ============================================================================
 */

#include <reg51.h>

/* Port 1 Pin 0 used for initial hardware sanity verification */
sbit TEST_PIN = P1^0;

/* Software loop delay */
void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 120; j++) {
            /* ~1ms calibrated delay for 11.0592 MHz crystal */
        }
    }
}

void main(void) {
    /* Initialize GPIO Port 1 to logic LOW */
    P1 = 0x00;
    
    while (1) {
        /* Heartbeat blink to verify oscillator stability & MCU clock */
        TEST_PIN = 1;
        delay_ms(500);
        TEST_PIN = 0;
        delay_ms(500);
    }
}
