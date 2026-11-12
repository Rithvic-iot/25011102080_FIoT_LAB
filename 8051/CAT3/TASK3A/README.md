# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 3  

**DATE:** 27/07/2026  

**NAME OF EXP:** Timer-Based LED Pattern Generator and Button Interrupt Controller / Switch Polling  

**HARDWARE SETUP / PLATFORM:** AT89S52 MCU + Push Button (P3.2) + 10kΩ Resistor + 4 LEDs + Keil µVision C51  

---

## TASK 3A : Switch Polling with Software Debouncing

### 1. Circuit Diagram

A tactile push button is connected to P3.2 with an external 10kΩ pull-up resistor to +5V (Active LOW). Four indicator LEDs are connected to Port 1 (P1.0-P1.3).

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**
Mechanical buttons physically bounce when pressed. A software delay of 25ms filters out chatter before accepting the button state transition.

**Pseudocode:**
1. Detect P3.2 == 0.
2. Wait 25ms and confirm P3.2 is still 0.
3. Cycle LED mode and wait for button release.

**Code Base (`main.c`):**
```c
#include <reg51.h>

sbit BUTTON = P3^2;

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 120; j++);
    }
}

unsigned char mode = 0;

void main(void) {
    BUTTON = 1;
    P1 = 0x00;
    while (1) {
        if (BUTTON == 0) {
            delay_ms(25);
            if (BUTTON == 0) {
                mode = (mode + 1) % 4;
                while (BUTTON == 0);
                delay_ms(25);
            }
        }
        switch (mode) {
            case 0: P1 = 0x01; delay_ms(200); P1 = 0x02; delay_ms(200); break;
            case 1: P1 = 0x0F; delay_ms(250); P1 = 0x00; delay_ms(250); break;
            case 2: P1 = 0x55; delay_ms(300); P1 = 0xAA; delay_ms(300); break;
            case 3: P1 = 0x00; break;
        }
    }
}

```

### 3. Inference

Software debouncing completely suppressed switch bouncing glitches, ensuring exactly one mode increment per button press.
