#ifndef __RGB_LED_H__
#define __RGB_LED_H__
#include <stdint.h>
// RGB LED GPIOs
#define RGB_LED_RED_GPIO    14
#define RGB_LED_GREEN_GPIO  12
#define RGB_LED_BLUE_GPIO   13

// RGB LED CHANNEL
#define RGB_LED_CHANNEL_NUM 3

typedef struct
{
	int channel;
	int gpio;
	int mode;
	int timer_index;
}ledc_info_t;

ledc_info_t ledc_ch[RGB_LED_CHANNEL_NUM];

void rgb_led_set_red(uint8_t value);
void rgb_led_set_green(uint8_t value);
void rgb_led_set_blue(uint8_t value);

int rgb_led_get_red();
int rgb_led_get_green();
int rgb_led_get_blue();

#endif
