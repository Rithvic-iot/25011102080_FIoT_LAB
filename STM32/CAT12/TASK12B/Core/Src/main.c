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
