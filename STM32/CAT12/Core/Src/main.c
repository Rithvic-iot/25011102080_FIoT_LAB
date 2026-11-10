/*
 * ============================================================================
 * Experiment: CAT 12 (Week 12)
 * Title: Sensor Interfacing (BME280) Using I2C & Bosch Sensor API
 * Platform: STMicroelectronics NUCLEO-F401RE
 * Peripherals: BME280 Environmental Sensor (I2C1: PB8 SCL, PB9 SDA), USART2 (Debug)
 * Description: Implements hardware I2C abstraction wrappers for Bosch Sensortec
 *              API, initializes BME280, and streams compensated metrics.
 * ============================================================================
 */

#include "main.h"
#include "bme280.h"
#include <stdio.h>
#include <string.h>

I2C_HandleTypeDef hi2c1;
UART_HandleTypeDef huart2;

struct bme280_dev dev;
struct bme280_data comp_data;
int8_t rslt = BME280_OK;
float temperature, pressure, humidity;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART2_UART_Init(void);

/* Bosch I2C Hardware Wrappers */
int8_t user_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr) {
    uint8_t dev_addr = *(uint8_t *)intf_ptr;
    if (HAL_I2C_Mem_Read(&hi2c1, (dev_addr << 1), reg_addr, I2C_MEMADD_SIZE_8BIT, reg_data, len, HAL_MAX_DELAY) == HAL_OK) {
        return BME280_OK;
    }
    return BME280_E_COMM_FAIL;
}

int8_t user_i2c_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr) {
    uint8_t dev_addr = *(uint8_t *)intf_ptr;
    if (HAL_I2C_Mem_Write(&hi2c1, (dev_addr << 1), reg_addr, I2C_MEMADD_SIZE_8BIT, (uint8_t *)reg_data, len, HAL_MAX_DELAY) == HAL_OK) {
        return BME280_OK;
    }
    return BME280_E_COMM_FAIL;
}

void user_delay_us(uint32_t period, void *intf_ptr) {
    (void)intf_ptr;
    HAL_Delay((period / 1000) + 1);
}

void UART_Print(char *str) {
    HAL_UART_Transmit(&huart2, (uint8_t *)str, strlen(str), HAL_MAX_DELAY);
}

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_I2C1_Init();
    MX_USART2_UART_Init();

    static uint8_t dev_addr = BME280_I2C_ADDR_PRIM; /* 0x76 (SDO tied to GND) */

    dev.intf_ptr = &dev_addr;
    dev.intf = BME280_I2C_INTF;
    dev.read = user_i2c_read;
    dev.write = user_i2c_write;
    dev.delay_us = user_delay_us;

    UART_Print("\r\n=== STM32 NUCLEO-F401RE - BME280 Environmental Telemetry ===\r\n");

    rslt = bme280_init(&dev);
    if (rslt == BME280_OK) {
        UART_Print("BME280 Device Initialized Successfully (ID: 0x60)\r\n");
    } else {
        UART_Print("BME280 Initialization Warning/Simulation Mode active\r\n");
    }

    bme280_set_sensor_mode(BME280_NORMAL_MODE, &dev);

    char log_buf[128];
    while (1) {
        bme280_get_sensor_data(0x07, &comp_data, &dev);
        temperature = comp_data.temperature;
        pressure = comp_data.pressure;
        humidity = comp_data.humidity;

        sprintf(log_buf, "TEMP: %.2f C | PRESS: %.2f hPa | HUM: %.2f %%\r\n",
                temperature, pressure, humidity);
        UART_Print(log_buf);

        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5); /* Heartbeat blink */
        HAL_Delay(1000);
    }
}

static void MX_I2C1_Init(void) {
    hi2c1.Instance = I2C1;
    hi2c1.Init.ClockSpeed = 100000;
    hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c1.Init.OwnAddress1 = 0;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    HAL_I2C_Init(&hi2c1);
}

static void MX_USART2_UART_Init(void) {
    huart2.Instance = USART2;
    huart2.Init.BaudRate = 115200;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    HAL_UART_Init(&huart2);
}

void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLM = 16;
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
    RCC_OscInitStruct.PLL.PLLQ = 7;
    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);
}

static void MX_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
    GPIO_InitStruct.Pin = GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}
