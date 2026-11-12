# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 11  

**DATE:** 14/10/2026  

**NAME OF EXP:** STM32F401RE Cortex-M4: GPIO and User Input Programming  

**HARDWARE SETUP / PLATFORM:** STM32 NUCLEO-F401RE Board + User Button B1 (PC13) + Green LED LD2 (PA5) + Keil MDK-ARM + STM32CubeMX  

---

## TASK 11B : Push Button B1 State Remembrance & Duration Classifier

### 1. Circuit Diagram

User Button B1 on PC13 with hardware pull-up (Active LOW); LD2 on PA5.

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**
Reads B1 and measures press duration using HAL_GetTick(). Short press toggles LED; long press (>1s) activates fast blinking.

**Pseudocode:**
1. Poll PC13.
2. Measure press duration.
3. Actuate PA5 accordingly.

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
        /* User Button B1 on PC13 is Active LOW */
        if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET) {
            if (press_start == 0) press_start = HAL_GetTick();
        } else {
            if (press_start != 0) {
                uint32_t dur = HAL_GetTick() - press_start;
                press_start = 0;
                if (dur >= 50 && dur < 1000) {
                    is_blinking = 0;
                    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
                } else if (dur >= 1000) {
                    is_blinking = !is_blinking;
                }
            }
        }
        
        if (is_blinking && (HAL_GetTick() - last_blink >= 100)) {
            last_blink = HAL_GetTick();
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        }
    }
}

```

### 3. Inference

Button B1 demonstrated state remembrance and reliable short vs long press classification.
