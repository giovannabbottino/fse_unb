#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_log.h"
#include "led.h"

#define BLINK_GPIO 2
#define TAG "LED"

#define ENERGY_MODE  CONFIG_ESP_ENERGY_MODE

int state_global = 0;

void set_led_state(){
    if (strcmp(ENERGY_MODE, "NORMAL_MODE") == 0){
        state_global = !state_global;
        gpio_pad_select_gpio(BLINK_GPIO);
        gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

        ESP_LOGI(TAG, "LED: %d", state_global);

        gpio_set_level(BLINK_GPIO, state_global);
    }
}

int get_led_state(){
    return state_global;
}
