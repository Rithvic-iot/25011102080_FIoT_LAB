# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 4  

**DATE:** 03/08/2026  

**NAME OF EXP:** Human-Machine Interface using Matrix Keypad, LEDs, and Seven-Segment Display  

**HARDWARE SETUP / PLATFORM:** AT89S52 Microcontroller Board + 4x4 Matrix Keypad (Port 2) + Common Cathode 7-Segment Display (Port 0) + 4 Mode LEDs (Port 1) + Keil µVision C51  

---

## TASK 4 : Keypad Scanning, 7-Segment Feedback & LED Actuation

### 1. Circuit Diagram

This experiment builds a complete user interface: the user presses a key on the 4x4 matrix keypad, the pressed number appears on the 7-segment display, and a matching LED function runs on Port 1.

- **Microcontroller:** AT89S52
- **Keypad Matrix:** Port 2 (Rows on `P2.0`-`P2.3`, Columns on `P2.4`-`P2.7`)
- **7-Segment Display:** Common Cathode connected to Port 0 with an external 10kΩ pull-up resistor pack
- **LED Indicators:** Port 1 Pins `P1.0` through `P1.3`

![Circuit Diagram](circuit.png)

### 2. Functional Requirements & Key Mapping

| Key Pressed | 7-Segment Display | LED Action Triggered |
|:---:|:---:|---|
| **1** | `1` | LED 1 ON (`P1.0 = 1`, others OFF) |
| **2** | `2` | LED 2 ON (`P1.1 = 1`, others OFF) |
| **3** | `3` | LED 3 ON (`P1.2 = 1`, others OFF) |
| **4** | `4` | LED 4 ON (`P1.3 = 1`, others OFF) |
| **5** | `5` | Running LED pattern ($0001_2 	o 0010_2 	o 0100_2 	o 1000_2$) |
| **6** | `6` | Alternate LEDs flashing ($1010_2 \leftrightarrow 0101_2$) |
| **7** | `7` | 4-bit binary counter (0 to 15) |
| **8** | `8` | All LEDs flashing synchronously |
| **9** | `9` | All LEDs turned OFF |
| **0** | `0` | Reset System (Display shows 0, LEDs turn off) |

### 3. Core Logic & Working Principle

1. **Keypad Scanning:** We ground one row at a time (`P2.0` to `P2.3`) by writing logic `0` to that row, then read the column pins (`P2.4` to `P2.7`). If a button is pressed, the corresponding column reads logic `0`.
2. **7-Segment Display:** Port 0 is open-drain, so it needs a 10kΩ resistor pack tied to +5V. We use a lookup table containing the 7-segment segment patterns for digits 0 to 9 (`0x3F` for '0', `0x06` for '1', `0x5B` for '2', etc.).
3. **LED Action:** A switch statement executes the mapped pattern on Port 1 based on the pressed key.

### 4. Inference

The 4x4 keypad matrix scanned keys cleanly without ghosting. The 7-segment display gave instant visual feedback of the selected number, and all ten mapped LED functions executed reliably.
