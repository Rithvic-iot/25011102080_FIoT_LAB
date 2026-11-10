# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 10  

**DATE:** 05/10/2026 & 12/10/2026 (Weeks 9 & 10)  

**NAME OF EXP:** STM32–Wemos Wi-Fi Modem Interface Using AT Commands & Embedded HTTP Server  

**HARDWARE SETUP / PLATFORM:** STM32 Blue Pill Board (STM32F103C8T6) + Wemos D1 Mini (ESP8266 Wi-Fi Module) + USB-TTL Serial Debugger + Node-RED Local Gateway + Keil MDK-ARM + STM32CubeMX  

---

## TASK 10A : Dual-UART Bridging & AT Commands

### 1. Circuit Diagram

In this experiment, the STM32 acts as a bridge and web server controller connected to the ESP8266 Wi-Fi module.

- **STM32 Blue Pill:**
  - `USART1` (Pins `PA9` TX, `PA10` RX) connected to PC via USB-TTL for debugging output.
  - `USART2` (Pins `PA2` TX, `PA3` RX) connected to Wemos D1 Mini pins `RX` and `TX`.
- **Wemos D1 Mini (ESP8266):** Powered by 3.3V/5V with common ground.
- **LED Indicator:** On-board LED on `PC13` controlled via web requests.

![Circuit Diagram](circuit.png)

### 2. Standard AT Commands Tested

| AT Command | Expected Response | Purpose |
|---|---|---|
| `AT` | `OK` | Checks if ESP8266 modem is alive and responding |
| `AT+CWMODE=1` | `OK` | Sets ESP8266 to Station Mode (client connecting to home/lab Wi-Fi) |
| `AT+CWJAP="SSID","PASS"`| `WIFI CONNECTED
OK` | Connects the module to the local Wi-Fi router |
| `AT+CIFSR` | `+CIFSR:STAIP,"192.168.x.x"`| Retrieves the assigned local IP address |
| `AT+CIPMUX=1` | `OK` | Enables multiple incoming TCP connections |
| `AT+CIPSERVER=1,80` | `OK` | Starts a TCP web server listening on port 80 |

---

## TASK 10B : Embedded HTTP Server & Node-RED Integration

### 1. Working Principle

1. **Incoming Request:** When a web browser or Node-RED makes an HTTP GET request to the ESP8266's IP address on port 80, the modem outputs a serial notification to STM32:  
   `+IPD,<link_id>,<len>:GET /led/on HTTP/1.1...`
2. **STM32 Parsing:** The STM32 reads this stream over USART2. If the path contains `/led/on`, it sets `PC13 = LOW` (LED ON); if it contains `/led/off`, it sets `PC13 = HIGH` (LED OFF).
3. **HTTP Response:** The STM32 sends back a standard HTTP 200 response with a small HTML webpage so the browser displays the updated LED status.
4. **Node-RED Client:** An HTTP Request node in Node-RED sends automated GET requests to control the LED based on dashboard buttons.

### 2. Node-RED Flow Configuration

The included `node_red_http_flow.json` file sets up a simple dashboard:
- An **Inject / Button Node** sends `GET http://<ESP_IP>/led/on`
- A second **Button Node** sends `GET http://<ESP_IP>/led/off`
- A **Debug Node** displays the returned HTML/JSON status.

### 3. Inference

The STM32 successfully initialized the ESP8266 using AT commands, joined the local Wi-Fi network, and ran an embedded web server on port 80. Both the web browser and Node-RED successfully toggled the physical LED over Wi-Fi.
