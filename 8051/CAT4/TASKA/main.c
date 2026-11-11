/*
 * ============================================================================
 * Experiment: CAT 4 (Week 4)
 * Title: Human-Machine Interface using Matrix Keypad, LEDs & 7-Segment Display
 * Hardware: AT89S52 MCU, 4x4 Keypad (Port 2), 7-Seg Display (Port 0), LEDs (Port 1)
 * Description: Scans 4x4 matrix keypad, decodes key value (0-9), drives 7-segment
 *              display feedback, and triggers specific LED operating modes.
 * ============================================================================
 */

#include <reg51.h>

/* Port Assignments */
#define KEYPAD_PORT P2
#define SEVEN_SEG_PORT P0
#define LED_PORT P1

/* Common-Cathode 7-Segment lookup table for digits 0-9 */
code unsigned char seg_lookup[10] = {
    0x3F, /* 0 */
    0x06, /* 1 */
    0x5B, /* 2 */
    0x4F, /* 3 */
    0x66, /* 4 */
    0x6D, /* 5 */
    0x7D, /* 6 */
    0x07, /* 7 */
    0x7F, /* 8 */
    0x6F  /* 9 */
};

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 120; j++);
    }
}

void display_digit(unsigned char val) {
    if (val <= 9) {
        SEVEN_SEG_PORT = seg_lookup[val];
    } else {
        SEVEN_SEG_PORT = 0x00;
    }
}

unsigned char keypad_scan(void) {
    unsigned char row, col;
    unsigned char row_mask[4] = {0xFE, 0xFD, 0xFB, 0xF7}; /* Active LOW on P2.0-P2.3 */

    for (row = 0; row < 4; row++) {
        KEYPAD_PORT = row_mask[row] | 0xF0; /* High nibble input (pull-up) */
        
        col = (KEYPAD_PORT >> 4) & 0x0F;
        if (col != 0x0F) {
            delay_ms(20); /* Debounce */
            col = (KEYPAD_PORT >> 4) & 0x0F;
            if (col != 0x0F) {
                if (col == 0x0E) { /* Column 0 */
                    if (row == 0) return 1;
                    if (row == 1) return 4;
                    if (row == 2) return 7;
                    if (row == 3) return 0xFF; /* * key */
                } else if (col == 0x0D) { /* Column 1 */
                    if (row == 0) return 2;
                    if (row == 1) return 5;
                    if (row == 2) return 8;
                    if (row == 3) return 0;    /* 0 key */
                } else if (col == 0x0B) { /* Column 2 */
                    if (row == 0) return 3;
                    if (row == 1) return 6;
                    if (row == 2) return 9;
                    if (row == 3) return 0xFE; /* # key */
                }
            }
        }
    }
    return 0xFF; /* No key pressed */
}

void running_led(void) {
    LED_PORT = 0x01; delay_ms(150);
    LED_PORT = 0x02; delay_ms(150);
    LED_PORT = 0x04; delay_ms(150);
    LED_PORT = 0x08; delay_ms(150);
}

void alternate_led(void) {
    LED_PORT = 0x0A; delay_ms(200);
    LED_PORT = 0x05; delay_ms(200);
}

void blink_all(void) {
    LED_PORT = 0x0F; delay_ms(200);
    LED_PORT = 0x00; delay_ms(200);
}

void main(void) {
    unsigned char key = 0xFF;
    unsigned char active_cmd = 0;
    unsigned char cnt = 0;

    SEVEN_SEG_PORT = 0x00;
    LED_PORT = 0x00;

    while (1) {
        key = keypad_scan();
        if (key != 0xFF) {
            active_cmd = key;
            display_digit(key);
            /* Wait for key release */
            while (keypad_scan() != 0xFF);
        }

        /* Execute mapped action */
        switch (active_cmd) {
            case 1: LED_PORT = 0x01; break; /* LED1 ON */
            case 2: LED_PORT = 0x02; break; /* LED2 ON */
            case 3: LED_PORT = 0x04; break; /* LED3 ON */
            case 4: LED_PORT = 0x08; break; /* LED4 ON */
            case 5: running_led(); break;   /* Running pattern */
            case 6: alternate_led(); break; /* Alternating pattern */
            case 7:                         /* Binary counter */
                LED_PORT = cnt & 0x0F;
                delay_ms(250);
                cnt = (cnt + 1) % 16;
                break;
            case 8: blink_all(); break;     /* All LEDs blink */
            case 9: LED_PORT = 0x00; break; /* All OFF */
            case 0:                         /* Reset System */
                LED_PORT = 0x00;
                SEVEN_SEG_PORT = seg_lookup[0];
                active_cmd = 0xFF;
                break;
            default:
                break;
        }
    }
}
