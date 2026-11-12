# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 5  

**DATE:** 10/08/2026  

**NAME OF EXP:** Hardware Timer and Interrupt-Based Timing for LED Fading, Pulse Generation, and Stepper Motor Control  

**HARDWARE SETUP / PLATFORM:** AT89S52 MCU + Timer 0 + Indicator LED on P1.0 + Keil µVision C51  

---

## TASK 5B.2 : Software PWM Dynamic LED Fading (0% to 100% Breathing Effect)

### 1. Circuit Diagram

The LED on P1.0 is continuously modulated with a dynamically ramping duty cycle to create a smooth breathing effect.

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**
Every 50 ms, the duty cycle increments from 0 to 10 and then decrements back down to 0, varying the average forward current through the LED.

**Pseudocode:**
1. Modulate pin within 1ms ISR.
2. Periodically step duty cycle up and down between 0 and 100%.

**Code Base (`main.c`):**
```c
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

```

### 3. Inference

The LED faded smoothly between fully off and maximum brightness without blocking CPU execution.
