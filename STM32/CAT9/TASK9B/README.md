# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 9  

**DATE:** 28/09/2026  

**NAME OF EXP:** STM32 UART Command Controlled LED  

**HARDWARE SETUP / PLATFORM:** STM32 Blue Pill + USB-TTL Module + PC Terminal + Keil MDK-ARM + STM32CubeMX  

---

## TASK 9B : Serial Text Command Parser (LED ON/OFF/TOGGLE)

### 1. Circuit Diagram

USART1 (PA9/PA10) serial interface, PC13 on-board LED.

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**
Incoming characters accumulate in a buffer until Enter is pressed. String comparison dispatches commands (LED ON, LED OFF, LED TOGGLE).

**Pseudocode:**
1. Accumulate characters until newline.
2. Compare string against valid command table.
3. Actuate PC13 and return response string.

**Code Base (`main.c`):**
```c
#include "main.h"
#include <string.h>

UART_HandleTypeDef huart1;
char rx_buf[64];
uint8_t rx_idx = 0;

void send_str(char *s) {
    HAL_UART_Transmit(&huart1, (uint8_t*)s, strlen(s), 100);
}

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART1_UART_Init();
    
    uint8_t ch;
    while (1) {
        if (HAL_UART_Receive(&huart1, &ch, 1, 10) == HAL_OK) {
            HAL_UART_Transmit(&huart1, &ch, 1, 10);
            if (ch == '\r' || ch == '\n') {
                if (rx_idx > 0) {
                    rx_buf[rx_idx] = '\0';
                    if (strcmp(rx_buf, "LED ON") == 0) {
                        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
                        send_str("\r\n[STM32] LED is turned ON\r\n");
                    } else if (strcmp(rx_buf, "LED OFF") == 0) {
                        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
                        send_str("\r\n[STM32] LED is turned OFF\r\n");
                    } else if (strcmp(rx_buf, "LED TOGGLE") == 0) {
                        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
                        send_str("\r\n[STM32] LED toggled\r\n");
                    } else {
                        send_str("\r\n[ERROR] Unknown command\r\n");
                    }
                    rx_idx = 0;
                }
            } else {
                if (rx_idx < sizeof(rx_buf) - 1) rx_buf[rx_idx++] = ch;
            }
        }
    }
}

```

### 3. Inference

The command parser executed all valid string commands and reported errors for unrecognized inputs.
