# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 10  

**DATE:** 05/10/2026  

**NAME OF EXP:** STM32–Wemos Wi-Fi Modem Interface Using AT Commands & Embedded HTTP Server  

**HARDWARE SETUP / PLATFORM:** STM32 Blue Pill + Wemos D1 Mini (ESP8266) + USB-TTL Debugger + Keil MDK-ARM + STM32CubeMX  

---

## TASK 10A : Dual-UART Bridging & AT Commands

### 1. Circuit Diagram

USART1 (PA9/PA10) connects to PC; USART2 (PA2/PA3) connects to ESP8266 modem at 115200 baud.

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**
The STM32 acts as a transparent serial bridge, enabling manual verification of AT commands (AT, AT+CWMODE, AT+CWJAP, AT+CIFSR).

**Pseudocode:**
1. Read byte from USART1 and transmit to USART2.
2. Read byte from USART2 and transmit to USART1.

**Code Base (`main.c`):**
```c
#include "main.h"

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART1_UART_Init();
    MX_USART2_UART_Init();
    
    uint8_t b;
    while (1) {
        /* Bridge PC (USART1) <--> ESP8266 (USART2) */
        if (HAL_UART_Receive(&huart1, &b, 1, 1) == HAL_OK) {
            HAL_UART_Transmit(&huart2, &b, 1, 10);
        }
        if (HAL_UART_Receive(&huart2, &b, 1, 1) == HAL_OK) {
            HAL_UART_Transmit(&huart1, &b, 1, 10);
        }
    }
}

```

### 3. Inference

The dual-UART bridge confirmed that the ESP8266 responded to all fundamental AT commands.
