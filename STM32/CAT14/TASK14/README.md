# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 14  

**DATE:** 27/10/2026  

**NAME OF EXP:** Node-RED Cloud Analytics Dashboard & Remote Actuation  

**HARDWARE SETUP / PLATFORM:** STM32 NUCLEO-F401RE + ESP8266 + Node-RED Dashboard + Cloud MQTT Broker  

---

## TASK 14 : Node-RED Cloud Analytics Dashboard & Remote Actuator Control

### 1. Circuit Diagram

Cloud MQTT broker broker.emqx.io:1883; Node-RED UI dashboard; Nucleo LD2 on PA5.

![Circuit Diagram](circuit.png)

### 2. Core Logic / Pseudocode / Code Base

**Working Principle:**
Node-RED subscribes to telemetry topic stm32/test/data to display radial gauges and charts, and publishes to stm32/control to actuate LD2.

**Pseudocode:**
1. Node-RED displays live gauges from MQTT telemetry.
2. User UI switch publishes command to stm32/control.
3. STM32 acts on command and toggles LED.

**Code Base (`main.c`):**
```c
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

```

### 3. Inference

The end-to-end IoT cloud pipeline demonstrated live data visualization and two-way actuation.
