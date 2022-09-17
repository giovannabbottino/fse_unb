#include "handler.h"
#include "string.h"

void handler_event_data(char * method_value,char * params){
    if (strcmp(method_value, "ligaLed") == 0){
        /* {"method":"ligaLed","params":"true"} */
        set_led_state();
    }else if (strcmp(method_value, "redValue") == 0){
         /* {"method":"redValue","params":"0-255"} */
        set_red(params);
    }else if (strcmp(method_value, "greenValue") == 0){
        /* {"method":"ligaLed","params":"0-255"} */
        set_green(params);
    }else if (strcmp(method_value, "blueValue") == 0){
        /* {"method":"ligaLed","params":"0-255"} */
        set_blue(params);
    }

}