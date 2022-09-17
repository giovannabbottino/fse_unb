#include "handler.h"
#include "string.h"

void handler_event_data(char * method_value,char * params){
    if (strcmp(method_value, "ligaLed") == 0){
        /* {"method":"ligaLed","params":"true"} */
        set_led_state();
    }

    

}