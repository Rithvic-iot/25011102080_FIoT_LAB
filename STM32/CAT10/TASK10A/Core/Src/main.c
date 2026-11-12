#include "main.h"

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART1_UART_Init();
    MX_USART2_UART_Init();
    
    uint8_t b;
    while (1) {
        /* Bridge PC (USART1) <--> ESP8266 (USART2) */
        if (HAL_UART_Receive(&huart1, &b, 1, 1) == HAL_OK) {
            HAL_UART_Transmit(&huart2, &b, 1, 10);
        }
        if (HAL_UART_Receive(&huart2, &b, 1, 1) == HAL_OK) {
            HAL_UART_Transmit(&huart1, &b, 1, 10);
        }
    }
}
