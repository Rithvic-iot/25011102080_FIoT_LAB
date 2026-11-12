# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 9  

**DATE:** 28/09/2026  

**NAME OF EXP:** STM32 UART Command Controlled LED  

**HARDWARE SETUP / PLATFORM:** STM32 Blue Pill (STM32F103) + CP2102 USB-TTL + PC PuTTY + Keil MDK-ARM + STM32CubeMX  

---

## TASK 9A : USART1 Character Echo & Line Termination Analysis

### 1. Circuit Diagram

USART1 PA9 (TX) and PA10 (RX) connected to USB-TTL at 115200-8-N-1.

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**
Characters received via HAL_UART_Receive are echoed back to the terminal. Both \r and \n line terminations are recognized.

**Pseudocode:**
1. Poll UART for incoming character.
2. Echo character back to terminal.
3. Handle carriage return and line feed.

**Code Base (`main.c`):**
```c
#include "main.h"
#include <string.h>

UART_HandleTypeDef huart1;

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART1_UART_Init();
    
    uint8_t ch;
    while (1) {
        if (HAL_UART_Receive(&huart1, &ch, 1, 10) == HAL_OK) {
            HAL_UART_Transmit(&huart1, &ch, 1, 10); /* Echo character */
            if (ch == '\r') {
                uint8_t lf = '\n';
                HAL_UART_Transmit(&huart1, &lf, 1, 10);
            }
        }
    }
}

```

### 3. Inference

The STM32 echoed characters in real-time and handled terminal line endings correctly.
