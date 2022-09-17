#include "button.h"
#include "led.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_log.h"
#include "mqtt.h"


#define BUTTON_GPIO 0
#define TAG "BUTTON"

extern xSemaphoreHandle conexaoMQTTSemaphore;

int button_state_global = 0;

void set_button_state(){
    gpio_pad_select_gpio(BUTTON_GPIO);
    gpio_set_direction(BUTTON_GPIO, GPIO_MODE_INPUT);

    gpio_pulldown_en(BUTTON_GPIO);
    gpio_pullup_dis(BUTTON_GPIO);

    while (1)
    {
        int button_state = gpio_get_level(BUTTON_GPIO);
        if (button_state != button_state_global && xSemaphoreTake(conexaoMQTTSemaphore, portMAX_DELAY)){
            button_state_global = button_state;
            if (button_state){
                ESP_LOGI(TAG, "BUTTON RELEASED");
            }
            else
            {
                ESP_LOGI(TAG, "BUTTON PRESSED");
                set_led_state();

            }
            xSemaphoreGive(conexaoMQTTSemaphore);
        }
        vTaskDelay(150 / portTICK_PERIOD_MS);
    }

}

