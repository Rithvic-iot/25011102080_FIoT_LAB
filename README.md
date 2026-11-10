# Foundations of Internet of Things (FIoT) – Laboratory Experiments

**Student Registration Number:** 25011102080  
**Repository Name:** 25011102080_FIoT_LAB  
**Course Code:** 25CS2741 – Fundamentals of Internet of Things + Lab  
**Department:** Computer Science & Engineering (IoT)  
**Institution:** Shiv Nadar University Chennai  

---

## 1. Overview

This repository contains the complete experimental laboratory coursework for the **Fundamentals of Internet of Things + Lab (25CS2741)** course. The repository integrates bare-metal microcontrollers, ARM Cortex-M processors, sensor interfaces, wireless transceivers, and cloud IoT communication pipelines.

The repository is structured into two main hardware architectural domains:
1. **8051 Microcontroller Architecture (`8051/`):** Low-level memory-mapped GPIO programming, software delay routines, matrix keypad multiplexing, seven-segment decoding, hardware timer interrupts, software PWM fading, stepper motor control, UART serial drivers, and HD44780 LCD drivers.
2. **STM32 ARM Cortex-M Platform (`STM32/`):** STM32CubeMX HAL firmware development, GPIO event handling, non-blocking button state machines, interrupt/DMA UART communication, dual-UART AT modem bridging (Wemos D1 ESP8266), embedded HTTP web server, Bosch Sensortec BME280 I2C sensor drivers, and cloud telemetry streaming via MQTT to Node-RED dashboards.

---

## 2. Repository Structure

```text
25011102080_FIoT_LAB/
│
├── .gitignore
├── README.md
│
├── 8051/
│   ├── CAT1/   # Commercial IoT Teardown & 8051 Toolchain Bring-Up
│   ├── CAT2/   # 8051 Tool Chain Setup & Bare-Metal LED Blink
│   ├── CAT3/   # Switch Polling & 4-State LED Pattern Controller
│   ├── CAT4/   # HMI Matrix Keypad + Seven-Segment + Mode LEDs
│   ├── CAT5/   # Hardware Timer Interrupts (PWM, Signal Gen & Stepper)
│   ├── CAT6/   # UART Driver & Serial PC Terminal Debugging
│   └── CAT7/   # 16x2 LCD Driver Development & Dynamic Display
│
└── STM32/
    ├── CAT8/   # STM32 GPIO Bring-Up & Switch-Controlled LED
    ├── CAT9/   # STM32 UART Command Controlled LED
    ├── CAT10/  # STM32–Wemos Wi-Fi Modem Interface & HTTP Web Server
    ├── CAT11/  # STM32F401RE Cortex-M4 GPIO & User Input Programming
    ├── CAT12/  # BME280 Environmental Sensor Interfacing over I2C
    └── CAT13/  # BME280 MQTT Cloud Telemetry & Node-RED Analytics
```

---

## 3. Experiment Index

### 3.1 8051 Microcontroller Experiments (`8051/`)

| Experiment Identifier | Week | Title / Topic | Hardware Setup & Peripherals | Primary Deliverables |
|---|---|---|---|---|
| **[CAT1](8051/CAT1/)** | Week 1 | Commercial IoT Teardown & 8051 Toolchain Bring-Up | AT89S52 + USB-ISP Programmer + Commercial Smart Bulb/Plug | Teardown analysis report, functional block diagrams, power rail verification |
| **[CAT2](8051/CAT2/)** | Week 2 | 8051 Development Board Tool Chain Setup & GPIO Interfacing | AT89S52 MCU, Port 1 (P1.0), 330Ω Resistor, Red LED | Bare-metal C blink, hardware bring-up sheet, custom delay loop |
| **[CAT3](8051/CAT3/)** | Week 3 | Timer-Based LED Pattern Generator & Switch Polling | AT89S52 MCU, P1.0-P1.3 (4 LEDs), P3.2 (Push Button) | 4-state sequencer (Running LED, Binary Counter, Alternating, Flash), debouncing |
| **[CAT4](8051/CAT4/)** | Week 4 | Human-Machine Interface using Keypad, LEDs & 7-Segment | AT89S52 MCU, 4x4 Keypad (Port 2), 7-Seg Display (Port 0), LEDs (Port 1) | Matrix row-column scanning, digit decoding (0-9), mapped LED functions |
| **[CAT5](8051/CAT5/)** | Week 5 | Hardware Timer Interrupts for LED Fading & Stepper Motor | AT89S52 MCU, Timer 0 (16-bit Mode 1), P1.0 (PWM), ULN2003 + 28BYJ-48 Stepper | 1ms system tick, 500Hz software PWM fading (0-100%), variable square wave, 4-step motor sequencer |
| **[CAT6](8051/CAT6/)** | Week 6 | UART Driver and Serial Debugging | AT89S52 MCU, Timer 1 (Mode 2 8-bit Auto-reload), USB-TTL Converter, PC PuTTY | 9600-8-N-1 UART driver, string transmission, PuTTY character echo, RX ISR |
| **[CAT7](8051/CAT7/)** | Week 7 | 16x2 LCD Driver Development & Dynamic Display Control | AT89S52 MCU, 16x2 HD44780 LCD (4-bit mode on Port 2), 4x4 Keypad (Port 1) | HD44780 4-bit initialization, cursor goto, number printing, keypad interactive character mover |

---

