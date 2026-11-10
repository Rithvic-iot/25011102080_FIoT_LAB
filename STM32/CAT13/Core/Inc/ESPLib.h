/**
 * @file ESPLib.h
 * @brief Custom ESP8266 MQTT Communication Driver Interface
 */

#ifndef ESPLIB_H_
#define ESPLIB_H_

#include "main.h"

typedef enum {
    StationMode = 1,
    SoftAPMode = 2,
    CombinedMode = 3
} ESP_Mode_t;

typedef enum {
    QoS0 = 0,
    QoS1 = 1,
    QoS2 = 2
} MQTT_QoS_t;

typedef enum {
    CleanSession = 1,
    KeepSession = 0
} MQTT_Session_t;

typedef struct {
    char *clientID;
    uint16_t keepAlive;
    MQTT_Session_t connectFlag;
} MQTT_InitTypeDef_t;

void ESP8266_Init(ESP_Mode_t mode, UART_HandleTypeDef huart);
uint8_t ESP8266_wifiConnect(char *SSID, char *PASS);
uint8_t ESP8266_portConnect(char *protocol, char *host, char *port);
uint8_t MQTT_connectBroker(MQTT_InitTypeDef_t *settings);
uint8_t MQTT_publishTopic(char *topic, char *payload, MQTT_QoS_t qos);
uint8_t MQTT_subscribeTopic(char *topic, uint8_t qos);
void MQTTDataHandler(char *topic, char *data);
void MQTTTimer(void);

#endif
