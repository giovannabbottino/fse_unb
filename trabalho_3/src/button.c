#include "button.h"
#include "led.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_log.h"

#include "led.h"
#include "rgb_led.h"
#include "mqtt.h"

#define BUTTON_GPIO 0
#define TAG "BUTTON"

extern xSemaphoreHandle conexaoMQTTSemaphore;

int button_state_global = 0;
int button_sensor = 0;

void button_set_state(){
    gpio_pad_select_gpio(BUTTON_GPIO);
    gpio_set_direction(BUTTON_GPIO, GPIO_MODE_INPUT);

    gpio_pulldown_en(BUTTON_GPIO);
    gpio_pullup_dis(BUTTON_GPIO);

    while (1)
    {
        int button_state = gpio_get_level(BUTTON_GPIO);
        if (button_state != button_state_global){
            button_state_global = button_state;
            if (button_state){
                ESP_LOGI(TAG, "BUTTON RELEASED");
            }
            else
            {
                ESP_LOGI(TAG, "BUTTON PRESSED");
                button_sensor = !button_sensor;
            }
            xSemaphoreGive(conexaoMQTTSemaphore);
        }
        if (button_sensor){
            ESP_LOGI(TAG, "BUTTON SENSOR %d", button_sensor);

            char JsonAttributes[500];
            sprintf(JsonAttributes, "{\"statusLed\": %d, \"RED\": %d, \"GREEN\": %d, \"BLUE\": %d}", 
                    led_get_state(), 
                    rgb_led_get_red(), 
                    rgb_led_get_green(), 
                    rgb_led_get_blue());
            mqtt_envia_mensagem("v1/devices/me/attributes",JsonAttributes);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
        vTaskDelay(150 / portTICK_PERIOD_MS);
    }

}

