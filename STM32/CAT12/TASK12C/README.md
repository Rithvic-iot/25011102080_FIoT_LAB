# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 12  

**DATE:** 23/10/2026  

**NAME OF EXP:** BME280 Sensor Interfacing Using I2C and Bosch Sensor API  

**HARDWARE SETUP / PLATFORM:** STM32 NUCLEO-F401RE + BME280 Sensor + PC PuTTY Terminal + Keil MDK-ARM + STM32CubeMX  

---

## TASK 12C : Multi-Variable Environmental Telemetry over UART

### 1. Circuit Diagram

BME280 on I2C1; serial telemetry streaming on USART2 (PA2/PA3) via ST-LINK VCP at 115200 baud.

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**
Acquires compensated temperature, pressure, and relative humidity and transmits formatted ASCII telemetry strings to PuTTY.

**Pseudocode:**
1. Acquire sensor data.
2. Format into ASCII string.
3. Transmit via USART2.
4. Repeat every 1000ms.

**Code Base (`main.c`):**
```c
#include "main.h"
#include "bme280.h"
#include <stdio.h>

I2C_HandleTypeDef hi2c1;
UART_HandleTypeDef huart2;
struct bme280_dev dev;
struct bme280_data comp_data;

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_I2C1_Init();
    MX_USART2_UART_Init();
    
    dev.dev_id = 0x76;
    dev.intf = BME280_I2C_INTF;
    bme280_init(&dev);
    
    while (1) {
        bme280_get_sensor_data(BME280_ALL, &comp_data, &dev);
        HAL_Delay(1000);
    }
}

```

### 3. Inference

Accurate, calibrated environmental telemetry was streamed continuously over UART.
