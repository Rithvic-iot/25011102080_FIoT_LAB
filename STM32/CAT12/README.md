# EXPERIMENT DETAILS

**EXP:** CONTINUOUS ASSESSMENT 12  

**DATE:** 23/10/2026  

**NAME OF EXP:** BME280 Sensor Interfacing Using I2C and Bosch Sensor API  

**HARDWARE SETUP / PLATFORM:** STMicroelectronics NUCLEO-F401RE Development Board + Bosch Sensortec BME280 Sensor Module + Keil MDK-ARM + STM32CubeMX + PuTTY Serial Terminal  

---

## TASK 12 : BME280 Sensor Interfacing over I2C

### 1. Circuit Diagram

We connected the BME280 combined temperature, relative humidity, and barometric pressure sensor to the Nucleo board over the I2C bus.

- **Board:** NUCLEO-F401RE
- **I2C Bus:** `I2C1` peripheral
  - `PB8` -> BME280 `SCL` (Serial Clock)
  - `PB9` -> BME280 `SDA` (Serial Data)
  - Two 4.7kΩ pull-up resistors connected to +3.3V
- **Sensor Power:** `VCC` connected to +3.3V, `GND` to Ground
- **I2C Address:** `0x76` (with `SDO` pin grounded)
- **UART Output:** `USART2` (`PA2`/`PA3`) sends serial telemetry at 115200 baud to the PC

![Circuit Diagram](circuit.png)

### 2. Bosch Sensor API Integration

Rather than manually reading raw ADC registers and computing 32-bit fixed-point polynomial compensation formulas, we integrated the official Bosch Sensortec `bme280` driver library:

1. **Hardware Wrapper Functions:**
   - `bme280_i2c_read()`: Uses `HAL_I2C_Mem_Read()` to fetch register data.
   - `bme280_i2c_write()`: Uses `HAL_I2C_Mem_Write()` to write configuration registers.
   - `bme280_delay_ms()`: Maps to `HAL_Delay()`.
2. **Sensor Configuration:**
   - Operating Mode: **Normal Mode** (continuous sampling)
   - Temperature Oversampling: x2
   - Pressure Oversampling: x16
   - Humidity Oversampling: x1
   - IIR Filter Coefficient: 16
   - Standby Time: 500 ms

### 3. Sample Output in PuTTY Terminal

```text
========================================
   BME280 Environmental Sensor System
========================================
[INFO] I2C Device detected at 0x76
[INFO] Chip ID = 0x60 (BME280 verified)
[INFO] Calibration parameters loaded.

[DATA] Temp: 26.42 C | Press: 1013.25 hPa | Hum: 58.30 %
[DATA] Temp: 26.45 C | Press: 1013.22 hPa | Hum: 58.24 %
[DATA] Temp: 26.50 C | Press: 1013.28 hPa | Hum: 58.19 %
```

### 4. Inference

The BME280 sensor initialized reliably over I2C1 at address `0x76`. The Bosch Sensor API successfully applied factory calibration trim parameters to produce calibrated, accurate temperature, atmospheric pressure, and humidity readings.
