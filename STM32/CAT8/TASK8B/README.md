# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 8  

**DATE:** 18/09/2026  

**NAME OF EXP:** STM32 GPIO Bring-Up and Switch-Controlled LED  

**HARDWARE SETUP / PLATFORM:** STM32 Blue Pill Board (STM32F103C8T6) + Push Button + Keil MDK-ARM + STM32CubeMX  

---

## TASK 8B : Debounced Switch State Toggle

### 1. Circuit Diagram

Tactile push button on PA0; on-board LED on PC13.

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**
Contact bounce is filtered by validating pin state after 25ms delay. On confirmed press, HAL_GPIO_TogglePin inverts LED state.

**Pseudocode:**
1. Detect button rising edge.
2. Confirm press after 25ms.
3. Toggle PC13 and wait for button release.

**Code Base (`main.c`):**
```c
#include "main.h"

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    
    uint8_t last_btn = GPIO_PIN_RESET;
    
    while (1) {
        uint8_t curr = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
        if (curr == GPIO_PIN_SET && last_btn == GPIO_PIN_RESET) {
            HAL_Delay(25); /* Debounce */
            if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET) {
                HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
                while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET);
                HAL_Delay(25);
            }
        }
        last_btn = curr;
    }
}

```

### 3. Inference

The LED toggled cleanly on each button press without spurious transitions.
