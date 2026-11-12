# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 10  

**DATE:** 12/10/2026  

**NAME OF EXP:** STM32–Wemos Wi-Fi Modem Interface Using AT Commands & Embedded HTTP Server  

**HARDWARE SETUP / PLATFORM:** STM32 Blue Pill + Wemos D1 Mini + Node-RED Local Gateway  

---

## TASK 10C : Node-RED Local Gateway Integration

### 1. Circuit Diagram

STM32 HTTP server interacting with Node-RED over the local Wi-Fi network.

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**
Node-RED HTTP Request nodes send automated GET requests to the ESP8266 IP address to actuate the LED and display feedback.

**Pseudocode:**
1. Node-RED sends HTTP GET.
2. STM32 processes request and responds.
3. Node-RED updates UI status.

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

Node-RED communicated with the embedded server, providing graphical dashboard control over Wi-Fi.
