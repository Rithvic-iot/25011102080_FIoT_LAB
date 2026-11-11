/*
 * ============================================================================
 * Experiment: CAT 10 (Weeks 9 & 10)
 * Title: STM32-Wemos Wi-Fi Modem Interface Using AT Commands & HTTP Server
 * Platform: STM32 Blue Pill (STM32F103C8T6 ARM Cortex-M3)
 * Modems: Wemos D1 Mini / ESP8266 (USART2: PA2 TX, PA3 RX)
 * Debug: PC PuTTY Terminal (USART1: PA9 TX, PA10 RX)
 * Description:
 *   - Task 10A & 10B: Dual-UART bridge & AT command exploration
 *   - Task 10C: Multi-connection TCP server on port 80 (AT+CIPSERVER=1,80)
 *   - Task 10D: Parse +IPD incoming HTTP request & transmit HTML payload
 *   - Task 10E: Node-RED HTTP client integration
 * ============================================================================
 */

#include "main.h"
#include <string.h>
#include <stdio.h>

UART_HandleTypeDef huart1; /* PC Debug */
UART_HandleTypeDef huart2; /* Wemos ESP8266 */

#define BUF_LEN 256
char esp_rx_buf[BUF_LEN];
uint8_t esp_rx_idx = 0;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);

void Debug_Print(char *msg) {
    HAL_UART_Transmit(&huart1, (uint8_t *)msg, strlen(msg), HAL_MAX_DELAY);
}

void ESP_SendCommand(char *cmd, uint32_t delay_ms) {
    Debug_Print("STM32 -> ESP: ");
    Debug_Print(cmd);
    HAL_UART_Transmit(&huart2, (uint8_t *)cmd, strlen(cmd), HAL_MAX_DELAY);
    HAL_Delay(delay_ms);
}

void Handle_HTTP_Client(int link_id) {
    char http_body[] = "<html><head><title>STM32 IoT Node</title></head>"
                       "<body><h1>STM32 + Wemos Wi-Fi HTTP Server</h1>"
                       "<p>Device Status: <b>Online</b></p>"
                       "<p>Telemetry: Temperature = 24.5 C, Humidity = 58%</p>"
                       "</body></html>";
    char http_resp[384];
    char send_cmd[32];
    int body_len = strlen(http_body);
    int total_len;

    sprintf(http_resp,
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: %d\r\n"
            "Connection: close\r\n"
            "\r\n"
            "%s", body_len, http_body);

    total_len = strlen(http_resp);

    /* Step 1: Send CIPSEND command */
    sprintf(send_cmd, "AT+CIPSEND=%d,%d\r\n", link_id, total_len);
    HAL_UART_Transmit(&huart2, (uint8_t *)send_cmd, strlen(send_cmd), HAL_MAX_DELAY);
    HAL_Delay(100);

    /* Step 2: Send HTTP response body */
    HAL_UART_Transmit(&huart2, (uint8_t *)http_resp, total_len, HAL_MAX_DELAY);
    HAL_Delay(200);

    /* Close TCP connection */
    sprintf(send_cmd, "AT+CIPCLOSE=%d\r\n", link_id);
    HAL_UART_Transmit(&huart2, (uint8_t *)send_cmd, strlen(send_cmd), HAL_MAX_DELAY);
    Debug_Print("HTTP Response Transmitted & Connection Closed.\r\n");
}

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART1_UART_Init();
    MX_USART2_UART_Init();

    Debug_Print("\r\n=== STM32 - Wemos ESP8266 HTTP Server Bring-Up ===\r\n");

    /* Initialize Wi-Fi modem */
    ESP_SendCommand("AT\r\n", 500);
    ESP_SendCommand("AT+CWMODE=1\r\n", 500);               /* Station Mode */
    ESP_SendCommand("AT+CIPMUX=1\r\n", 500);               /* Enable Multi-connection */
    ESP_SendCommand("AT+CIPSERVER=1,80\r\n", 1000);        /* Start TCP Server on Port 80 */
    ESP_SendCommand("AT+CIFSR\r\n", 1000);                 /* Query IP address */

    Debug_Print("Server running. Waiting for HTTP requests on Port 80...\r\n");

    while (1) {
        char ch;
        if (HAL_UART_Receive(&huart2, (uint8_t *)&ch, 1, 10) == HAL_OK) {
            HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 10); /* Mirror to debug */

            if (ch == '\n' || esp_rx_idx >= BUF_LEN - 1) {
                esp_rx_buf[esp_rx_idx] = '\0';
                
                /* Detect incoming HTTP request frame: +IPD,<id>,<len>:GET / HTTP/1.1 */
                if (strstr(esp_rx_buf, "+IPD") != NULL) {
                    int link_id = 0;
                    sscanf(esp_rx_buf, "+IPD,%d", &link_id);
                    Handle_HTTP_Client(link_id);
                }
                esp_rx_idx = 0;
            } else {
                esp_rx_buf[esp_rx_idx++] = ch;
            }
        }
    }
}

static void MX_USART1_UART_Init(void) {
    huart1.Instance = USART1;
    huart1.Init.BaudRate = 115200;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    HAL_UART_Init(&huart1);
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
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
}
