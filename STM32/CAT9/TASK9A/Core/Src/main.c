#include "main.h"
#include <string.h>

UART_HandleTypeDef huart1;

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART1_UART_Init();
    
    uint8_t ch;
    while (1) {
        if (HAL_UART_Receive(&huart1, &ch, 1, 10) == HAL_OK) {
            HAL_UART_Transmit(&huart1, &ch, 1, 10); /* Echo character */
            if (ch == '\r') {
                uint8_t lf = '\n';
                HAL_UART_Transmit(&huart1, &lf, 1, 10);
            }
        }
    }
}
