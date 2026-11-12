#include "main.h"
#include "ESPLib.h"
#include "bme280.h"

UART_HandleTypeDef huart2;

int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_USART2_UART_Init();
    
    ESP8266_Init(StationMode, huart2);
    ESP8266_wifiConnect("WiFiSSID", "Password");
    ESP8266_portConnect("TCP", "broker.emqx.io", "1883");
    
    while (1) {
        MQTT_Publish("stm32/test/data", "{\"temperature\":25.4,\"humidity\":58.2}");
        HAL_Delay(2000);
    }
}