### 3.2 STM32 ARM Cortex-M Experiments (`STM32/`)

| Experiment Identifier | Week | Title / Topic | Hardware Setup & Peripherals | Primary Deliverables |
|---|---|---|---|---|
| **[CAT8](STM32/CAT8/)** | Week 7 | STM32 GPIO Bring-Up and Switch-Controlled LED | STM32 Blue Pill (STM32F103C8T6 ARM Cortex-M3), PC13 User LED, PA0 Push Button | Direct GPIO mirror, debounced event toggle, non-blocking short vs long press classifier |
| **[CAT9](STM32/CAT9/)** | Week 8 | STM32 UART Command Controlled LED | STM32 Blue Pill, USART1 (PA9/PA10), USB-to-UART Adapter, PC PuTTY Terminal | Character echo, string command parser (`LED ON`, `LED OFF`, `LED TOGGLE`), CR/LF validation |
| **[CAT10](STM32/CAT10/)** | Week 9-10 | STM32–Wemos Wi-Fi Modem Interface & HTTP Server | STM32 Blue Pill, Wemos D1 Mini (ESP8266), USART2 (Modem), USART1 (PC Debug) | Dual-UART bridge, AT command engine, TCP server (`AT+CIPSERVER=1,80`), HTML response transmitter, Node-RED client flow |
| **[CAT11](STM32/CAT11/)** | Week 11 | STM32F401RE Cortex-M4 GPIO & User Input Programming | STM32 NUCLEO-F401RE Board (ARM Cortex-M4 @ 84MHz), LD2 (PA5), B1 (PC13) | LD2 onboard bring-up, switch state remembrance, millisecond timestamp duration classifier |
| **[CAT12](STM32/CAT12/)** | Week 12 | Sensor Interfacing (BME280) Using I2C & Bosch Sensor API | STM32 NUCLEO-F401RE, BME280 Environmental Sensor (I2C1: PB8/PB9), Virtual COM | Bosch Sensor API HAL wrappers, sensor calibration compensation, telemetry stream (Temp, Press, Hum) |
| **[CAT13](STM32/CAT13/)** | Week 13 | Sensor Interfacing (BME280) with MQTT & Node Analytics | STM32 NUCLEO-F401RE + BME280 (I2C) + ESP8266 (UART) + Cloud MQTT Broker + Node-RED | Custom ESP8266 MQTT driver, QoS0 publishing (`broker.emqx.io:1883`), remote command subscription, live Node-RED dashboard |

---

## 4. Hardware Platforms & Toolchains

### Hardware Platforms
- **8051 Development System:** Microchip/Atmel AT89S52 8-bit CISC Microcontroller (40-pin DIP, 8KB In-System Flash, 256B RAM, 32 GPIO lines, three 16-bit timers, full-duplex UART).
- **STM32 Blue Pill Board:** STMicroelectronics STM32F103C8T6 ARM Cortex-M3 core @ 72 MHz, 64KB Flash, 20KB SRAM, standard peripherals (USART, SPI, I2C, Timers, ADC).
- **STM32 Nucleo-64 Board:** STMicroelectronics NUCLEO-F401RE ARM Cortex-M4 with FPU @ 84 MHz, 512KB Flash, 96KB SRAM, integrated ST-LINK/V2-1 programmer/debugger.
- **Wireless & Sensor Peripherals:** Wemos D1 Mini / ESP8266 Wi-Fi Module (802.11 b/g/n), Bosch Sensortec BME280 Combined Environmental Sensor (I2C interface).
- **HMI & Actuator Peripherals:** 4x4 Matrix Keypad, Common Cathode 7-Segment Display, 16x2 Character LCD (HD44780 compatible), 28BYJ-48 5V Stepper Motor with ULN2003 Darlington array.

### Development Toolchains & Software
- **Keil µVision C51 (v9.x):** 8051 toolchain for Embedded C compilation, assembly startup generation, and `.hex` binary production.
- **Keil MDK-ARM (v5.x):** ARM Cortex-M toolchain for STM32 firmware compilation and SWD in-circuit debugging.
- **STM32CubeMX:** Graphical initialization tool for pin multiplexing, clock tree synthesis, and HAL peripheral code generation.
- **Serial Debugging:** PuTTY terminal emulator configured for 9600 / 115200 baud, 8 data bits, no parity, 1 stop bit, no flow control.
- **IoT Cloud & Analytics:** Node-RED visual programming environment, EMQX Public MQTT Broker (`broker.emqx.io:1883`), Chrome / Web Browser HTTP client.

---

## 5. Documentation & Submission Compliance

Every experiment folder contains:
1. `README.md` following the standardized format:
   - Header with Experiment Name, Number, Date, and Hardware Platform.
   - Distinct sections for all required subtasks (`TASK A`, `TASK B`, `TASK C`...).
   - Circuit schematic embedded as `![Circuit Diagram](circuit.png)` detailing microcontroller pins, clock, power rails, and connected components.
   - Core Logic, Pseudocode, and complete Embedded C source implementations.
   - Technical Inferences and experimental observations.
2. Verified Embedded C source files (`.c`, `.h`).
3. Hardware schematic diagrams (`circuit.png`).
4. Keil project configuration files (`.uvproj` / `.uvprojx`) and startup assembly files (`STARTUP.A51` / `startup_stm32*.s`).
5. Compiled firmware binaries (`.hex`).
6. Node-RED flow configuration files (`.json`) for networked IoT experiments.
