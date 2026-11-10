# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 9  

**DATE:** 28/09/2026  

**NAME OF EXP:** STM32 UART Command Controlled LED  

**HARDWARE SETUP / PLATFORM:** STM32 Blue Pill Board (STM32F103C8T6 ARM Cortex-M3) + USB-to-UART Serial Converter + PC with PuTTY Serial Terminal + Keil MDK-ARM + STM32CubeMX  

---

## TASK 9A : Basic UART Communication & Line Termination Analysis

### 1. Circuit Diagram

The circuit interfaces the STM32 USART1 peripheral to a host workstation using an asynchronous USB-to-TTL serial transceiver.

- **Microcontroller:** STM32F103C8T6 (Blue Pill)
- **USART Peripheral:** `USART1` (Asynchronous Mode)
- **TX Pin:** `PA9` connected to USB-TTL `RXD`
- **RX Pin:** `PA10` connected to USB-TTL `TXD`
- **Common Ground:** MCU `GND` tied to USB-TTL `GND`
- **On-board User LED:** Connected to `PC13` (Active LOW)

![Circuit Diagram](circuit.png)

### 2. Line Termination Investigation (`` vs `
`)

| Test String | Sequence Transmitted | Observed Behavior in PuTTY Terminal |
|---|---|---|
| **Test 1** | `"HELLO
"` | Prints `HELLO`, moves cursor to start of next line (Standard CR+LF). |
| **Test 2** | `"HELLO"` | Prints `HELLO`, moves cursor to line start without linefeed; overwrites on next write. |
| **Test 3** | `"HELLO
"` | Moves cursor down one row, maintaining previous column index (staircase artifact). |
| **Test 4** | `"HELLO
WORLD
"` | Displays two properly aligned distinct rows: `HELLO` followed by `WORLD`. |

---

## TASK 9B : Text Command Parser Application Logic

### 1. Core Logic & Supported Commands

The firmware receives ASCII characters into a 64-byte accumulation buffer until a newline or carriage return delimiter is detected. The string is then evaluated against a command dictionary:

| Command Sent | Action Executed by STM32 | Serial Confirmation Returned |
|---|---|---|
| `LED ON` | Clears `PC13` to logic LOW | `OK: LED turned ON
` |
| `LED OFF` | Sets `PC13` to logic HIGH | `OK: LED turned OFF
` |
| `LED TOGGLE` | Inverts `PC13` logic state | `OK: LED toggled
` |
| `STATUS` | Reads current `PC13` state | `STATUS: LED is ON
` or `OFF` |

### 2. Code Base

Implemented in `Core/Src/main.c` utilizing STM32 HAL UART polling functions (`HAL_UART_Transmit`, `HAL_UART_Receive`).

### 3. Inference

The experiment demonstrated structured serial packet parsing on ARM Cortex-M microcontrollers. The character parser reliably identified string commands, filtered escape characters, and accurately actuated the hardware LED.
