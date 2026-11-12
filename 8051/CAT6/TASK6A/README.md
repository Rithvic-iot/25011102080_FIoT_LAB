# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 6  

**DATE:** 17/08/2026  

**NAME OF EXP:** UART Driver and Serial Debugging  

**HARDWARE SETUP / PLATFORM:** AT89S52 MCU + CP2102 USB-to-TTL Converter + PC PuTTY Terminal + Keil µVision C51  

---

## TASK 6A : UART Driver 9600-8-N-1 String Transmission

### 1. Circuit Diagram

Pins P3.1 (TXD) and P3.0 (RXD) connect to USB-TTL RXD and TXD with common ground. Serial parameters: 9600 Baud, 8 Data Bits, 1 Stop Bit, No Parity.

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**
Timer 1 in Mode 2 (8-bit auto-reload) with TH1 = 0xFD produces 9600 baud at 11.0592 MHz with 0% error.

**Pseudocode:**
1. Set TMOD = 0x20, TH1 = 0xFD, SCON = 0x50, TR1 = 1.
2. Write character to SBUF and wait for TI == 1.

**Code Base (`main.c`):**
```c
#include <reg51.h>

void uart_init(void) {
    TMOD = 0x20;
    TH1 = 0xFD;
    SCON = 0x50;
    TR1 = 1;
}

void uart_tx(char c) {
    SBUF = c;
    while (!TI);
    TI = 0;
}

void uart_send_str(char *s) {
    while (*s) uart_tx(*s++);
}

void main(void) {
    uart_init();
    uart_send_str("Hello from 8051 UART!
");
    while (1);
}

```

### 3. Inference

Diagnostic messages were transmitted reliably and printed legibly on the PC PuTTY serial terminal.
