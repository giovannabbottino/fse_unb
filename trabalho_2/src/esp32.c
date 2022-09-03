#include "esp32.h"

float get_TI(){
    modbus_config(GET_DATA, 0xc1);
    modbus_send(NULL, 0);
    unsigned char message[255];

    int size = modbus_receive(message, 254);
    size += 0;
    float temp = *(float *) &message[3];

    modbus_close();
    return temp;
}
int get_comando(){

    modbus_config(GET_DATA, 0xc3);
    modbus_send(NULL, 0);
    unsigned char message[255];

    int size = modbus_receive(message, 254);
    size += 0;
    if(message[3] == 0x01){
        printf("Comando: LIGAR\n");
        modbus_close();
        send_system_status(1);
        return 1;
    }
    else if(message[3] == 0x02 ){
        printf("Comando: DESLIGAR\n");
        modbus_close();
        send_system_status(0);
        return 2;
    }
    else if(message[3] == 0x03){
        printf("Comando: INICIA AQUECIMENTO\n");
        return 3;
    }
    else if(message[3] == 0x04){
        printf("Comando: CANCELA\n");
        return 4;
    }
    else if(message[3] == 0x05){
        printf("Comando: TEMPO +\n");
        return 5;
    }
    else if(message[3] == 0x06){
        printf("Comando: MENU\n");
        return 6;
    }
    return 0;
}

void send_int(int control_signal){

    modbus_config(SEND_DATA, 0xd1);
    unsigned char message[255];
    memcpy(message, &control_signal, sizeof(int));

    modbus_send(message, 4);
    modbus_close();
}

void send_float(float control_signal){

    modbus_config(SEND_DATA, 0xd2);
    unsigned char message[255];
    memcpy(message, &control_signal, sizeof(float));

    modbus_send(message, 4);
    modbus_close();
}
