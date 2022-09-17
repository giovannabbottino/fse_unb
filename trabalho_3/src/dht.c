#include "dht.h"
#include <dht11.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "mqtt.h"

#define TAG "DHT11"

float umidade = 0.0;
float temperatura = 0.0;

void setup_dht_11(){
    DHT11_init(GPIO_NUM_32);
    ESP_LOGI(TAG, "Pin : %d", GPIO_NUM_15);
    xTaskCreate(&sensor, "Sensor de temperatura e umidade", 4096, NULL, 1, NULL);
}

void sensor(){
    while(true){
        temperatura = DHT11_read().temperature;
        ESP_LOGI(TAG, "Temperatura: %.2f", temperatura);
        umidade = DHT11_read().humidity;
        ESP_LOGI(TAG, "Umidade: %.2f", umidade);

        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

float get_umidade(){
    return umidade;
}

float get_temperatura(){
    return temperatura;
}
