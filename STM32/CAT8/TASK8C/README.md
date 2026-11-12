# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 8  

**DATE:** 18/09/2026  

**NAME OF EXP:** STM32 GPIO Bring-Up and Switch-Controlled LED  

**HARDWARE SETUP / PLATFORM:** STM32 Blue Pill Board (STM32F103C8T6) + Push Button + Keil MDK-ARM + STM32CubeMX  

---

## TASK 8C : Non-Blocking Short Press vs Long Press Event Classifier

### 1. Circuit Diagram

Button on PA0, on-board LED on PC13.

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**
Timing is measured using HAL_GetTick() upon release. Presses < 1000ms toggle LED; presses >= 1000ms toggle 5 Hz blinking.

**Pseudocode:**
1. Record press timestamp.
2. On release, calculate duration.
3. If duration < 1s, toggle LED; if >= 1s, enable 5 Hz blink mode.

**Code Base (`main.c`):**
```c
#include "main.h"

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    
    uint32_t press_start = 0;
    uint8_t is_blinking = 0;
    uint32_t last_blink = 0;
    
    while (1) {
        if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == GPIO_PIN_SET) {
            if (press_start == 0) press_start = HAL_GetTick();
        } else {
            if (press_start != 0) {
                uint32_t dur = HAL_GetTick() - press_start;
                press_start = 0;
                if (dur >= 50 && dur < 1000) {
                    is_blinking = 0;
                    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
                } else if (dur >= 1000) {
                    is_blinking = !is_blinking;
                }
            }
        }
        
        if (is_blinking && (HAL_GetTick() - last_blink >= 100)) {
            last_blink = HAL_GetTick();
            HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        }
    }
}

```

### 3. Inference

HAL_GetTick() provided non-blocking duration measurement without interrupting continuous background LED blinking.
