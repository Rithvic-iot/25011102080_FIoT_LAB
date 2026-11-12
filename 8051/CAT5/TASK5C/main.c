#include <reg51.h>

unsigned char code step_seq[4] = {0x08, 0x04, 0x02, 0x01};

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 120; j++);
    }
}

void main(void) {
    unsigned char i = 0;
    while (1) {
        P2 = (P2 & 0xF0) | step_seq[i];
        i = (i + 1) % 4;
        delay_ms(25);
    }
}
