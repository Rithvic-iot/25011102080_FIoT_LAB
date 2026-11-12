#include "main.h"
#include <string.h>

UART_HandleTypeDef huart1;
char rx_buf[64];
uint8_t rx_idx = 0;

void send_str(char *s) {
    HAL_UART_Transmit(&huart1, (uint8_t*)s, strlen(s), 100);
}

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART1_UART_Init();
    
    uint8_t ch;
    while (1) {
        if (HAL_UART_Receive(&huart1, &ch, 1, 10) == HAL_OK) {
            HAL_UART_Transmit(&huart1, &ch, 1, 10);
            if (ch == '\r' || ch == '\n') {
                if (rx_idx > 0) {
                    rx_buf[rx_idx] = '\0';
                    if (strcmp(rx_buf, "LED ON") == 0) {
                        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
                        send_str("\r\n[STM32] LED is turned ON\r\n");
                    } else if (strcmp(rx_buf, "LED OFF") == 0) {
                        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
                        send_str("\r\n[STM32] LED is turned OFF\r\n");
                    } else if (strcmp(rx_buf, "LED TOGGLE") == 0) {
                        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
                        send_str("\r\n[STM32] LED toggled\r\n");
                    } else {
                        send_str("\r\n[ERROR] Unknown command\r\n");
                    }
                    rx_idx = 0;
                }
            } else {
                if (rx_idx < sizeof(rx_buf) - 1) rx_buf[rx_idx++] = ch;
            }
        }
    }
}
