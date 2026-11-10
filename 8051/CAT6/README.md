# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 6  

**DATE:** 17/08/2026  

**NAME OF EXP:** UART Driver and Serial Debugging  

**HARDWARE SETUP / PLATFORM:** AT89S52 Microcontroller Development Board + USB-to-TTL Serial Converter (CP2102/CH340) + PC PuTTY Terminal Emulator + Keil µVision C51  

---

## TASK 6A : UART Driver Initialization & String Transmission

### 1. Circuit Diagram

The circuit connects the hardware UART pins of the AT89S52 to a PC via an asynchronous USB-to-TTL serial converter.

- **Microcontroller:** AT89S52
- **TXD Pin:** Port 3, Pin 1 (`P3.1`, Pin 11) connected to USB-TTL `RXD`
- **RXD Pin:** Port 3, Pin 0 (`P3.0`, Pin 10) connected to USB-TTL `TXD`
- **Common Ground:** MCU `GND` connected to USB-TTL `GND`
- **Baud Rate Timing Peripheral:** Timer 1 in Mode 2 (8-bit Auto-Reload)

![Circuit Diagram](circuit.png)

### 2. Baud Rate Derivation (9600 Baud)

For the standard 8051 architecture with crystal $f_{osc} = 11.0592	ext{ MHz}$ and $SMOD = 0$:

$$	ext{UART Baud Rate} = rac{2^{SMOD}}{32} 	imes rac{f_{osc}}{12 	imes (256 - TH1)}$$

$$9600 = rac{1}{32} 	imes rac{11059200}{12 	imes (256 - TH1)} = rac{28800}{256 - TH1}$$

$$256 - TH1 = rac{28800}{9600} = 3 \implies TH1 = 256 - 3 = 253 = 	ext{0xFD}$$

Reloading `TH1 = 0xFD` into Timer 1 achieves exactly 9600 baud with **0.00% clock error**.

---

## TASK 6B : Interactive PuTTY Terminal Echo & RX Ring Buffer

### 1. Core Logic / Pseudocode / Code Base

**Working Principle:**

The UART receiver operates via interrupt `vector 4`. When a character arrives, the hardware sets the `RI` flag, triggering `serial_ISR()`. The ISR fetches the character from `SBUF`, clears `RI`, and enqueues the byte into a circular ring buffer (`rx_buffer`). The foreground loop dequeues received characters and re-transmits them to the terminal (`uart_send_char()`).

**Pseudocode:**
1. Configure `TMOD` for Timer 1 Mode 2 (8-bit auto-reload).
2. Set `TH1 = 0xFD`, `TL1 = 0xFD`, start Timer 1 (`TR1 = 1`).
3. Set `SCON = 0x50` (Mode 1, 8-bit UART, Receiver Enabled `REN = 1`).
4. Enable interrupts (`ES = 1`, `EA = 1`).
5. Transmit formatted banner `"Hello from 8051"`.
6. Continuously pop characters from ring buffer and echo back to terminal.

**Code Base (`main.c`):**
Implemented with modular driver functions: `uart_init()`, `uart_send_char()`, `uart_send_string()`, and `serial_ISR()`.

### 3. Inference

The UART driver established reliable bidirectional communication with the PuTTY serial console at 9600-8-N-1. The interrupt-driven ring buffer prevented character loss during bursts, validating the mathematical precision of the 8051 baud rate generator.
