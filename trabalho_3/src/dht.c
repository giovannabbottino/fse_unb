#include "dht.h"
#include "dht11.h"
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "mqtt.h"
#include "freertos/semphr.h"
#include "driver/adc.h"

#include "mqtt.h"

#define TAG "DHT11"
#define PIN GPIO_NUM_23

#include <stdbool.h>

int temperatura;
int umidade;

extern struct memoria *data;
bool g_setup_dht_11 = false;
void dht_11_setup(){
    DHT11_init(PIN);
    ESP_LOGI(TAG, "Pin : %d", PIN);
    g_setup_dht_11 = true;
}

void dht_11_run(){
    if(!g_setup_dht_11){
        dht_11_setup();
    }
    int nova_temperatura = DHT11_read().temperature;
    ESP_LOGI(TAG, "Temperatura: %d", nova_temperatura);
    int nova_umidade = DHT11_read().humidity;
    ESP_LOGI(TAG, "Umidade: %d", nova_umidade);

    if ( nova_temperatura >= temperatura * 0.8 && nova_umidade >= umidade * 0.8){
        temperatura = nova_temperatura;
        umidade = nova_umidade;
        dth_11_envia_menssagem();
    }
}

void dth_11_envia_menssagem(){
    char mensagem[50];
    char JsonAttributes[500];

    sprintf(mensagem, "{\"temperatura\": %d, \"umidade\":%d}", dht_11_get_temperatura(), dht_11_get_umidade());
    mqtt_envia_mensagem("v1/devices/me/telemetry", mensagem);

    sprintf(JsonAttributes, "{\"umidade\":%d,\"temperatura\":%d,\"statusLed\": %d}", dht_11_get_umidade(), dht_11_get_temperatura(), led_get_state());
    mqtt_envia_mensagem("v1/devices/me/attributes",JsonAttributes);
    vTaskDelay(3000 / portTICK_PERIOD_MS);
}

int dht_11_get_umidade(){
    return umidade;
}

int dht_11_get_temperatura(){
    return temperatura;
}
