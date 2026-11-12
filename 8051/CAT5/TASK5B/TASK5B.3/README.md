# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 5  

**DATE:** 10/08/2026  

**NAME OF EXP:** Hardware Timer and Interrupt-Based Timing for LED Fading, Pulse Generation, and Stepper Motor Control  

**HARDWARE SETUP / PLATFORM:** AT89S52 MCU + Timer 0 + Dual LEDs on P1.0 and P1.1 + Keil µVision C51  

---

## TASK 5B.3 : Multi-Channel Software PWM Pulse Generation

### 1. Circuit Diagram

Two independent PWM signals (30% duty on P1.0, 70% duty on P1.1) are generated simultaneously using a single hardware timer.

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**
The 1 ms timer ISR compares the shared cycle counter against multiple independent duty cycle registers.

**Pseudocode:**
1. Increment cycle counter.
2. Set P1.0 based on Duty1.
3. Set P1.1 based on Duty2.

**Code Base (`main.c`):**
```c
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

```

### 3. Inference

Both PWM channels operated concurrently with precise timing and independent duty ratios.
