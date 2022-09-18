#include <stdio.h>
#include <string.h>
#include "nvs_flash.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_http_client.h"
#include "esp_log.h"
#include "freertos/semphr.h"

#include "wifi.h"
#include "http_client.h"

#include "mqtt.h"

#include "led.h"
#include "rgb_led.h"
#include "dht.h"
#include "button.h"

#include <nvs_component.h>
#include "memoria.h"

xSemaphoreHandle conexaoWifiSemaphore;
xSemaphoreHandle conexaoMQTTSemaphore;

struct memoria *data;

void conectadoWifi(void * params)
{
  while(true)
  {
    if(xSemaphoreTake(conexaoWifiSemaphore, portMAX_DELAY))
    {
      // Processamento Internet
      mqtt_start();
    }
  }
}

void trataComunicacaoComServidor(void * params)
{
  char mensagem[50];
  char JsonAttributes[500];
  if(xSemaphoreTake(conexaoMQTTSemaphore, portMAX_DELAY))
  {
    while(true)
    {
      sensor();
      sprintf(mensagem, "{\"temperatura\": %d, \"umidade\":%d}", get_temperatura(), get_umidade());
      mqtt_envia_mensagem("v1/devices/me/telemetry", mensagem);

      sprintf(JsonAttributes, "{\"umidade\":%d,\"temperatura\":%d,\"statusLed\": %d}", get_umidade(), get_temperatura(), get_led_state());
      mqtt_envia_mensagem("v1/devices/me/attributes",JsonAttributes);
      vTaskDelay(3000 / portTICK_PERIOD_MS);
    }
  }
}

void app_main(void)
{
    setup_dht_11();
    // Inicializa o NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    data = malloc(sizeof(data));
    data->temperatura = 0;
    data->umidade = 0;
    data->red = 0;
    data->green = 0;
    data->blue = 0;
    read_struct("DATA", &data, sizeof(data));
    
    conexaoWifiSemaphore = xSemaphoreCreateBinary();
    conexaoMQTTSemaphore = xSemaphoreCreateBinary();

    wifi_start();

    xTaskCreate(&conectadoWifi,  "Conexão ao MQTT", 4096, NULL, 1, NULL);
    xTaskCreate(&trataComunicacaoComServidor, "Comunicação com Broker", 4096, NULL, 1, NULL);
    xTaskCreate(&set_button_state, "Botão ESP", 4096, NULL, 1, NULL);
    // Red: 108 Green: 120 Blue: 109
}
