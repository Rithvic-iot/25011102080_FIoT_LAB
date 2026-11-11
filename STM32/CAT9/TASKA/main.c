/*
 * ============================================================================
 * Experiment: CAT 9 (Week 8)
 * Title: STM32 UART Command Controlled LED
 * Platform: STM32 Blue Pill (STM32F103C8T6 ARM Cortex-M3)
 * Peripherals: USART1 (PA9 TX, PA10 RX @ 9600-8-N-1), PC13 User LED
 * Description: Character and string transmission/reception, CR/LF parsing,
 *              and text command parser (LED ON, LED OFF, LED TOGGLE).
 * ============================================================================
 */

#include "main.h"
#include <string.h>
#include <stdio.h>

UART_HandleTypeDef huart1;

#define RX_BUFFER_SIZE 64
char rx_char;
char rx_line[RX_BUFFER_SIZE];
uint8_t rx_index = 0;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);

void UART_SendString(char *str) {
    HAL_UART_Transmit(&huart1, (uint8_t *)str, strlen(str), HAL_MAX_DELAY);
}

void Process_Command(char *cmd) {
    /* Strip leading/trailing whitespaces or carriage returns */
    while (*cmd == ' ' || *cmd == '\r' || *cmd == '\n') cmd++;
    int len = strlen(cmd);
    while (len > 0 && (cmd[len - 1] == ' ' || cmd[len - 1] == '\r' || cmd[len - 1] == '\n')) {
        cmd[--len] = '\0';
    }

    if (strcmp(cmd, "LED ON") == 0) {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET); /* Active LOW: Turn ON */
        UART_SendString("OK: LED turned ON\r\n");
    } else if (strcmp(cmd, "LED OFF") == 0) {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);   /* Turn OFF */
        UART_SendString("OK: LED turned OFF\r\n");
    } else if (strcmp(cmd, "LED TOGGLE") == 0) {
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        UART_SendString("OK: LED toggled\r\n");
    } else if (strcmp(cmd, "STATUS") == 0) {
        if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET) {
            UART_SendString("STATUS: LED is ON\r\n");
        } else {
            UART_SendString("STATUS: LED is OFF\r\n");
        }
    } else {
        UART_SendString("ERROR: Unknown Command. Available: LED ON, LED OFF, LED TOGGLE, STATUS\r\n");
    }
}

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART1_UART_Init();

    /* Initial banner */
    UART_SendString("\r\n========================================\r\n");
    UART_SendString("  STM32 UART Command Controlled LED Ready \r\n");
    UART_SendString("  Commands: LED ON | LED OFF | LED TOGGLE \r\n");
    UART_SendString("========================================\r\n> ");

    while (1) {
        /* Receive 1 byte synchronously */
        if (HAL_UART_Receive(&huart1, (uint8_t *)&rx_char, 1, 100) == HAL_OK) {
            /* Echo character back */
            HAL_UART_Transmit(&huart1, (uint8_t *)&rx_char, 1, HAL_MAX_DELAY);

            if (rx_char == '\r' || rx_char == '\n') {
                HAL_UART_Transmit(&huart1, (uint8_t *)"\n", 1, HAL_MAX_DELAY);
                rx_line[rx_index] = '\0';
                if (rx_index > 0) {
                    Process_Command(rx_line);
                    rx_index = 0;
                }
                UART_SendString("> ");
            } else if (rx_index < RX_BUFFER_SIZE - 1) {
                rx_line[rx_index++] = rx_char;
            }
        }
    }
}

static void MX_USART1_UART_Init(void) {
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 9600;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    HAL_UART_Init(&huart1);
}

void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}
