#include <reg51.h>

sbit TEST_PIN = P1^1;
volatile unsigned int ms_ticks = 0;

void timer0_isr(void) interrupt 1 {
    TH0 = 0xFC;
    TL0 = 0x66;
    ms_ticks++;
    if (ms_ticks % 500 == 0) {
        TEST_PIN = !TEST_PIN;
    }
}

void main(void) {
    TMOD = 0x01;
    TH0 = 0xFC;
    TL0 = 0x66;
    ET0 = 1;
    EA = 1;
    TR0 = 1;
    while (1);
}
