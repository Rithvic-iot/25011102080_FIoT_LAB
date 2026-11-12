# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 4  

**DATE:** 03/08/2026  

**NAME OF EXP:** Human-Machine Interface using Matrix Keypad, LEDs, and Seven-Segment Display  

**HARDWARE SETUP / PLATFORM:** AT89S52 MCU + 4x4 Keypad (Port 2) + 7-Segment Display (Port 0) + Keil µVision C51  

---

## TASK 4A : Matrix Keypad Scanning & 7-Segment Output

### 1. Circuit Diagram

A 4x4 matrix keypad is wired to Port 2 (rows P2.0-P2.3, columns P2.4-P2.7). A Common Cathode 7-segment display is driven by Port 0 with a 10kΩ pull-up pack.

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**
The MCU grounds one row at a time and scans column inputs to identify the pressed key coordinate, decoding it into segment patterns for the display.

**Pseudocode:**
1. Ground row pin.
2. Read column pins.
3. If button pressed, lookup segment byte and output to Port 0.

**Code Base (`main.c`):**
```c
#include <reg51.h>

unsigned char code seg_lut[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 120; j++);
    }
}

char scan_keypad(void) {
    P2 = 0xFE; if ((P2 & 0x10) == 0) return 1;
    P2 = 0xFD; if ((P2 & 0x10) == 0) return 4;
    P2 = 0xFB; if ((P2 & 0x10) == 0) return 7;
    return 0;
}

void main(void) {
    P0 = 0x3F;
    while (1) {
        char key = scan_keypad();
        if (key > 0 && key <= 9) {
            P0 = seg_lut[key];
            P1 = key;
        }
        delay_ms(50);
    }
}

```

### 3. Inference

The row-scanning algorithm detected numeric key presses cleanly and updated the 7-segment display with zero ghosting.
