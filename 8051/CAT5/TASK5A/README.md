# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 5  

**DATE:** 10/08/2026  

**NAME OF EXP:** Hardware Timer and Interrupt-Based Timing for LED Fading, Pulse Generation, and Stepper Motor Control  

**HARDWARE SETUP / PLATFORM:** AT89S52 MCU @ 11.0592 MHz + Timer 0 + Oscilloscope + Keil µVision C51  

---

## TASK 5A : Hardware Timer 0 Interrupt 1ms Time Base

### 1. Circuit Diagram

Timer 0 is configured in 16-bit Mode 1 with preload values TH0 = 0xFC and TL0 = 0x66 to generate an exact 1 ms periodic interrupt at 11.0592 MHz.

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**
Instead of CPU-blocking delay loops, hardware interrupts provide an accurate background time tick counter for concurrent system tasks.

**Pseudocode:**
1. Set TMOD = 0x01.
2. Load TH0 = 0xFC, TL0 = 0x66.
3. Enable ET0 and EA.
4. In ISR, reload timer and increment tick counter.

**Code Base (`main.c`):**
```c
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

```

### 3. Inference

Timer 0 produced an accurate 1.00 ms periodic interrupt verified by oscilloscope toggling on pin P1.1.
