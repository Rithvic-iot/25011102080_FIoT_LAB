# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 11  

**DATE:** 14/10/2026  

**NAME OF EXP:** STM32F401RE Cortex-M4: GPIO and User Input Programming  

**HARDWARE SETUP / PLATFORM:** STM32 NUCLEO-F401RE Board (ARM Cortex-M4 @ 84 MHz) + ST-LINK/V2-1 + Keil MDK-ARM + STM32CubeMX  

---

## TASK 11A : On-Board Green LED LD2 Bring-Up (1 Hz)

### 1. Circuit Diagram

Nucleo-F401RE on-board user LED LD2 connected to pin PA5 (Active HIGH).

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**
PA5 is configured as Output Push-Pull via CubeMX. The main loop toggles the pin at 1 Hz using HAL_Delay(500).

**Pseudocode:**
1. Initialize PA5 output.
2. In while(1), toggle PA5 and delay 500ms.

**Code Base (`main.c`):**
```c
#include "main.h"

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    
    while (1) {
        /* Green LED LD2 on PA5 (Active HIGH) */
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        HAL_Delay(500);
    }
}

```

### 3. Inference

Green LED LD2 on PA5 blinked steadily at 1.0 Hz, verifying basic Cortex-M4 HAL GPIO bring-up.
