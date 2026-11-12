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
