# Foundations of Internet of Things (FIoT) – Lab Repository

**Student Registration Number:** 25011102080  
**Repository Name:** 25011102080_FIoT_LAB  
**Course:** 25CS2741 – Fundamentals of Internet of Things + Lab  
**Department:** Computer Science & Engineering (IoT)  
**Institution:** Shiv Nadar University Chennai  

---

## 1. About

This repository contains all laboratory experiments and subtasks completed for the **Fundamentals of Internet of Things (FIoT) Lab**.

The lab tasks cover two core hardware architectures:
1. **8051 Microcontroller (AT89S52):** Bare-metal Embedded C, GPIO control, button debouncing, matrix keypad scanning, seven-segment display decoding, hardware timers, software PWM dimming, UART serial communication, and 16x2 HD44780 LCD interfacing.
2. **STM32 ARM Cortex-M (STM32F103 Blue Pill & NUCLEO-F401RE):** STM32CubeMX HAL programming, non-blocking button state machines, serial command parser, ESP8266 Wi-Fi modem interfacing with AT commands, embedded TCP/HTTP web server, Bosch Sensortec BME280 environmental sensor interfacing via I2C, and cloud MQTT telemetry with Node-RED dashboards.

---

## 2. Repository Structure

```text
25011102080_FIoT_LAB/
│
├── .gitignore
├── README.md
│
├── 8051/
│   ├── CAT2/   # 8051 Tool Chain Setup & GPIO Interfacing
│   │   ├── TASKA/      # Task 2A: Hardware Board Bring-Up & Rail Verification
│   │   └── TASKB/      # Task 2B: Bare-Metal LED Blink & Modular Delay Function
│   ├── CAT3/   # Switch Polling & 4-State LED Pattern Sequencer
│   │   ├── TASKA/      # Task 3A: Switch Polling with Software Debouncing
│   │   └── TASKB/      # Task 3B: 4-State LED Pattern Sequencer
│   ├── CAT4/   # HMI Matrix Keypad, LEDs & Seven-Segment Display
│   │   ├── TASKA/      # Task 4A: Matrix Keypad Scanning
│   │   ├── TASKB/      # Task 4B: Common Cathode 7-Segment Display Decoding
│   │   └── TASKC/      # Task 4C: Keypad Controlled LED Pattern Modes
│   ├── CAT5/   # Hardware Timer Interrupts (PWM Fading & Stepper Motor)
│   │   ├── TASKA/      # Task 5A: Hardware Timer 0 Interrupt 1ms Time Base
│   │   ├── TASKB/      # Task 5B: Software PWM LED Fading (0% to 100%)
│   │   └── TASKC/      # Task 5C: Stepper Motor Commutation & Speed Control
│   ├── CAT6/   # UART Driver & Serial PC Terminal Debugging
│   │   ├── TASKA/      # Task 6A: UART Driver Initialization & 9600-8-N-1 Transmit
│   │   └── TASKB/      # Task 6B: Interactive PuTTY Terminal Echo & RX Buffer
│   └── CAT7/   # 16x2 LCD Driver Development & Interactive Display Control
│       ├── TASKA/      # Task 7A: 4-Bit Parallel LCD Driver Implementation
│       ├── TASKB/      # Task 7B: Alphanumeric String Display & Cursor Positioning
│       └── TASKC/      # Task 7C: Keypad Controlled Interactive Character Navigation
│
└── STM32/
    ├── CAT8/   # STM32 GPIO Bring-Up & Switch-Controlled LED
    │   ├── TASKA/      # Task 8A: GPIO Input/Output Bring-Up
    │   ├── TASKB/      # Task 8B: Debounced Switch State Toggle
    │   └── TASKC/      # Task 8C: Non-Blocking Short Press vs Long Press Classifier
    ├── CAT9/   # STM32 UART Command Controlled LED
    │   ├── TASKA/      # Task 9A: UART Character Echo & Line Termination Analysis
    │   └── TASKB/      # Task 9B: Serial Text Command Parser (LED ON/OFF/TOGGLE)
    ├── CAT10/  # STM32–Wemos Wi-Fi Modem & Embedded HTTP Server
    │   ├── TASKA/      # Task 10A & 10B: Dual-UART Bridging & AT Commands
    │   ├── TASKB/      # Task 10C & 10D: TCP Server & Embedded HTTP Web Server
    │   └── TASKC/      # Task 10E: Node-RED Local Gateway Integration
    ├── CAT11/  # STM32F401RE Cortex-M4 GPIO & User Input Programming
    │   ├── TASKA/      # Task 11A: On-Board Green LED LD2 Bring-Up (1 Hz)
    │   ├── TASKB/      # Task 11B: Push Button B1 State Remembrance
    │   └── TASKC/      # Task 11C: Non-Blocking Short vs Long Press Detection
    ├── CAT12/  # BME280 Environmental Sensor Interfacing over I2C
    │   ├── TASKA/      # Task 12A: I2C Hardware Bus Bring-Up & Sensor Detection
    │   ├── TASKB/      # Task 12B: Bosch Sensor API Wrapper & Normal Mode Sampling
    │   └── TASKC/      # Task 12C: Multi-Variable Telemetry Output over UART
    └── CAT13/  # BME280 MQTT Cloud Telemetry & Node-RED Dashboard
        ├── TASKA/      # Task 13A: Custom ESP8266 MQTT Client Driver (ESPLib)
        ├── TASKB/      # Task 13B: Cloud Telemetry Publishing & Remote Actuation
        └── TASKC/      # Task 13C: Node-RED IoT Cloud Analytics Dashboard
```

