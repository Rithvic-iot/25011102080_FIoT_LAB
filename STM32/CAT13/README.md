# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 13  

**DATE:** 27/10/2026  

**NAME OF EXP:** BME280 Sensor Interfacing Using I2C and MQTT with Custom Built ESP8266 API  

**HARDWARE SETUP / PLATFORM:** STMicroelectronics NUCLEO-F401RE Board + Bosch BME280 Sensor + Wemos D1 Mini (ESP8266 Wi-Fi Module) + Cloud MQTT Broker (`broker.emqx.io:1883`) + Node-RED Dashboard  

---

## TASK 13A & 13B : Custom ESP8266 MQTT Driver & Cloud Telemetry

### 1. Circuit Diagram

This end-to-end IoT system collects environmental data, sends it over I2C to the STM32, transmits it via UART to an ESP8266 modem, and publishes it to a public cloud MQTT broker for real-time visualization on a Node-RED dashboard.

- **Microcontroller:** STM32 Nucleo-F401RE
- **BME280 Sensor:** Connected to `I2C1` (`PB8` SCL, `PB9` SDA)
- **Wemos D1 Mini (ESP8266):** Connected to `USART1` (`PA9` TX, `PA10` RX)
- **PC Debug Port:** `USART2` via ST-LINK VCP (115200 baud)
- **MQTT Cloud Broker:** `broker.emqx.io` on TCP port `1883`

![Circuit Diagram](circuit.png)

### 2. Custom MQTT Driver (`ESPLib`)

We developed a lightweight Embedded C library (`ESPLib.c` / `ESPLib.h`) that wraps MQTT protocol packets inside standard ESP8266 TCP connections:

1. **`ESP_Init()`**: Initializes the serial port and tests modem communication (`AT`).
2. **`ESP_ConnectWiFi(ssid, pass)`**: Connects to the local Wi-Fi network.
3. **`MQTT_Connect(broker, port, client_id)`**: Opens a TCP connection to port 1883 and transmits an MQTT CONNECT control packet.
4. **`MQTT_Publish(topic, payload)`**: Encapsulates data into an MQTT PUBLISH packet (QoS 0) and transmits it over the TCP socket.
5. **`MQTT_Subscribe(topic)`**: Sends an MQTT SUBSCRIBE packet to listen for incoming actuator commands.

---

## TASK 13C : Node-RED Live Dashboard

### 1. Topics Used

- **Telemetry Topic (Publish):** `stm32/test/data`  
  Payload format: `{"temperature": 26.4, "humidity": 58.2, "pressure": 1013.2}`
- **Actuator Command Topic (Subscribe):** `stm32/control`  
  Payload: `"1"` (turns Nucleo LED ON) or `"0"` (turns Nucleo LED OFF)

### 2. Node-RED Flow Layout

The file `node_red_mqtt_dashboard.json` contains the complete dashboard flow:
- An **MQTT In node** connected to `broker.emqx.io:1883` listening on `stm32/test/data`.
- A **JSON parser node** that breaks the payload into temperature and humidity values.
- A **Radial Gauge** displaying real-time Temperature (°C).
- A **Linear Level Gauge** displaying Humidity (%).
- A **Historical Chart** tracking environmental trends over time.
- A **UI Switch toggle** publishing to `stm32/control` to turn the physical Nucleo LED on or off from the dashboard.

### 3. Inference

The complete end-to-end IoT pipeline worked as intended. The STM32 successfully sampled the BME280 sensor over I2C, formatted the readings into JSON, and published them to the EMQX MQTT cloud broker through the ESP8266 modem. The Node-RED dashboard displayed live sensor charts and controlled the Nucleo's on-board LED remotely with minimal latency.
