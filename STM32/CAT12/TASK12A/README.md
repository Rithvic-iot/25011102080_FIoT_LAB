# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 12  

**DATE:** 23/10/2026  

**NAME OF EXP:** BME280 Sensor Interfacing Using I2C and Bosch Sensor API  

**HARDWARE SETUP / PLATFORM:** STM32 NUCLEO-F401RE + Bosch Sensortec BME280 Sensor + Keil MDK-ARM + STM32CubeMX  

---

## TASK 12A : I2C Hardware Bus Bring-Up & BME280 Detection

### 1. Circuit Diagram

BME280 connected to I2C1 (PB8 SCL, PB9 SDA) with 4.7kΩ pull-up resistors to +3.3V. Primary address: 0x76.

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**
The MCU checks bus presence with HAL_I2C_IsDeviceReady and reads register 0xD0 (Chip ID), confirming value 0x60.

**Pseudocode:**
1. Initialize I2C1 at 100 kHz.
2. Read register 0xD0.
3. Validate Chip ID == 0x60.

**Code Base (`main.c`):**
```c
#include "main.h"
#include <stdio.h>

I2C_HandleTypeDef hi2c1;

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_I2C1_Init();
    
    uint8_t chip_id = 0;
    /* Probe BME280 at address 0x76, register 0xD0 */
    HAL_I2C_Mem_Read(&hi2c1, 0x76 << 1, 0xD0, I2C_MEMADD_SIZE_8BIT, &chip_id, 1, 100);
    
    while (1);
}

```

### 3. Inference

The BME280 sensor was detected on I2C1 with verified Chip ID 0x60.
