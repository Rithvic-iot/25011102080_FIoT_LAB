# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 8  

**DATE:** 18/09/2026  

**NAME OF EXP:** STM32 GPIO Bring-Up and Switch-Controlled LED  

**HARDWARE SETUP / PLATFORM:** STM32 Blue Pill Board (STM32F103C8T6 @ 72 MHz) + External Push Button + Keil MDK-ARM + STM32CubeMX  

---

## TASK 8A : STM32 GPIO Input/Output Bring-Up

### 1. Circuit Diagram

Push button connected to PA0 with 10kΩ pull-down resistor to GND; on-board user LED on PC13 (Active LOW).

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**
The microcontroller polls PA0. When button is pressed (PA0 == HIGH), PC13 is pulled LOW turning the LED ON.

**Pseudocode:**
1. Initialize GPIOs via CubeMX.
2. In while(1), read PA0.
3. If PA0 is HIGH, write PC13 LOW (LED ON); else write PC13 HIGH (LED OFF).

**Code Base (`main.c`):**
```c
#include "main.h"

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    
    while (1) {
        /* Read button on PA0 (Active HIGH) and drive PC13 LED (Active LOW) */
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET) {
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET); /* LED ON */
        } else {
            HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);   /* LED OFF */
        }
    }
}

```

### 3. Inference

The STM32 HAL GPIO functions accurately read the switch and mirrored its state to the LED.