---

## 3. Experiment & Task Index

### 3.1 8051 Microcontroller Tasks (`8051/`)

| Folder | Experiment Name | Subtasks | Hardware Platform |
|---|---|---|---|
| **[CAT2](8051/CAT2/)** | 8051 Development Board Tool Chain Setup & GPIO Interfacing | • [TASKA](8051/CAT2/TASKA/): Board Bring-Up & Rail Verification<br>• [TASKB](8051/CAT2/TASKB/): Bare-Metal LED Blink | AT89S52 MCU, P1.0, Red LED, 330Ω Resistor |
| **[CAT3](8051/CAT3/)** | Timer-Based LED Pattern & Switch Polling | • [TASKA](8051/CAT3/TASKA/): Switch Polling & Software Debouncing<br>• [TASKB](8051/CAT3/TASKB/): 4-State LED Sequencer | AT89S52, 4 LEDs (P1.0-P1.3), Push Button (P3.2) |
| **[CAT4](8051/CAT4/)** | HMI using Matrix Keypad, LEDs & 7-Segment Display | • [TASKA](8051/CAT4/TASKA/): 4x4 Keypad Matrix Scanning<br>• [TASKB](8051/CAT4/TASKB/): 7-Segment Display Output<br>• [TASKC](8051/CAT4/TASKC/): Keypad Actuated LED Modes | AT89S52, 4x4 Keypad (P2), 7-Seg (P0), LEDs (P1) |
| **[CAT5](8051/CAT5/)** | Hardware Timer Interrupts for PWM & Stepper Control | • [TASKA](8051/CAT5/TASKA/): Timer 0 1ms Time Base<br>• [TASKB](8051/CAT5/TASKB/): Software PWM LED Fading (0-100%)<br>• [TASKC](8051/CAT5/TASKC/): Stepper Motor Commutation | AT89S52, Timer 0, PWM LED, ULN2003 + Stepper |
| **[CAT6](8051/CAT6/)** | UART Driver and Serial Debugging | • [TASKA](8051/CAT6/TASKA/): UART Driver 9600-8-N-1 Transmit<br>• [TASKB](8051/CAT6/TASKB/): Interactive PuTTY Echo & RX Buffer | AT89S52, Timer 1, CP2102 USB-TTL, PC PuTTY |
| **[CAT7](8051/CAT7/)** | 16x2 LCD Driver Development & Display Control | • [TASKA](8051/CAT7/TASKA/): 4-Bit Parallel LCD Driver<br>• [TASKB](8051/CAT7/TASKB/): String Display & Cursor Control<br>• [TASKC](8051/CAT7/TASKC/): Keypad Character Navigation | AT89S52, 16x2 HD44780 LCD, 4x4 Keypad |

