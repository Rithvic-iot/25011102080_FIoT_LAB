# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 6  

**DATE:** 17/08/2026  

**NAME OF EXP:** UART Driver and Serial Debugging  

**HARDWARE SETUP / PLATFORM:** AT89S52 MCU + CP2102 USB-to-TTL Converter + PC PuTTY Terminal + Keil µVision C51  

---

## TASK 6B : Interactive PuTTY Terminal Echo & RX Ring Buffer

### 1. Circuit Diagram

The 8051 UART receiver interrupt (interrupt 4) listens for keystrokes typed in the terminal emulator.

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**
When a byte arrives, the ISR retrieves it from SBUF, clears RI, and transmits it back to SBUF so it echoes on screen.

**Pseudocode:**
1. In UART ISR, check if RI == 1.
2. Read byte = SBUF; clear RI = 0.
3. Retransmit byte to SBUF.

**Code Base (`main.c`):**
```c
#include <reg51.h>

void uart_init(void) {
    TMOD = 0x20;
    TH1 = 0xFD;
    SCON = 0x50;
    TR1 = 1;
    ES = 1;
    EA = 1;
}

void uart_isr(void) interrupt 4 {
    if (RI) {
        char c = SBUF;
        RI = 0;
        SBUF = c;
        while (!TI);
        TI = 0;
    }
}

void main(void) {
    uart_init();
    while (1);
}

```

### 3. Inference

Keystrokes echoed instantaneously on the PC terminal without dropped characters or transmission lag.
