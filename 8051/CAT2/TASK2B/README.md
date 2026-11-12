# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 2  

**DATE:** 20/07/2026  

**NAME OF EXP:** 8051 Development Board Tool Chain Setup & GPIO Interfacing  

**HARDWARE SETUP / PLATFORM:** 8051 Microcontroller (AT89S52) + Red LED + 330Ω Resistor + Keil µVision C51  

---

## TASK 2B : Bare-Metal LED Blink & Modular Delay Function

### 1. Circuit Diagram

The circuit connects Port 1 Pin 0 (P1.0) of the AT89S52 microcontroller to an external red LED through a 330Ω current-limiting resistor to ground.

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**
The microcontroller toggles pin P1.0 between logic 1 (+5V) and logic 0 (0V). Calibrated nested loops generate a software delay of ~500ms between transitions.

**Pseudocode:**
1. Define P1.0 as LED.
2. In an infinite loop, write LED = 1, delay 500ms, write LED = 0, delay 500ms.

**Code Base (`main.c`):**
```c
#include <reg51.h>

sbit LED = P1^0;

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 120; j++);
    }
}

void main(void) {
    P1 = 0x00;
    while (1) {
        LED = 1;
        delay_ms(500);
        LED = 0;
        delay_ms(500);
    }
}

```

### 3. Inference

The LED blinked continuously at ~1 Hz (500 ms ON, 500 ms OFF), verifying GPIO control and delay generation on the 8051.
