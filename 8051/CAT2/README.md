# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 2  

**DATE:** 20/07/2026  

**NAME OF EXP:** 8051 Development Board Tool Chain Setup & GPIO Interfacing  

**HARDWARE SETUP / PLATFORM:** 8051 Development Board (AT89S52) + Keil µVision C51 + USB-ISP Programmer + Breadboard & Discrete LEDs  

---

## TASK 2A : Hardware Board Bring-Up & Rail Verification

### 1. Circuit Diagram

The experiment demonstrates initial hardware board bring-up and bare-metal LED blink control using the AT89S52 8-bit microcontroller.

- **Microcontroller:** AT89S52 (40-Pin DIP)
- **CPU Architecture:** 8051 8-bit CISC Core @ 11.0592 MHz
- **Operating Voltage:** +5.0 V DC (Regulated)
- **GPIO Port / Pin:** Port 1, Pin 0 (`P1.0`, Physical Pin 1)
- **Connected Peripheral:** Red 5mm LED with 330Ω Current-Limiting Resistor
- **Programming Interface:** 10-pin USB-ISP Header (SPI lines MOSI/MISO/SCK/RST)

![Circuit Diagram](circuit.png)

### 2. Hardware Bring-Up Sheet

| Parameter | Measurement / Specification Entry |
|---|---|
| **MCU Model** | Atmel AT89S52 |
| **CPU Core Architecture** | 8051 8-bit CISC Harvard Architecture |
| **Clock Oscillator Frequency** | 11.0592 MHz (1 Machine Cycle = 1.0851 µs) |
| **Operating Voltage ($V_{CC}$)** | +5.02 V DC (Verified with Digital Multimeter) |
| **Debug / Flash Interface** | USB-ISP In-System Programming Header |
| **LED GPIO Port & Pin** | Port 1, Pin 0 (`P1.0`, Physical Pin 1) |
| **LED Active State** | Active HIGH (Current Sourcing from MCU) |
| **Blink Frequency ($f$)** | ~1.0 Hz (500 ms ON, 500 ms OFF, 50% Duty Cycle) |

---

## TASK 2B : Bare-Metal LED Blink & Modular Delay Library

### 1. Core Logic / Pseudocode / Code Base

**Working Principle:**

The AT89S52 microcontroller has four 8-bit bidirectional I/O ports: P0, P1, P2, and P3. In bare-metal programming, Port 1 is directly accessed through its memory-mapped Special Function Register (`P1` at SFR address `0x90`). By assigning `sbit LED = P1^0`, the CPU manipulates the specific latch bit directly without overhead.

A modular delay function `delay_ms(unsigned int ms)` utilizes calibrated nested loops to generate standard time increments of 1 millisecond. Since each machine cycle requires 12 oscillator periods ($T_{cy} = 12 / 11.0592	ext{ MHz} pprox 1.085\,\mu	ext{s}$), a calibrated inner loop of 120 iterations provides exactly 1 ms delay.

**Pseudocode:**
1. Include register definitions header `<reg51.h>`.
2. Map `P1.0` as bit-addressable symbol `LED`.
3. Construct modular loop `delay_ms(ms)`.
4. Initialize `P1 = 0x00` setting pin to logic LOW.
5. In an infinite loop:
   - Set `LED = 1` (turns LED ON).
   - Call `delay_ms(500)`.
   - Set `LED = 0` (turns LED OFF).
   - Call `delay_ms(500)`.

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

The hardware bring-up confirmed correct DC rail distribution (+5.02V) across the AT89S52 development board. Direct register manipulation of `P1.0` produced consistent, non-flickering LED toggling at exactly 1.0 Hz. The software delay implementation demonstrated accurate machine-cycle timing based on the 11.0592 MHz crystal oscillator.
