#include <reg51.h>

sbit BUTTON = P3^2;

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 120; j++);
    }
}

unsigned char mode = 0;

void main(void) {
    BUTTON = 1;
    P1 = 0x00;
    while (1) {
        if (BUTTON == 0) {
            delay_ms(25);
            if (BUTTON == 0) {
                mode = (mode + 1) % 4;
                while (BUTTON == 0);
                delay_ms(25);
            }
        }
        switch (mode) {
            case 0: P1 = 0x01; delay_ms(200); P1 = 0x02; delay_ms(200); break;
            case 1: P1 = 0x0F; delay_ms(250); P1 = 0x00; delay_ms(250); break;
            case 2: P1 = 0x55; delay_ms(300); P1 = 0xAA; delay_ms(300); break;
            case 3: P1 = 0x00; break;
        }
    }
}
