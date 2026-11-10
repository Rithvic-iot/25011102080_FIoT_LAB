# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 3  

**DATE:** 27/07/2026  

**NAME OF EXP:** Timer-Based LED Pattern Generator and Button Interrupt Controller / Switch Polling  

**HARDWARE SETUP / PLATFORM:** AT89S52 Microcontroller Development Board + 4x Discrete LEDs + 1x Tactile Push-Button + 10kΩ Pull-Up Resistor + Keil µVision C51  

---

## TASK 3A : Switch Polling with Hardware & Software Debouncing

### 1. Circuit Diagram

The circuit interfaces four output LEDs on Port 1 and a tactile push-button switch on Port 3.

- **Microcontroller:** AT89S52
- **Switch Input Pin:** Port 3, Pin 2 (`P3.2` / `INT0`)
- **Switch Configuration:** Active LOW with 10 kΩ pull-up resistor to +5V
- **LED Output Pins:** `P1.0` (LED1), `P1.1` (LED2), `P1.2` (LED3), `P1.3` (LED4)
- **Current Limiting:** 4x 330 Ω Resistors in series with each LED anode

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**

Mechanical switches exhibit mechanical contact bounce lasting 5 ms to 20 ms during transition. Without debouncing, a single button press generates multiple spurious state transitions. Software debouncing samples the pin, inserts a 25 ms settling delay, and re-verifies the stable state before registering a state advance.

Each valid button press cycles through a 4-state finite state machine:
- **Mode 1 (Running LED):** LEDs illuminate sequentially ($0001_2 	o 0010_2 	o 0100_2 	o 1000_2$).
- **Mode 2 (Binary Counter):** 4-bit binary progression from $0000_2$ (0) to $1111_2$ (15).
- **Mode 3 (Alternating Pattern):** Alternate pairs toggle ($1010_2 \leftrightarrow 0101_2$).
- **Mode 4 (All LED Flash):** Synchronous flashing of all 4 LEDs ($1111_2 \leftrightarrow 0000_2$).

**Pseudocode:**
1. Configure `P3.2 = 1` for input mode.
2. Initialize `P1 = 0x00` (all LEDs OFF).
3. Poll `P3.2`. If logic LOW:
   - Delay 25 ms.
   - If still LOW, increment `current_mode` (wrap from 4 to 1).
   - Wait until `P3.2 == 1` (button release) and delay 25 ms.
4. Execute LED pattern for active `current_mode`.

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

unsigned char current_mode = 0;
unsigned char counter_val = 0;

void main(void) {
    BUTTON = 1;
    P1 = 0x00;
    while (1) {
        if (BUTTON == 0) {
            delay_ms(25);
            if (BUTTON == 0) {
                current_mode++;
                if (current_mode > 4) current_mode = 1;
                counter_val = 0;
                while (BUTTON == 0);
                delay_ms(25);
            }
        }
        switch (current_mode) {
            case 1: /* Running LED */
                P1 = 0x01; delay_ms(200);
                P1 = 0x02; delay_ms(200);
                P1 = 0x04; delay_ms(200);
                P1 = 0x08; delay_ms(200);
                break;
            case 2: /* Binary Counter */
                P1 = counter_val & 0x0F;
                delay_ms(300);
                counter_val = (counter_val + 1) % 16;
                break;
            case 3: /* Alternating */
                P1 = 0x0A; delay_ms(250);
                P1 = 0x05; delay_ms(250);
                break;
            case 4: /* All Flash */
                P1 = 0x0F; delay_ms(250);
                P1 = 0x00; delay_ms(250);
                break;
        }
    }
}
```

### 3. Inference

The software debounce algorithm successfully suppressed mechanical contact chatter, guaranteeing exactly one mode transition per physical actuation. The finite state machine responded reliably across all four pattern sequences.
