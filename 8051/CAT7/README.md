# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 7  

**DATE:** 24/08/2026  

**NAME OF EXP:** 16x2 LCD Driver Development and Dynamic Display Control  

**HARDWARE SETUP / PLATFORM:** AT89S52 Microcontroller Development Board + 16x2 Character LCD (HD44780 Controller) + 10kΩ Contrast Trimpot + 4x4 Matrix Keypad + Keil µVision C51  

---

## TASK 7A : 4-Bit Parallel LCD Driver Implementation

### 1. Circuit Diagram

The circuit interfaces an alphanumeric 16x2 HD44780 LCD module in 4-bit bus mode to minimize pin consumption on Port 2.

- **Microcontroller:** AT89S52
- **Data Lines:** `D4`-`D7` connected to `P2.4`-`P2.7`
- **Register Select (RS):** `P2.0` (0 = Command, 1 = Data)
- **Read/Write (RW):** `P2.1` (Tied to GND or driven LOW for Write)
- **Enable (EN):** `P2.2` (Falling edge latches data)
- **Contrast Pin (V0):** Connected to wiper of 10 kΩ potentiometer between +5V and GND
- **4x4 Keypad:** Connected to Port 1 (`P1.0`-`P1.7`) for interactive controls

![Circuit Diagram](circuit.png)

### 2. HD44780 Command Table (4-Bit Mode)

| Command Code | Hex | Function Description |
|---|---|---|
| `0010 1000` | `0x28` | Function Set: 4-bit bus, 2 display lines, 5x8 dot matrix |
| `0000 1100` | `0x0C` | Display Control: Display ON, Cursor OFF, Blinking OFF |
| `0000 0110` | `0x06` | Entry Mode Set: Increment DDRAM address automatically |
| `0000 0001` | `0x01` | Clear Display: Clears DDRAM and returns cursor home |
| `1000 0000 + col` | `0x80 + col` | Set DDRAM Address: Line 1 (Columns 0 to 15) |
| `1100 0000 + col` | `0xC0 + col` | Set DDRAM Address: Line 2 (Columns 0 to 15) |

---

## TASK 7B & 7C : Cursor Positioning & Keypad Character Movement

### 1. Core Logic / Pseudocode / Code Base

**Working Principle:**

In 4-bit mode, each 8-bit byte is transmitted as two consecutive 4-bit nibbles (higher nibble first, then lower nibble) accompanied by high-to-low pulses on the `EN` line.

For the interactive navigation task:
- Key `2` increments row upward (`cur_row = 0`).
- Key `8` moves row downward (`cur_row = 1`).
- Key `4` moves column leftward (`cur_col--`).
- Key `6` moves column rightward (`cur_col++`).
The previous cell is cleared with `' '` and the character `'A'` is redrawn at `lcd_goto(cur_row, cur_col)`.

**Code Base (`main.c`):**
Implemented with modular low-level drivers: `lcd_init()`, `lcd_cmd()`, `lcd_data()`, `lcd_goto()`, `lcd_puts()`, and `lcd_print_number()`.

### 3. Inference

The 4-bit driver halved the required I/O lines from 8 to 4 while maintaining full command functionality. Cursor address relocation was verified across both rows, and character navigation mapped seamlessly to directional keypad inputs.
