#include <reg51.h>

sbit PWM_PIN = P1^0;
volatile unsigned char pwm_counter = 0;
volatile unsigned char duty = 5; /* 50% */

void timer0_isr(void) interrupt 1 {
    TH0 = 0xFC;
    TL0 = 0x66;
    pwm_counter = (pwm_counter + 1) % 10;
    PWM_PIN = (pwm_counter < duty) ? 1 : 0;
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
