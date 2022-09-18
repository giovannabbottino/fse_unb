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

#include <nvs_component.h>
#include "memoria.h"
#include <stdbool.h>

extern struct memoria *data;
bool g_setup_dht_11 = false;
void setup_dht_11(){
    DHT11_init(PIN);
    ESP_LOGI(TAG, "Pin : %d", PIN);
    g_setup_dht_11 = true;
}

void sensor(){
    if(!g_setup_dht_11){
        setup_dht_11();
    }
    data->temperatura = DHT11_read().temperature;
    ESP_LOGI(TAG, "Temperatura: %d", data->temperatura);
    data->umidade = DHT11_read().humidity;
    ESP_LOGI(TAG, "Umidade: %d", data->umidade);
}

int get_umidade(){
    return data->umidade;
}

int get_temperatura(){
    return data->temperatura;
}
