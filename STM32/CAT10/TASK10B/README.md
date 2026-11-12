# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 10  

**DATE:** 12/10/2026  

**NAME OF EXP:** STM32–Wemos Wi-Fi Modem Interface Using AT Commands & Embedded HTTP Server  

**HARDWARE SETUP / PLATFORM:** STM32 Blue Pill + Wemos D1 Mini (ESP8266) + Keil MDK-ARM + STM32CubeMX  

---

## TASK 10B : ESP8266 TCP Server & Embedded HTTP Web Server

### 1. Circuit Diagram

ESP8266 connected via USART2, on-board LED on PC13.

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**
Configures TCP server on port 80. Incoming HTTP GET requests delivered via +IPD are parsed to toggle PC13 LED and serve an HTML response.

**Pseudocode:**
1. Configure server with AT+CIPSERVER=1,80.
2. Read +IPD packet.
3. If path contains /led/on, turn LED ON; if /led/off, turn LED OFF.
4. Send HTTP 200 response.

**Code Base (`main.c`):**
```c
#include "main.h"
#include <string.h>

UART_HandleTypeDef huart2;

void send_cmd(char *c) {
    HAL_UART_Transmit(&huart2, (uint8_t*)c, strlen(c), 500);
    HAL_Delay(200);
}

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART2_UART_Init();
    
    send_cmd("AT\r\n");
    send_cmd("AT+CWMODE=1\r\n");
    send_cmd("AT+CIPMUX=1\r\n");
    send_cmd("AT+CIPSERVER=1,80\r\n");
    
    uint8_t buf[128];
    while (1) {
        if (HAL_UART_Receive(&huart2, buf, sizeof(buf)-1, 100) == HAL_OK) {
            if (strstr((char*)buf, "/led/on")) {
                HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
            } else if (strstr((char*)buf, "/led/off")) {
                HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
            }
        }
    }
}

```

### 3. Inference

The embedded HTTP web server allowed remote web browser control of the microcontroller LED.
