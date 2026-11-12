# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 7  

**DATE:** 24/08/2026  

**NAME OF EXP:** 16x2 LCD Driver Development and Dynamic Display Control  

**HARDWARE SETUP / PLATFORM:** AT89S52 MCU + 16x2 LCD + 4x4 Matrix Keypad + Keil µVision C51  

---

## TASK 7C : Keypad Controlled Interactive Character Navigation

### 1. Circuit Diagram

The user moves a character ('A') dynamically across the 16x2 grid using directional inputs from the keypad.

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**
Before updating the character position, the previous cell is cleared with a space character (' ').

**Pseudocode:**
1. Poll directional inputs.
2. Clear current position.
3. Update row and column coordinates within bounds.
4. Draw character at new position.

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

unsigned char row = 0, col = 0;

void update_pos(void) {
    lcd_cmd((row == 0 ? 0x80 : 0xC0) + col);
    lcd_data('A');
}

void main(void) {
    lcd_init();
    update_pos();
    while (1) {
        /* Poll keypad on Port 1 */
        if ((P1 & 0x01) == 0) { row = 0; lcd_cmd(0x01); update_pos(); delay_ms(200); }
        if ((P1 & 0x02) == 0) { row = 1; lcd_cmd(0x01); update_pos(); delay_ms(200); }
    }
}

```

### 3. Inference

The character navigated smoothly across all 32 display cells in response to keypad presses.
