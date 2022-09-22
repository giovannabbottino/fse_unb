#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "sdkconfig.h"
#include "esp_log.h"
#include "led.h"
#include <stdbool.h>
#include "mqtt.h"

#define TAG "LED"

#include "memoria.h"

extern struct memoria *data;

bool g_setup_led = false;

static void led_setup(void){
    // Configuração do Timer
    ledc_timer_config_t timer_config = {
    .speed_mode = LEDC_LOW_SPEED_MODE,
    .duty_resolution = LEDC_TIMER_8_BIT,
    .timer_num = LEDC_TIMER_0,
    .freq_hz = 1000,
    .clk_cfg = LEDC_AUTO_CLK
    };
    ledc_timer_config(&timer_config);

    // Configuração do Canal
    ledc_channel_config_t channel_config = {
    .gpio_num = 2,
    .speed_mode = LEDC_LOW_SPEED_MODE,
    .channel = LEDC_CHANNEL_0,
    .timer_sel = LEDC_TIMER_0,
    .duty = 0,
    .hpoint = 0
    };
    ledc_channel_config(&channel_config);
    g_setup_led = true;
}

void led_set_state(int state){
    state = 2.55 * state;
    if(!g_setup_led){
        led_setup();
    }
    ESP_LOGI(TAG, "LED: %d", state);

    if (state > data->led){
        for (int i = data->led; i < state; i++){
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, i);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
            vTaskDelay(10 / portTICK_PERIOD_MS);
        }
    } else {
        for (int i = data->led; i >= state; i--){ 
         ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, i); 
         ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
         vTaskDelay(10 / portTICK_PERIOD_MS);
        }
    }
    data->led = state;
    led_envia_menssagem();
}

void led_envia_menssagem(){
    char JsonAttributes[500];
    
    sprintf(JsonAttributes, "{\"statusLed\": %d}", led_get_state());
    mqtt_envia_mensagem("v1/devices/me/attributes",JsonAttributes);
}

int led_get_state(){
    return data->led > 0;
}