### 3.2 STM32 ARM Cortex-M Tasks (`STM32/`)

| Folder | Experiment Name | Subtasks | Hardware Platform |
|---|---|---|---|
| **[CAT8](STM32/CAT8/)** | STM32 GPIO Bring-Up and Switch-Controlled LED | • [TASKA](STM32/CAT8/TASKA/): GPIO Input/Output Bring-Up<br>• [TASKB](STM32/CAT8/TASKB/): Debounced Switch Toggle<br>• [TASKC](STM32/CAT8/TASKC/): Short vs Long Press Classifier | STM32 Blue Pill (STM32F103), PC13 LED, PA0 Button |
| **[CAT9](STM32/CAT9/)** | STM32 UART Command Controlled LED | • [TASKA](STM32/CAT9/TASKA/): Character Echo & Line Termination<br>• [TASKB](STM32/CAT9/TASKB/): Text Command Parser | STM32 Blue Pill, USART1 (PA9/PA10), USB-TTL |
| **[CAT10](STM32/CAT10/)** | STM32–Wemos Wi-Fi Modem & Embedded HTTP Server | • [TASKA](STM32/CAT10/TASKA/): Dual-UART Bridging & AT Commands<br>• [TASKB](STM32/CAT10/TASKB/): TCP Server & HTTP Response<br>• [TASKC](STM32/CAT10/TASKC/): Node-RED Gateway Flow | STM32 Blue Pill, Wemos D1 ESP8266, Dual UART |
| **[CAT11](STM32/CAT11/)** | STM32F401RE Cortex-M4 GPIO Programming | • [TASKA](STM32/CAT11/TASKA/): On-Board Green LED LD2 Blink<br>• [TASKB](STM32/CAT11/TASKB/): Button B1 State Remembrance<br>• [TASKC](STM32/CAT11/TASKC/): Short vs Long Press Classifier | STM32 NUCLEO-F401RE, Green LED LD2, Blue Button B1 |
| **[CAT12](STM32/CAT12/)** | BME280 Sensor Interfacing using I2C | • [TASKA](STM32/CAT12/TASKA/): I2C Bus Bring-Up & ID Check<br>• [TASKB](STM32/CAT12/TASKB/): Bosch Sensor API Integration<br>• [TASKC](STM32/CAT12/TASKC/): Environmental Data Telemetry | STM32 NUCLEO-F401RE, BME280 Sensor (I2C1) |
| **[CAT13](STM32/CAT13/)** | BME280 MQTT Telemetry & Node-RED Dashboard | • [TASKA](STM32/CAT13/TASKA/): Custom ESP8266 MQTT Driver<br>• [TASKB](STM32/CAT13/TASKB/): Telemetry Publishing & Actuation<br>• [TASKC](STM32/CAT13/TASKC/): Node-RED Live Dashboard | STM32 NUCLEO-F401RE, BME280, ESP8266, EMQX Broker |

---

## 4. Evaluator Verification Standards

Every experiment and subtask directory contains:
1. **`README.md`**: Complete student lab report including experiment details, hardware setup, circuit diagram, pseudocode, code logic, and inferences.
2. **`circuit.png`**: High-resolution hardware schematic diagram.
3. **Source Code**: Clean Embedded C source code (`main.c`, `.h`).
4. **Project Files**: Keil project files (`.uvproj` / `.uvprojx`), startup assembly, CubeMX `.ioc` files, and `.hex` binaries.
