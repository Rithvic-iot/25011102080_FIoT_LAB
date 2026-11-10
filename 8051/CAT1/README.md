# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 1  

**DATE:** 13/07/2026  

**NAME OF EXP:** Commercial IoT Device Teardown and 8051 Toolchain Setup  

**HARDWARE SETUP / PLATFORM:** Commercial Wi-Fi Smart Plug (ESP8266) + AT89S52 Microcontroller Board + Keil µVision C51 + USB-ISP Programmer  

---

## TASK 1A : Commercial IoT Device Teardown

### 1. Circuit Diagram & Block Diagram

In this task, we carefully opened up a standard commercial Wi-Fi smart plug to understand the internal electronic building blocks of a real IoT product.

- **Main Wi-Fi Chip / MCU:** ESP8266 Wi-Fi SoC (handles wireless network and control logic)
- **Power Supply Section:** AC to DC power converter stepping down 230V AC mains to 5V DC and 3.3V DC
- **Actuator Section:** 10A / 250V AC Relay driven by a transistor to turn the connected appliance ON and OFF
- **Protection Diode:** 1N4148 flyback diode across the relay coil to stop inductive voltage spikes
- **User Interface:** Push button for manual ON/OFF toggling and Wi-Fi reset, plus LED indicators for power and Wi-Fi status

![Circuit Diagram](circuit.png)

### 2. Teardown Observations

1. **Power Domain Separation:** The board has a clear separation between the high-voltage AC mains section (230V) and the low-voltage DC section (3.3V/5V) with isolation slots cut into the PCB for safety.
2. **Relay Driver:** The microcontroller cannot drive the relay coil directly because it draws too much current, so an NPN transistor is used as a switch with a flyback diode for protection.
3. **Compact Antenna:** The Wi-Fi antenna is a meandered PCB trace antenna printed right on the edge of the board.

---

## TASK 1B : 8051 Toolchain Setup & Verification

### 1. Hardware Setup

- **Microcontroller:** Atmel AT89S52 (40-pin DIP)
- **Clock Source:** 11.0592 MHz crystal oscillator with two 33pF ceramic capacitors
- **Reset Circuit:** 10µF capacitor and 10kΩ resistor for power-on reset
- **Programmer:** USB-ISP connected to MOSI (P1.5), MISO (P1.6), SCK (P1.7), and RST

### 2. Core Logic & Working Principle

We installed and configured Keil µVision C51 for the AT89S52 target. To confirm our development setup works from end-to-end, we wrote a simple C program that toggles pin P1.0 at 1 Hz, compiled it to produce a `.hex` file, and flashed it to the chip.

**Pseudocode:**
1. Include `<reg51.h>` to access 8051 special function registers.
2. Define `TEST_PIN = P1^0` to control Port 1 Pin 0.
3. Write a delay function using nested loops for ~500ms intervals.
4. In an infinite loop, set `TEST_PIN = 1`, wait 500ms, set `TEST_PIN = 0`, and wait 500ms.

**Code Base (`main.c`):**
```c
#include <reg51.h>

sbit TEST_PIN = P1^0;

void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 120; j++);
    }
}

void main(void) {
    P1 = 0x00;
    while (1) {
        TEST_PIN = 1;
        delay_ms(500);
        TEST_PIN = 0;
        delay_ms(500);
    }
}
```

### 3. Inference

By opening and inspecting the commercial smart plug, we saw firsthand how the power, microcontroller, Wi-Fi, and relay subsystems fit together on a production PCB. We also verified that our Keil µVision C51 toolchain, startup code, and USB-ISP programmer work correctly by successfully flashing our first bare-metal test code to the AT89S52 board.
