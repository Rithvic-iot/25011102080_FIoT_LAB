#include "main.h"
#include <string.h>

UART_HandleTypeDef huart2;

void send_cmd(char *c) {
    HAL_UART_Transmit(&huart2, (uint8_t*)c, strlen(c), 500);
    HAL_Delay(200);
}

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART2_UART_Init();
    
    send_cmd("AT\r\n");
    send_cmd("AT+CWMODE=1\r\n");
    send_cmd("AT+CIPMUX=1\r\n");
    send_cmd("AT+CIPSERVER=1,80\r\n");
    
    uint8_t buf[128];
    while (1) {
        if (HAL_UART_Receive(&huart2, buf, sizeof(buf)-1, 100) == HAL_OK) {
            if (strstr((char*)buf, "/led/on")) {
                HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
            } else if (strstr((char*)buf, "/led/off")) {
                HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
            }
        }
    }
}
