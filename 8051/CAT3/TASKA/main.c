/*
 * ============================================================================
 * Experiment: CAT 3 (Week 3)
 * Title: Timer-Based LED Pattern Generator & Button Interrupt / Switch Polling
 * Hardware: AT89S52 MCU, 4 LEDs (P1.0-P1.3), Push Button (P3.2)
 * Description: 4-State LED Sequencer with software contact debouncing.
 *              Mode 1: Running LED
 *              Mode 2: 4-Bit Binary Counter (0-15)
 *              Mode 3: Alternating Pattern (1010 <-> 0101)
 *              Mode 4: All-LED Flash (1111 <-> 0000)
 * ============================================================================
 */

#include <reg51.h>

/* Button connected to P3.2 with external 10k pull-up (Active LOW) */
sbit BUTTON = P3^2;

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 120; j++);
    }
}

/* Global state variable */
unsigned char current_mode = 0;
unsigned char counter_val = 0;

void main(void) {
    BUTTON = 1;  /* Configure P3.2 as input pin */
    P1 = 0x00;   /* Turn off all LEDs initially */

    while (1) {
        /* Check for switch press (Active LOW) */
        if (BUTTON == 0) {
            delay_ms(25);  /* 25ms Debounce delay */
            if (BUTTON == 0) {
                /* Valid button transition detected */
                current_mode++;
                if (current_mode > 4) {
                    current_mode = 1;
                }
                counter_val = 0;
                /* Wait for button release */
                while (BUTTON == 0);
                delay_ms(25);  /* Release debounce */
            }
        }

        /* Execute active mode pattern */
        switch (current_mode) {
            case 1:
                /* Mode 1: Running LED (LED1 -> LED2 -> LED3 -> LED4) */
                P1 = 0x01; delay_ms(200);
                if (BUTTON == 0) break;
                P1 = 0x02; delay_ms(200);
                if (BUTTON == 0) break;
                P1 = 0x04; delay_ms(200);
                if (BUTTON == 0) break;
                P1 = 0x08; delay_ms(200);
                break;

            case 2:
                /* Mode 2: 4-bit Binary Counter (0000 to 1111) */
                P1 = (counter_val & 0x0F);
                delay_ms(300);
                counter_val++;
                if (counter_val > 15) counter_val = 0;
                break;

            case 3:
                /* Mode 3: Alternating Pattern (1010 <-> 0101) */
                P1 = 0x0A; delay_ms(250);
                if (BUTTON == 0) break;
                P1 = 0x05; delay_ms(250);
                break;

            case 4:
                /* Mode 4: All-LED Flash (1111 <-> 0000) */
                P1 = 0x0F; delay_ms(250);
                if (BUTTON == 0) break;
                P1 = 0x00; delay_ms(250);
                break;

            default:
                P1 = 0x00;
                break;
        }
    }
}
