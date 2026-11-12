# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 7  

**DATE:** 24/08/2026  

**NAME OF EXP:** 16x2 LCD Driver Development and Dynamic Display Control  

**HARDWARE SETUP / PLATFORM:** AT89S52 MCU + 16x2 HD44780 LCD Display + Keil µVision C51  

---

## TASK 7B : Alphanumeric String Display & Cursor Positioning

### 1. Circuit Diagram

Alphanumeric text strings are printed across both lines of the LCD using DDRAM address mapping.

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**
Line 1 base address is 0x80 and Line 2 base address is 0xC0. The driver positions the cursor before printing character streams.

**Pseudocode:**
1. Position cursor with command (0x80 or 0xC0) + column.
2. Loop through string transmitting characters to data register.

**Code Base (`main.c`):**
```c
#include <reg51.h>

sbit RS = P2^0;
sbit RW = P2^1;
sbit E  = P2^2;

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++) for (j = 0; j < 120; j++);
}

void lcd_pulse(void) { E = 1; delay_ms(2); E = 0; delay_ms(2); }

void lcd_cmd(unsigned char cmd) {
    RS = 0; RW = 0;
    P2 = (P2 & 0x0F) | (cmd & 0xF0); lcd_pulse();
    P2 = (P2 & 0x0F) | ((cmd << 4) & 0xF0); lcd_pulse();
}

void lcd_data(unsigned char d) {
    RS = 1; RW = 0;
    P2 = (P2 & 0x0F) | (d & 0xF0); lcd_pulse();
    P2 = (P2 & 0x0F) | ((d << 4) & 0xF0); lcd_pulse();
}

void lcd_init(void) {
    delay_ms(20);
    lcd_cmd(0x28); lcd_cmd(0x0C); lcd_cmd(0x06); lcd_cmd(0x01);
}

void lcd_print(char *s) { while (*s) lcd_data(*s++); }

void main(void) {
    lcd_init();
    lcd_cmd(0x80); lcd_print("Foundations IoT");
    lcd_cmd(0xC0); lcd_print("LCD Driver OK");
    while (1);
}

```

### 3. Inference

Custom strings were rendered clearly on both lines with accurate coordinate positioning.
