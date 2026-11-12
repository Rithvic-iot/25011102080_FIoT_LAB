# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 12  

**DATE:** 23/10/2026  

**NAME OF EXP:** BME280 Sensor Interfacing Using I2C and Bosch Sensor API  

**HARDWARE SETUP / PLATFORM:** STM32 NUCLEO-F401RE + Bosch Sensortec BME280 + Keil MDK-ARM + STM32CubeMX  

---

## TASK 12B : Bosch Sensor API Wrapper & Normal Mode Sampling

### 1. Circuit Diagram

BME280 on I2C1, Bosch driver integration.

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**
Wraps HAL_I2C read/write into Bosch API callback signatures, loading trim calibration parameters and enabling normal continuous sampling.

**Pseudocode:**
1. Implement bme280_i2c_read and bme280_i2c_write.
2. Call bme280_init(&dev).
3. Set oversampling and normal power mode.

**Code Base (`main.c`):**
```c
#include "main.h"
#include "bme280.h"

I2C_HandleTypeDef hi2c1;
struct bme280_dev dev;

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_I2C1_Init();
    
    dev.dev_id = 0x76;
    dev.intf = BME280_I2C_INTF;
    bme280_init(&dev);
    
    while (1);
}

```

### 3. Inference

The Bosch Sensor API initialized and applied factory calibration compensation trim parameters.
