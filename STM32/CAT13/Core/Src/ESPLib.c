/**
 * @file ESPLib.c
 * @brief Implementation of ESP8266 AT-based MQTT Client Driver
 */

#include "ESPLib.h"
#include <string.h>
#include <stdio.h>

static UART_HandleTypeDef esp_huart;
static volatile uint32_t mqtt_timer_tick = 0;

void ESP8266_Init(ESP_Mode_t mode, UART_HandleTypeDef huart) {
    esp_huart = huart;
    char cmd[32];
    HAL_UART_Transmit(&esp_huart, (uint8_t *)"AT\r\n", 4, 500);
    HAL_Delay(300);
    sprintf(cmd, "AT+CWMODE=%d\r\n", mode);
    HAL_UART_Transmit(&esp_huart, (uint8_t *)cmd, strlen(cmd), 500);
    HAL_Delay(300);
}

uint8_t ESP8266_wifiConnect(char *SSID, char *PASS) {
    char cmd[128];
    sprintf(cmd, "AT+CWJAP=\"%s\",\"%s\"\r\n", SSID, PASS);
    HAL_UART_Transmit(&esp_huart, (uint8_t *)cmd, strlen(cmd), HAL_MAX_DELAY);
    HAL_Delay(3000);
    return 1;
}

uint8_t ESP8266_portConnect(char *protocol, char *host, char *port) {
    char cmd[128];
    sprintf(cmd, "AT+CIPSTART=\"%s\",\"%s\",%s\r\n", protocol, host, port);
    HAL_UART_Transmit(&esp_huart, (uint8_t *)cmd, strlen(cmd), HAL_MAX_DELAY);
    HAL_Delay(1500);
    return 1;
}

uint8_t MQTT_connectBroker(MQTT_InitTypeDef_t *settings) {
    char cmd[128];
    sprintf(cmd, "AT+MQTTCONN=\"%s\",%d,%d\r\n", settings->clientID, settings->keepAlive, settings->connectFlag);
    HAL_UART_Transmit(&esp_huart, (uint8_t *)cmd, strlen(cmd), HAL_MAX_DELAY);
    HAL_Delay(1000);
    return 1;
}

uint8_t MQTT_publishTopic(char *topic, char *payload, MQTT_QoS_t qos) {
    char cmd[256];
    sprintf(cmd, "AT+MQTTPUB=\"%s\",\"%s\",%d\r\n", topic, payload, qos);
    HAL_UART_Transmit(&esp_huart, (uint8_t *)cmd, strlen(cmd), HAL_MAX_DELAY);
    return 1;
}

uint8_t MQTT_subscribeTopic(char *topic, uint8_t qos) {
    char cmd[128];
    sprintf(cmd, "AT+MQTTSUB=\"%s\",%d\r\n", topic, qos);
    HAL_UART_Transmit(&esp_huart, (uint8_t *)cmd, strlen(cmd), HAL_MAX_DELAY);
    return 1;
}

void MQTTDataHandler(char *topic, char *data) {
    /* If command received to toggle LED */
    if (strstr(data, "TOGGLE") != NULL) {
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
    }
}

void MQTTTimer(void) {
    mqtt_timer_tick++;
}
