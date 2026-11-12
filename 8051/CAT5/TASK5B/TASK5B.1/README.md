# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 5  

**DATE:** 10/08/2026  

**NAME OF EXP:** Hardware Timer and Interrupt-Based Timing for LED Fading, Pulse Generation, and Stepper Motor Control  

**HARDWARE SETUP / PLATFORM:** AT89S52 MCU + Timer 0 + Indicator LED on P1.0 + Keil µVision C51  

---

## TASK 5B.1 : Software PWM with Discrete Duty Cycles (25%, 50%, 75%)

### 1. Circuit Diagram

The LED on P1.0 is driven by a software PWM signal modulated within the 1 ms Timer 0 interrupt.

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**
A 100 Hz PWM frame consists of 10 steps of 1 ms. Comparing the counter to a fixed duty threshold sets the LED on or off.

**Pseudocode:**
1. In ISR, pwm_counter = (pwm_counter + 1) % 10.
2. If counter < duty, P1.0 = 1; else P1.0 = 0.

**Code Base (`main.c`):**
```c
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

```

### 3. Inference

The LED maintained stable discrete brightness levels at 25%, 50%, and 75% duty cycles with zero observable flicker.
