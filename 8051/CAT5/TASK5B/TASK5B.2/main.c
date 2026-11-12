#include <reg51.h>

sbit PWM_PIN = P1^0;
volatile unsigned char pwm_cnt = 0;
volatile unsigned char duty = 0;
volatile int dir = 1;
volatile unsigned int tick_cnt = 0;

void timer0_isr(void) interrupt 1 {
    TH0 = 0xFC;
    TL0 = 0x66;
    pwm_cnt = (pwm_cnt + 1) % 10;
    PWM_PIN = (pwm_cnt < duty) ? 1 : 0;
    tick_cnt++;
    if (tick_cnt >= 50) {
        tick_cnt = 0;
        duty += dir;
        if (duty >= 10) dir = -1;
        if (duty <= 0) dir = 1;
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
