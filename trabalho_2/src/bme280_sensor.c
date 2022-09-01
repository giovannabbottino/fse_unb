#include "bme280_driver.h"
#include "bme280.h"
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h> 
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define FILE_DESCRIPTOR "/dev/i2c-1"


#define BME280_R_SUCCESS    0
#define BME280_R_FAIL       -1


static uint32_t min_req_delay;
static int8_t file_descriptor; 
struct bme280_dev dev;


int32_t init_bme(){

    if((file_descriptor = open(FILE_DESCRIPTOR, O_RDWR)) < 0) return BME280_R_FAIL;
    if(ioctl(file_descriptor, I2C_SLAVE, BME280_I2C_ADDR_PRIM) < 0) return BME280_R_FAIL;

    dev.intf = BME280_I2C_INTF;
    dev.read = user_i2c_read;
    dev.write = user_i2c_write;
    dev.delay_us = user_delay_us;

    //Initialize the bme280
    int8_t result = BME280_OK;
    result = bme280_init(&dev);
    if(result != BME280_OK) return BME280_R_FAIL;

    uint8_t settings_sel = BME280_OSR_PRESS_SEL | BME280_OSR_TEMP_SEL | BME280_OSR_HUM_SEL | BME280_FILTER_SEL;

    //Recommended mode of operation: Indoor navigation
    dev.settings.osr_h = BME280_OVERSAMPLING_1X;
    dev.settings.osr_p = BME280_OVERSAMPLING_16X;
    dev.settings.osr_t = BME280_OVERSAMPLING_2X;
    dev.settings.filter = BME280_FILTER_COEFF_16;

    //Set the sensor settings
    result = bme280_set_sensor_settings(settings_sel, &dev);
    if(result != BME280_OK) return BME280_R_FAIL;

    //Calculate the minimum delay required between consecutive measurement
    min_req_delay = bme280_cal_meas_delay(&dev.settings);

    //Set the sensor to forced mode
    result = bme280_set_sensor_mode(BME280_FORCED_MODE, &dev);
    if(result != BME280_OK) return BME280_R_FAIL;

    return BME280_R_SUCCESS;
}

int8_t user_i2c_read(uint8_t reg_addr, uint8_t *data, uint32_t len, __attribute__((unused)) void *intf_ptr){

    write(file_descriptor, &reg_addr, 1);
    read(file_descriptor, data, len);
    return BME280_R_SUCCESS;
}

int8_t user_i2c_write(uint8_t reg_addr, const uint8_t *data, uint32_t len, __attribute__((unused)) void *intf_ptr){
    
    uint8_t *buffer;

    buffer = malloc(len + 1);
    buffer[0] = reg_addr;
    memcpy(buffer + 1, data, len);

    if(write(file_descriptor, buffer, len+1) < (uint16_t)len) return BME280_R_FAIL;
    
    free(buffer);
    return BME280_R_SUCCESS;
}

void user_delay_us(uint32_t period, __attribute__((unused)) void *intf_ptr){
    usleep(period*1000);
}

int32_t get_temp(double *temperature){

    int8_t result = BME280_OK;
    struct bme280_data data;

    usleep(min_req_delay*1000);
    result = bme280_get_sensor_data(BME280_ALL, &data, &dev);

    *temperature = data.temperature;

    if(result != BME280_OK) return BME280_R_FAIL;

    return BME280_R_SUCCESS;
}

void bme280_driver_close(void){
    close(file_descriptor);
}
