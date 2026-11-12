#include <reg51.h>

unsigned char code seg_lut[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 120; j++);
    }
}

char scan_keypad(void) {
    P2 = 0xFE; if ((P2 & 0x10) == 0) return 1;
    P2 = 0xFD; if ((P2 & 0x10) == 0) return 4;
    P2 = 0xFB; if ((P2 & 0x10) == 0) return 7;
    return 0;
}

void main(void) {
    P0 = 0x3F;
    while (1) {
        char key = scan_keypad();
        if (key > 0 && key <= 9) {
            P0 = seg_lut[key];
            P1 = key;
        }
        delay_ms(50);
    }
}
