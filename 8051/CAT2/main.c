/*
 * ============================================================================
 * Experiment: CAT 2 (Week 2)
 * Title: 8051 Development Board Tool Chain Setup & GPIO Interfacing
 * Hardware: AT89S52 Microcontroller (11.0592 MHz Crystal)
 * Description: Bare-metal memory-mapped GPIO access toggling P1.0 at ~1 Hz.
 *              Includes modular calibrated software delay function.
 * ============================================================================
 */

#include <reg51.h>

/* Define LED connected to Port 1 Pin 0 */
sbit LED = P1^0;

/**
 * @brief  Generates a calibrated millisecond software delay
 * @param  ms: Duration in milliseconds
 * @note   Calibrated for AT89S52 standard 12-clock architecture @ 11.0592 MHz.
 *         1 Machine Cycle = 12 / 11.0592 MHz = 1.085 us.
 */
void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 120; j++) {
            /* 120 iterations approx 1.0 ms */
        }
    }
}

void main(void) {
    /* Initialize Port 1 */
    P1 = 0x00;
    
    while (1) {
        /* Turn LED ON (Active High) */
        LED = 1;
        delay_ms(500);  /* 500 ms ON */
        
        /* Turn LED OFF */
        LED = 0;
        delay_ms(500);  /* 500 ms OFF */
    }
}
