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

xSemaphoreHandle conexaoWifiSemaphore;
xSemaphoreHandle conexaoMQTTSemaphore;

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
      sprintf(mensagem, "{\"temperatura\": %d}", get_temperatura());
      mqtt_envia_mensagem("v1/devices/me/telemetry", mensagem);

      sprintf(JsonAttributes, "{\"umidade\":%d,\"statusLed\": %d}", get_umidade(), get_led_state());
      mqtt_envia_mensagem("v1/devices/me/attributes",JsonAttributes);
      vTaskDelay(1000 / portTICK_PERIOD_MS);
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
    
    conexaoWifiSemaphore = xSemaphoreCreateBinary();
    conexaoMQTTSemaphore = xSemaphoreCreateBinary();

    wifi_start();

    xTaskCreate(&conectadoWifi,  "Conexão ao MQTT", 4096, NULL, 1, NULL);
    xTaskCreate(&trataComunicacaoComServidor, "Comunicação com Broker", 4096, NULL, 1, NULL);
    xTaskCreate(&set_button_state, "Botão ESP", 4096, NULL, 1, NULL);
}
