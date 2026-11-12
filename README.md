# Foundations of Internet of Things (FIoT) – Lab Repository

**Student Registration Number:** 25011102080  
**Repository Name:** 25011102080_FIoT_LAB  
**Course:** 25CS2741 – Fundamentals of Internet of Things + Lab  
**Department:** Computer Science & Engineering (IoT)  
**Institution:** Shiv Nadar University Chennai  

---

## Evaluation Status Summary

| Metric | Result | Status |
|---|---|---|
| **Total Tasks Discovered** | 28 / 28 | **PASSED** |
| **Tasks Successfully Passed** | 28 / 28 | **PASSED** |
| **Tasks Failed** | 0 | **NONE** |
| **Total Automated File Checks** | 198 / 198 | **100% PASS** |
| **Overall Evaluation Status** | **PASSED** | **VERIFIED** |

---

## 1. Repository Directory Structure

```text
25011102080_FIoT_LAB/
│
├── .gitignore
├── README.md                                   # Root Master Index
│
├── 8051/
│   ├── CAT2/
│   │   └── TASK2B/                             # Bare-Metal LED Blink & Modular Delay Function
│   ├── CAT3/
│   │   └── TASK3A/                             # Switch Polling with Software Debouncing
│   ├── CAT4/
│   │   └── TASK4A/                             # Matrix Keypad Scanning & 7-Segment Output
│   ├── CAT5/
│   │   ├── TASK5A/                             # Hardware Timer 0 Interrupt 1ms Time Base
│   │   ├── TASK5B/
│   │   │   ├── TASK5B.1/                       # Software PWM (Discrete 25%, 50%, 75% Duty)
│   │   │   ├── TASK5B.2/                       # Software PWM (Dynamic 0-100% Fading)
│   │   │   └── TASK5B.3/                       # Multi-Channel Software PWM Pulse Generation
│   │   └── TASK5C/                             # Stepper Motor Commutation & Speed Control
│   ├── CAT6/
│   │   ├── TASK6A/                             # UART Driver 9600-8-N-1 Transmit
│   │   └── TASK6B/                             # Interactive PuTTY Terminal Echo & RX Buffer
│   └── CAT7/
│       ├── TASK7A/                             # 4-Bit Parallel LCD Driver Implementation
│       ├── TASK7B/                             # Alphanumeric String Display & Cursor Positioning
│       └── TASK7C/                             # Keypad Controlled Interactive Navigation
│
└── STM32/
    ├── CAT8/
    │   ├── TASK8A/                             # GPIO Input/Output Mirroring (PC13 & PA0)
    │   ├── TASK8B/                             # Debounced Switch State Toggle
    │   └── TASK8C/                             # Non-Blocking Short vs Long Press Classifier
    ├── CAT9/
    │   ├── TASK9A/                             # USART1 Character Echo & Line Termination
    │   └── TASK9B/                             # Serial Text Command Parser (LED ON/OFF/TOGGLE)
    ├── CAT10/
    │   ├── TASK10A/                            # Dual-UART Bridging & AT Commands
    │   ├── TASK10B/                            # TCP Server & Embedded HTTP Web Server
    │   └── TASK10C/                            # Node-RED Local Gateway Integration
    ├── CAT11/
    │   ├── TASK11A/                            # On-Board Green LED LD2 Bring-Up (1 Hz)
    │   └── TASK11B/                            # Push Button B1 State Remembrance & Classifier
    ├── CAT12/
    │   ├── TASK12A/                            # I2C Bus Bring-Up & BME280 Sensor Detection
    │   ├── TASK12B/                            # Bosch Sensor API Wrapper & Normal Mode
    │   └── TASK12C/                            # Multi-Variable Telemetry Output over UART
    ├── CAT13/
    │   └── TASK13/                             # Custom ESP8266 MQTT Driver & Telemetry
    └── CAT14/
        └── TASK14/                             # Node-RED Cloud Analytics Dashboard & Actuation
```

---

