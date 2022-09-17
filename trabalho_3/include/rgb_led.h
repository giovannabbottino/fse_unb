#ifndef __RGB_LED_H__
#define __RGB_LED_H__

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

void set_red(char * value);
void set_green(char * value);
void set_blue(char * value);

char * get_rgb_led_state();

#endif
