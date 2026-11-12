# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 5  

**DATE:** 10/08/2026  

**NAME OF EXP:** Hardware Timer and Interrupt-Based Timing for LED Fading, Pulse Generation, and Stepper Motor Control  

**HARDWARE SETUP / PLATFORM:** AT89S52 MCU + 28BYJ-48 Stepper Motor + ULN2003 Driver + Keil µVision C51  

---

## TASK 5C : Stepper Motor Commutation & Speed Control

### 1. Circuit Diagram

A 28BYJ-48 unipolar stepper motor is connected to Port 2 (P2.0-P2.3) through a ULN2003 Darlington driver powered by external +5V.

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**
A 4-step sequence (0x08, 0x04, 0x02, 0x01) energizes stator coils in succession. Speed is controlled by altering the stepping delay.

**Pseudocode:**
1. Output step sequence byte to P2.
2. Advance step index.
3. Wait step delay interval.

**Code Base (`main.c`):**
```c
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

```

### 3. Inference

The stepper motor rotated smoothly in both forward and reverse directions across multiple speed presets.
