#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_log.h"
#include "driver/ledc.h"
#include "rgb_led.h"

#define BLINK_GPIO 2
#define TAG "LED"

bool g_pwm_init_handle = false;
int red = 0;
int green = 0;
int blue = 0;

static void rgb_led_pwm_init(void){
    int rgb_ch;
    //Red
    ledc_ch[0].channel      = LEDC_CHANNEL_0;
    ledc_ch[0].gpio         = RGB_LED_RED_GPIO;
    ledc_ch[0].mode         = LEDC_HIGH_SPEED_MODE;
    ledc_ch[0].timer_index  = LEDC_TIMER_0;
    //Green
    ledc_ch[1].channel      = LEDC_CHANNEL_1;
    ledc_ch[1].gpio         = RGB_LED_GREEN_GPIO;
    ledc_ch[1].mode         = LEDC_HIGH_SPEED_MODE;
    ledc_ch[1].timer_index  = LEDC_TIMER_0;
    //Blue
    ledc_ch[2].channel      = LEDC_CHANNEL_2;
    ledc_ch[2].gpio         = RGB_LED_BLUE_GPIO;
    ledc_ch[2].mode         = LEDC_HIGH_SPEED_MODE;
    ledc_ch[2].timer_index  = LEDC_TIMER_0;

    //Configure timer 0
	ledc_timer_config_t ledc_timer = {
		.duty_resolution    = LEDC_TIMER_8_BIT,
		.freq_hz            = 100,
		.speed_mode         = LEDC_HIGH_SPEED_MODE,
		.timer_num          = LEDC_TIMER_0
	};
	ledc_timer_config(&ledc_timer);

    //Configure channels
    for (int rgb_ch = 0; rgb_ch < RGB_LED_CHANNEL_NUM; rgb_ch++){
		ledc_channel_config_t ledc_channel = {
			.channel    = ledc_ch[rgb_ch].channel,
			.duty       = 0,
			.hpoint     = 0,
			.gpio_num   = ledc_ch[rgb_ch].gpio,
			.intr_type  = LEDC_INTR_DISABLE,
			.speed_mode = ledc_ch[rgb_ch].mode,
			.timer_sel  = ledc_ch[rgb_ch].timer_index,
		};
		ledc_channel_config(&ledc_channel);
	}
    ledc_set_duty(ledc_ch[0].mode, ledc_ch[0].channel, red);
	ledc_update_duty(ledc_ch[0].mode, ledc_ch[0].channel);

    ledc_set_duty(ledc_ch[0].mode, ledc_ch[0].channel, green);
	ledc_update_duty(ledc_ch[0].mode, ledc_ch[0].channel);

    ledc_set_duty(ledc_ch[0].mode, ledc_ch[0].channel, blue);
	ledc_update_duty(ledc_ch[0].mode, ledc_ch[0].channel);

    g_pwm_init_handle = true;
}



void set_red(char * value){
    red = atoi(value);
    if(!g_pwm_init_handle){
        rgb_led_pwm_init
    }
    ledc_set_duty(ledc_ch[0].mode, ledc_ch[0].channel, red);
	ledc_update_duty(ledc_ch[0].mode, ledc_ch[0].channel);
}
void set_green(char * value){
    green = atoi(value);
    if(!g_pwm_init_handle){
        rgb_led_pwm_init
    }
    ledc_set_duty(ledc_ch[0].mode, ledc_ch[0].channel, green);
	ledc_update_duty(ledc_ch[0].mode, ledc_ch[0].channel);

}
void set_blue(char * value){
    blue = atoi(value);
    if(!g_pwm_init_handle){
        rgb_led_pwm_init
    }
    ledc_set_duty(ledc_ch[0].mode, ledc_ch[0].channel, blue);
	ledc_update_duty(ledc_ch[0].mode, ledc_ch[0].channel);
}

char * get_rgb_led_state(){
    char * state;
    strcat(state, "R: ");
    strcat(state, itoa(red));
    strcat(state, " G: ");
    strcat(state, itoa(green));
    strcat(state, " B: ");
    strcat(state, itoa(blue));
    strcat(state, "\n ");
    return state;
}