#ifndef BME280_DRIVER_
#define BME280_DRIVER_

#include "bme280.h"
void user_delay_us(uint32_t period, void *intf_ptr);

int8_t user_i2c_read(uint8_t reg_addr, uint8_t *data, uint32_t len, void *intf_ptr);

int8_t user_i2c_write(uint8_t reg_addr, const uint8_t *data, uint32_t len, void *intf_ptr);

int32_t get_temp(double *temp);

int init_bme();

void bme280_driver_close(void);

#endif