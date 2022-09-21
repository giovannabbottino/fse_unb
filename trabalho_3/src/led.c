#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_log.h"
#include "driver/ledc.h"
#include "led.h"
#include "esp_log.h"


#define TAG "LED"

#include "memoria.h"

extern struct memoria *data;

bool g_setup_led = false;
void led_setup(){

    //Configure timer 0
    ledc_timer_config_t ledc_timer = {
        .duty_resolution    = LEDC_TIMER_8_BIT,
        .freq_hz            = 100,
        .speed_mode         = LEDC_HIGH_SPEED_MODE,
        .timer_num          = LEDC_TIMER_0
    };
    ledc_timer_config(&ledc_timer);

    //Configure channels
    ledc_channel_config_t ledc_channel = {
        .channel    = LEDC_CHANNEL_0,
        .duty       = 0,
        .hpoint     = 0,
        .gpio_num   = 2,
        .intr_type  = LEDC_INTR_DISABLE,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .timer_sel  = LEDC_TIMER_0
    };
    ledc_channel_config(&ledc_channel);
    ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, data->led);
    ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);

    g_setup_led = true;
}

void led_set_state(int state){
    if(!g_setup_led){
        led_setup();
    }
    ESP_LOGI(TAG, "LED: %d", state);

    if (state <= data.led){
        for (int i = data.led; i < state; i++){
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, i);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
            vTaskDelay(10 / portTICK_PERIOD_MS);
        }
    } else {
        for (int i = state; i > data.led; i--){
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, i);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
            vTaskDelay(10 / portTICK_PERIOD_MS);
        }
    }
}

int led_get_state(){
    return data.led;
}
