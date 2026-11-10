# Foundations of Internet of Things (FIoT) – Lab Repository

**Student Registration Number:** 25011102080  
**Repository Name:** 25011102080_FIoT_LAB  
**Course:** 25CS2741 – Fundamentals of Internet of Things + Lab  
**Department:** Computer Science & Engineering (IoT)  
**Institution:** Shiv Nadar University Chennai  

---

## 1. About

This repository contains all the laboratory experiments completed for the **Fundamentals of Internet of Things (FIoT) Lab**.

The lab tasks cover two hardware architectures:
1. **8051 Microcontroller (AT89S52):** Bare-metal embedded C programming, GPIO control, button debouncing, keypad matrix scanning, seven-segment display, hardware timers, software PWM, serial UART communication, and 16x2 LCD interfacing.
2. **STM32 ARM Cortex-M (Blue Pill STM32F103 & Nucleo-F401RE):** STM32CubeMX and HAL library programming, non-blocking button state machines, serial command parser, ESP8266 Wi-Fi modem interfacing with AT commands, embedded HTTP web server, Bosch BME280 sensor interfacing via I2C, and cloud MQTT telemetry with Node-RED dashboards.

---

## 2. Repository Structure

```text
25011102080_FIoT_LAB/
│
├── .gitignore
├── README.md
│
├── 8051/
│   ├── CAT1/   # Week 1: Commercial IoT Teardown & 8051 Toolchain Bring-Up
│   ├── CAT2/   # Week 2: 8051 Tool Chain Setup & Bare-Metal LED Blink
│   ├── CAT3/   # Week 3: Switch Polling & 4-State LED Pattern Controller
│   ├── CAT4/   # Week 4: HMI Matrix Keypad, LEDs & Seven-Segment Display
│   ├── CAT5/   # Week 5: Hardware Timer Interrupts (PWM Fading & Stepper Motor)
│   ├── CAT6/   # Week 6: UART Driver & Serial PC Terminal Debugging
│   └── CAT7/   # Week 7: 16x2 LCD Driver Development & Keypad Movement
│
└── STM32/
    ├── CAT8/   # Week 7: STM32 GPIO Bring-Up & Switch-Controlled LED
    ├── CAT9/   # Week 8: STM32 UART Command Controlled LED
    ├── CAT10/  # Week 9-10: STM32–Wemos Wi-Fi Modem & Embedded HTTP Server
    ├── CAT11/  # Week 11: STM32F401RE Cortex-M4 GPIO & User Input Programming
    ├── CAT12/  # Week 12: BME280 Environmental Sensor Interfacing over I2C
    └── CAT13/  # Week 13: BME280 MQTT Cloud Telemetry & Node-RED Dashboard
```

---

## 3. Experiment Index

### 3.1 8051 Microcontroller Tasks (`8051/`)

| Folder | Week | Experiment Title | Hardware Used | Key Outcomes |
|---|---|---|---|---|
| **[CAT1](8051/CAT1/)** | Week 1 | Commercial IoT Teardown & Toolchain Setup | Commercial Smart Plug + AT89S52 + Keil µVision | Subsystem teardown analysis, power rail check, Keil C51 setup |
| **[CAT2](8051/CAT2/)** | Week 2 | 8051 Tool Chain Setup & GPIO Interfacing | AT89S52 MCU, P1.0, Red LED, 330Ω resistor | Bare-metal LED blink at ~1 Hz, hardware bring-up sheet, delay loop |
| **[CAT3](8051/CAT3/)** | Week 3 | Timer-Based LED Pattern & Switch Polling | AT89S52, 4 LEDs (P1.0-P1.3), Push Button (P3.2) | 4-state sequencer (Running LED, Counter, Alternate, Flash), debouncing |
| **[CAT4](8051/CAT4/)** | Week 4 | HMI using Matrix Keypad, LEDs & 7-Segment | AT89S52, 4x4 Keypad (P2), 7-Seg (P0), LEDs (P1) | Matrix scanning, 0-9 digit display, mapped LED mode actuation |
| **[CAT5](8051/CAT5/)** | Week 5 | Hardware Timer Interrupts for PWM & Stepper | AT89S52, Timer 0, PWM LED, ULN2003 + Stepper | 1ms timer interrupt, software PWM LED fading (0-100%), stepper motor |
| **[CAT6](8051/CAT6/)** | Week 6 | UART Driver and Serial Debugging | AT89S52, Timer 1, CP2102 USB-TTL, PC PuTTY | 9600 baud 8-N-1 UART driver, string transmission, PuTTY echo |
| **[CAT7](8051/CAT7/)** | Week 7 | 16x2 LCD Driver Development & Display Control| AT89S52, 16x2 HD44780 LCD (4-bit), 4x4 Keypad | 4-bit parallel LCD driver, cursor positioning, keypad character mover |

### 3.2 STM32 ARM Cortex-M Tasks (`STM32/`)

| Folder | Week | Experiment Title | Hardware Used | Key Outcomes |
|---|---|---|---|---|
| **[CAT8](STM32/CAT8/)** | Week 7 | STM32 GPIO Bring-Up & Switch-Controlled LED | STM32 Blue Pill (STM32F103), PC13 LED, PA0 Button| Direct switch mirror, debounced toggle, short vs long press classifier |
| **[CAT9](STM32/CAT9/)** | Week 8 | STM32 UART Command Controlled LED | STM32 Blue Pill, USART1 (PA9/PA10), USB-TTL | Serial character echo, CR/LF testing, command parser (`LED ON/OFF/TOGGLE`) |
| **[CAT10](STM32/CAT10/)** | Week 9-10 | STM32–Wemos Wi-Fi Modem & HTTP Server | STM32 Blue Pill, Wemos D1 ESP8266, Dual UART | Dual-UART bridge, AT commands, TCP server (port 80), HTML response, Node-RED |
| **[CAT11](STM32/CAT11/)** | Week 11 | STM32F401RE Cortex-M4 GPIO Programming | STM32 NUCLEO-F401RE, Green LED LD2, Blue Button B1 | 1 Hz LED blink, button state remembrance, short vs long press detection |
| **[CAT12](STM32/CAT12/)** | Week 12 | BME280 Sensor Interfacing using I2C | STM32 NUCLEO-F401RE, BME280 Sensor (I2C1) | Bosch Sensor API wrappers, temperature/pressure/humidity acquisition |
| **[CAT13](STM32/CAT13/)** | Week 13 | BME280 MQTT Telemetry & Node-RED Dashboard | STM32 NUCLEO-F401RE, BME280, ESP8266, EMQX Broker | Custom ESP8266 MQTT driver, QoS0 publishing, Node-RED live dashboard |

---

## 4. Each Experiment Folder Contains
1. **`README.md`**: Complete lab report containing the experiment details, hardware setup, circuit diagram, pseudocode, code logic, and inferences.
2. **`circuit.png`**: Clear hardware schematic diagram showing the microcontroller, pin numbers, components, power, and ground connections.
3. **Source Code**: Clean Embedded C code (`main.c`, `.h`).
4. **Project Files**: Keil project files (`.uvproj` / `.uvprojx`), startup assembly files, CubeMX `.ioc` files, and compiled `.hex` binaries.