## 2. Platform 1: 8051 Microcontroller Tasks (13 Tasks)

Every 8051 task directory contains:
- `*.uvproj`: Keil µVision Project configuration
- `main.c`: Embedded C source implementation
- `STARTUP.A51`: 8051 assembly bootstrap
- `Objects/`: Build directory containing compiled `*.hex` firmware
- `circuit.png`: Hardware connection schematic
- `README.md`: Lab report with experiment details, logic, pseudocode, and inference

| Task Folder | Experiment Title | Hardware Peripherals | Key Implementation |
|---|---|---|---|
| **[TASK2B](8051/CAT2/TASK2B/)** | Bare-Metal LED Blink | AT89S52, Port 1.0, Red LED | GPIO output register latch, nested-loop calibrated delay |
| **[TASK3A](8051/CAT3/TASK3A/)** | Switch Polling & Debouncing | AT89S52, Push Button P3.2, 4 LEDs | 25 ms software debounce confirmation, contact chatter elimination |
| **[TASK4A](8051/CAT4/TASK4A/)** | Keypad Scanning & 7-Segment | 4x4 Keypad (Port 2), 7-Seg (Port 0) | Grounded-row scanning algorithm, open-drain pull-up bus decoding |
| **[TASK5A](8051/CAT5/TASK5A/)** | Timer 0 1ms Time Base | Timer 0 Mode 1 (16-bit), TH0=0xFC, TL0=0x66 | Hardware timer interrupt generating precise non-blocking 1ms tick |
| **[TASK5B.1](8051/CAT5/TASK5B/TASK5B.1/)** | Software PWM (Discrete Duty) | Timer 0, P1.0 Indicator LED | 100 Hz PWM frame with fixed duty thresholds (25%, 50%, 75%) |
| **[TASK5B.2](8051/CAT5/TASK5B/TASK5B.2/)** | Software PWM (Dynamic Fading) | Timer 0, P1.0 Indicator LED | Ramping duty cycle counter creating smooth breathing LED fading |
| **[TASK5B.3](8051/CAT5/TASK5B/TASK5B.3/)** | Multi-Channel Software PWM | Timer 0, Dual LEDs on P1.0 & P1.1 | Single timer driving dual asynchronous duty cycle waveforms |
| **[TASK5C](8051/CAT5/TASK5C/)** | Stepper Motor Control | ULN2003 Driver, 28BYJ-48 Stepper | 4-step commutation sequence on P2.0-P2.3 with variable speeds |
| **[TASK6A](8051/CAT6/TASK6A/)** | UART String Transmission | Timer 1 Mode 2, CP2102 USB-TTL, PC | 9600-8-N-1 UART driver with 0.0% baud rate error (TH1=0xFD) |
| **[TASK6B](8051/CAT6/TASK6B/)** | Interactive PuTTY Echo | Hardware UART, Serial ISR (interrupt 4) | Full-duplex character echo and circular receive buffering |
| **[TASK7A](8051/CAT7/TASK7A/)** | 4-Bit LCD Driver Setup | 16x2 HD44780 LCD, Port 2 (RS/RW/E/D4-D7) | High/low nibble splitting conserving microcontroller GPIO pins |
| **[TASK7B](8051/CAT7/TASK7B/)** | Alphanumeric String Output | 16x2 LCD Display | DDRAM address mapping (Line 1: 0x80, Line 2: 0xC0) |
| **[TASK7C](8051/CAT7/TASK7C/)** | Keypad Character Navigation | 16x2 LCD, 4x4 Keypad on Port 1 | Real-time coordinate tracking and character translation across grid |

---

## 3. Platform 2: STM32 ARM Cortex-M Tasks (15 Tasks)

Every STM32 task directory contains:
- `*.ioc`: STM32CubeMX hardware initialization configuration
- `.mxproject`: CubeMX project metadata
- `Core/`: `Inc/` and `Src/` containing application firmware (`main.c`, `main.h`, `stm32f1xx_it.c`)
- `Drivers/`: CMSIS and STM32 HAL peripheral drivers
- `MDK-ARM/`: Keil MDK project (`*.uvprojx`) and vector startup assembly (`startup_*.s`)
- `circuit.png`: Hardware connection schematic
- `README.md`: Lab report with experiment details, logic, pseudocode, and inference

