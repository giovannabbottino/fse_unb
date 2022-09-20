#include "handler.h"
#include <stdio.h>
#include <string.h>
#include "esp_log.h"
#include "cJSON.h"
#include "mqtt.h"

#define TAG "HANDLER"

void handler_event_data(char * data){
    cJSON *json = cJSON_Parse(data);
    cJSON *method = cJSON_GetObjectItem(json, "method");
    char method_value[20];
    strcpy(method_value, method->valuestring);
    ESP_LOGI(TAG, "method: %s", method_value);

    cJSON *params = cJSON_GetObjectItem(json, "params");
    int params_value = params->valueint;
    ESP_LOGI(TAG, "params: %d", params_value);

    if (strcmp(method_value, "ligaLed") == 0){
        /* {"method":"ligaLed","params":1-100} */
        led_set_state(params_value);
    }else if (strcmp(method_value, "redValue") == 0){
         /* {"method":"redValue","params":"0-255"} */
        rgb_led_set_red(params_value);
    }else if (strcmp(method_value, "greenValue") == 0){
        /* {"method":"greenValue","params":"0-255"} */
        rgb_led_set_green(params_value);
    }else if (strcmp(method_value, "blueValue") == 0){
        /* {"method":"blueValue","params":"0-255"} */
        rgb_led_set_blue(params_value);
    }else if (strcmp(method_value, "getValue") == 0){
        /* {"method":"getValue","params":""} */
        char JsonAttributes[500];
        sprintf(JsonAttributes, "{\"statusLed\": %d, \"RED\": %d, \"GREEN\": %d, \"BLUE\": %d}", led_get_state(), rgb_led_get_red(), rgb_led_get_green(), rgb_led_get_blue());
        mqtt_envia_mensagem("v1/devices/me/attributes",JsonAttributes);
    }
}
