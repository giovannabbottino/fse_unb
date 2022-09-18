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
#include "dht.h"
#include "led.h"


#define BUTTON_GPIO 0
#define TAG "BUTTON"

#include <nvs_component.h>
#include "memoria.h"

extern struct memoria *data;

extern xSemaphoreHandle conexaoMQTTSemaphore;

int button_state_global = 0;
int button_sensor = 0;

void set_button_state(){
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
                set_led_state();
                button_sensor = !button_sensor;
            }
            xSemaphoreGive(conexaoMQTTSemaphore);
        }
        if (button_sensor){
            char mensagem[50];
            char JsonAttributes[500];
            ESP_LOGI(TAG, "BUTTON SENSOR %d", button_sensor);
            sensor();
            sprintf(mensagem, "{\"temperatura\": %d, \"umidade\":%d}", get_temperatura(), get_umidade());
            mqtt_envia_mensagem("v1/devices/me/telemetry", mensagem);

            sprintf(JsonAttributes, "{\"umidade\":%d,\"temperatura\":%d,\"statusLed\": %d}", get_umidade(), get_temperatura(), get_led_state());
            mqtt_envia_mensagem("v1/devices/me/attributes",JsonAttributes);
            vTaskDelay(3000 / portTICK_PERIOD_MS);
        }
        vTaskDelay(150 / portTICK_PERIOD_MS);
    }

}

