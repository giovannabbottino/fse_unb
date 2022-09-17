#include "handler.h"
#include "string.h"

void handler_event_data(char * method_value,char * params){
    uint8_t value;
    if (strcmp(method_value, "ligaLed") == 0){
        /* {"method":"ligaLed","params":"true"} */
        set_led_state();
    }else if (strcmp(method_value, "redValue") == 0){
         /* {"method":"redValue","params":"0-255"} */
        value = atoi(params);
        set_red(value);
    }else if (strcmp(method_value, "greenValue") == 0){
        /* {"method":"ligaLed","params":"0-255"} */
        value = atoi(params);
        set_green(value);
    }else if (strcmp(method_value, "blueValue") == 0){
        /* {"method":"ligaLed","params":"0-255"} */
        value =  atoi(params);
        set_blue(value);
    }

}