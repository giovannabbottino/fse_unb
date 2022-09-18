#include "dht.h"
#include "dht11.h"
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "mqtt.h"
#include "freertos/semphr.h"
#include "driver/adc.h"
#define TAG "DHT11"
#define PIN GPIO_NUM_23

int umidade = 0;
int temperatura = 0;

void setup_dht_11(){
    DHT11_init(PIN);
    ESP_LOGI(TAG, "Pin : %d", PIN);
}

void sensor(){
    temperatura = DHT11_read().temperature;
    ESP_LOGI(TAG, "Temperatura: %d", temperatura);
    umidade = DHT11_read().humidity;
    ESP_LOGI(TAG, "Umidade: %d", umidade);
}

int get_umidade(){
    umidade = DHT11_read().humidity;
    return umidade;
}

int get_temperatura(){
    temperatura = DHT11_read().temperature;
    return temperatura;
}