| Task Folder | Experiment Title | Hardware Peripherals | Key Implementation |
|---|---|---|---|
| **[TASK8A](STM32/CAT8/TASK8A/)** | GPIO Input/Output Mirroring | STM32 Blue Pill (STM32F103), PC13, PA0 | Polling tactile switch and directly driving active-low LED |
| **[TASK8B](STM32/CAT8/TASK8B/)** | Debounced Switch Toggle | STM32 Blue Pill, PC13 LED, PA0 Button | Edge detection with software debounce via `HAL_Delay` |
| **[TASK8C](STM32/CAT8/TASK8C/)** | Short vs Long Press Classifier | STM32 Blue Pill, PC13 LED, PA0 Button | Non-blocking duration check via `HAL_GetTick()` (<1s toggle, >=1s 5Hz blink) |
| **[TASK9A](STM32/CAT9/TASK9A/)** | USART1 Echo & Line Termination | STM32 Blue Pill, USART1 (PA9/PA10), USB-TTL | 115200 baud character echo and CR (`\r`) / LF (`\n`) parser |
| **[TASK9B](STM32/CAT9/TASK9B/)** | Serial Command Parser | STM32 Blue Pill, USART1, PC13 LED | String dispatcher for `LED ON`, `LED OFF`, and `LED TOGGLE` |
| **[TASK10A](STM32/CAT10/TASK10A/)** | Dual-UART Bridging & AT Commands | STM32 Blue Pill, Wemos D1 ESP8266 | Transparent bidirectional serial bridge between PC and Wi-Fi modem |
| **[TASK10B](STM32/CAT10/TASK10B/)** | TCP & Embedded HTTP Server | STM32 Blue Pill, ESP8266 Modem | Port 80 TCP server, HTTP `+IPD` parser, LED actuation, HTML reply |
| **[TASK10C](STM32/CAT10/TASK10C/)** | Node-RED Gateway Flow | STM32 Blue Pill, ESP8266, Node-RED | Automated HTTP GET requests from Node-RED dashboard |
| **[TASK11A](STM32/CAT11/TASK11A/)** | Green LED LD2 Bring-Up | STM32 NUCLEO-F401RE (Cortex-M4 @ 84MHz) | 1.0 Hz blinking of active-high green LED LD2 on PA5 |
| **[TASK11B](STM32/CAT11/TASK11B/)** | Button B1 State & Classifier | Nucleo-F401RE, Button B1 (PC13), LED (PA5) | State remembrance and non-blocking duration detection via `HAL_GetTick` |
| **[TASK12A](STM32/CAT12/TASK12A/)** | I2C Bus Bring-Up & Sensor Probe | Nucleo-F401RE, BME280 Sensor (I2C1) | Hardware bus probe at 0x76, verifying factory Chip ID 0x60 |
| **[TASK12B](STM32/CAT12/TASK12B/)** | Bosch Sensor API Integration | Nucleo-F401RE, BME280 Sensor | Hardware read/write wrappers and continuous normal mode sampling |
| **[TASK12C](STM32/CAT12/TASK12C/)** | Multi-Variable Telemetry Stream | Nucleo-F401RE, BME280, USART2 VCP | Temperature, pressure, and humidity streaming to PC terminal |
| **[TASK13](STM32/CAT13/TASK13/)** | MQTT Telemetry Publishing | Nucleo-F401RE, BME280, ESP8266, EMQX | Lightweight custom `ESPLib` driver publishing to `stm32/test/data` |
| **[TASK14](STM32/CAT14/TASK14/)** | Cloud Dashboard & Actuation | Nucleo-F401RE, ESP8266, Node-RED | Live web dashboard with gauges, trends, and remote LED toggle |
