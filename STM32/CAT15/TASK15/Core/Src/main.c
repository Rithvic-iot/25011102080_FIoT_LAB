#include "main.h"
#include "ESPLib.h"

UART_HandleTypeDef huart2;

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART2_UART_Init();
    
    ESP8266_Init(StationMode, huart2);
    ESP8266_wifiConnect("WiFiSSID", "Password");
    ESP8266_portConnect("TCP", "broker.emqx.io", "1883");
    MQTT_Subscribe("stm32/control");
    
    while (1) {
        /* Check incoming control messages from Node-RED */
    }
}
