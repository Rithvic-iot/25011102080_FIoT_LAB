#include <reg51.h>

sbit PWM1 = P1^0;
sbit PWM2 = P1^1;
volatile unsigned char cnt = 0;

void timer0_isr(void) interrupt 1 {
    TH0 = 0xFC;
    TL0 = 0x66;
    cnt = (cnt + 1) % 10;
    PWM1 = (cnt < 3) ? 1 : 0; /* 30% */
    PWM2 = (cnt < 7) ? 1 : 0; /* 70% */
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
