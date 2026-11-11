/*
 * ============================================================================
 * Experiment: CAT 13 (Week 13)
 * Title: Sensor Interfacing (BME280) with MQTT & Node-RED Cloud Analytics
 * Platform: STMicroelectronics NUCLEO-F401RE
 * Peripherals: BME280 Sensor (I2C1), ESP8266 Modem (USART2: PA2/PA3), Broker EMQX
 * Description: Streams sensor telemetry over MQTT to a cloud broker and Node-RED
 *              dashboard, and processes remote actuator command subscriptions.
 * ============================================================================
 */

#include "main.h"
#include "ESPLib.h"
#include "bme280.h"
#include <stdio.h>
#include <string.h>

UART_HandleTypeDef huart2;
I2C_HandleTypeDef hi2c1;

uint8_t uartRxData;
char mqttData[64];
char mqttTopic[32];

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART2_UART_Init(void);

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_I2C1_Init();
    MX_USART2_UART_Init();

    /* 1. Initialize ESP8266 Wi-Fi Module on USART2 */
    ESP8266_Init(StationMode, huart2);

    /* 2. Connect to local Wi-Fi router */
    ESP8266_wifiConnect("IoT_Lab_AP", "SNU_IoT_2026");

    /* 3. Connect to Public MQTT Broker over standard TCP port 1883 */
    ESP8266_portConnect("TCP", "broker.emqx.io", "1883");

    /* 4. Configure MQTT Client Settings */
    MQTT_InitTypeDef_t mqttSetting;
    mqttSetting.keepAlive = 500;
    mqttSetting.connectFlag = CleanSession;
    mqttSetting.clientID = "SNU_STM32_Node080";
    MQTT_connectBroker(&mqttSetting);

    /* 5. Subscribe to incoming remote control topic */
    MQTT_subscribeTopic("stm32/control", 0);

    /* Start non-blocking UART interrupt reception */
    HAL_UART_Receive_IT(&huart2, &uartRxData, 1);

    char payload[128];
    float mock_temp = 25.4f;
    float mock_hum = 58.2f;

    while (1) {
        /* Format telemetry JSON payload */
        sprintf(payload, "{\"temp\":%.2f,\"hum\":%.2f,\"node\":\"Nucleo-F401\"}", mock_temp, mock_hum);

        /* Publish telemetry to public MQTT broker */
        MQTT_publishTopic("stm32/test/data", payload, QoS0);

        /* Execute incoming message handler */
        MQTTDataHandler(mqttTopic, mqttData);

        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5); /* Heartbeat */
        HAL_Delay(2000); /* 2 second transmission interval */
    }
}

void SysTick_Handler(void) {
    MQTTTimer();
    HAL_IncTick();
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

static void MX_I2C1_Init(void) {
    hi2c1.Instance = I2C1;
    hi2c1.Init.ClockSpeed = 100000;
    hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c1.Init.OwnAddress1 = 0;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    HAL_I2C_Init(&hi2c1);
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
