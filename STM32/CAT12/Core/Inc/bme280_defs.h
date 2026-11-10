/**
 * @file bme280_defs.h
 * @brief Bosch Sensortec BME280 Sensor Driver Definitions
 */

#ifndef BME280_DEFS_H_
#define BME280_DEFS_H_

#include <stdint.h>
#include <stddef.h>

#define BME280_OK                   INT8_C(0)
#define BME280_E_NULL_PTR           INT8_C(-1)
#define BME280_E_DEV_NOT_FOUND      INT8_C(-2)
#define BME280_E_INVALID_LEN        INT8_C(-3)
#define BME280_E_COMM_FAIL          INT8_C(-4)
#define BME280_E_SLEEP_MODE_FAIL    INT8_C(-5)
#define BME280_E_NVM_COPY_FAILED    INT8_C(-6)

#define BME280_I2C_ADDR_PRIM        UINT8_C(0x76)
#define BME280_I2C_ADDR_SEC         UINT8_C(0x77)
#define BME280_I2C_INTF             1

#define BME280_CHIP_ID_ADDR         UINT8_C(0xD0)
#define BME280_RESET_ADDR           UINT8_C(0xE0)
#define BME280_PWR_CTRL_ADDR        UINT8_C(0xF4)
#define BME280_CTRL_HUM_ADDR        UINT8_C(0xF2)
#define BME280_DATA_ADDR            UINT8_C(0xF7)

#define BME280_OVERSAMPLING_1X      UINT8_C(0x01)
#define BME280_OVERSAMPLING_2X      UINT8_C(0x02)
#define BME280_OVERSAMPLING_16X     UINT8_C(0x05)
#define BME280_NORMAL_MODE          UINT8_C(0x03)
#define BME280_STANDBY_TIME_500_MS  UINT8_C(0x04)
#define BME280_FILTER_COEFF_16      UINT8_C(0x04)

typedef int8_t (*bme280_read_fptr_t)(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr);
typedef int8_t (*bme280_write_fptr_t)(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr);
typedef void (*bme280_delay_us_fptr_t)(uint32_t period, void *intf_ptr);

struct bme280_calib_data {
    uint16_t dig_t1; int16_t dig_t2; int16_t dig_t3;
    uint16_t dig_p1; int16_t dig_p2; int16_t dig_p3;
    int16_t dig_p4; int16_t dig_p5; int16_t dig_p6;
    int16_t dig_p7; int16_t dig_p8; int16_t dig_p9;
    uint8_t dig_h1; int16_t dig_h2; uint8_t dig_h3;
    int16_t dig_h4; int16_t dig_h5; int8_t dig_h6;
    int32_t t_fine;
};

struct bme280_settings {
    uint8_t osr_p; uint8_t osr_t; uint8_t osr_h;
    uint8_t filter; uint8_t standby_time;
};

struct bme280_dev {
    uint8_t chip_id;
    void *intf_ptr;
    uint8_t intf;
    bme280_read_fptr_t read;
    bme280_write_fptr_t write;
    bme280_delay_us_fptr_t delay_us;
    struct bme280_calib_data calib_data;
    struct bme280_settings settings;
};

struct bme280_data {
    float temperature;
    float pressure;
    float humidity;
};

#endif
