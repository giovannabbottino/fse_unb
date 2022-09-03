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
        modbus_close();
        send_working_status(1);
        return 3;
    }
    else if(message[3] == 0x04){
        printf("Comando: CANCELA\n");
        modbus_close();
        send_working_status(0);
        return 4;
    }
    else if(message[3] == 0x05){
        printf("Comando: TEMPO +\n");
        modbus_close();
        return 5;
    }
    else if(message[3] == 0x06){
        printf("Comando: TEMPO -\n");
        modbus_close();
        return 6;
    }
    else if(message[3] == 0x07){
        printf("Comando: MENU\n");
        modbus_close();
        send_working_status(0);
        return 7;
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

void send_system_status(int control_signal){

    modbus_config(SEND_DATA, 0xd3);
    unsigned char message[255];
    memcpy(message, &control_signal, sizeof(int));

    modbus_send(message, 1);
    int size = modbus_receive(message, 254);
    if(size == -1){
        printf("CRC RECEBIDO INVALIDO\n");
    }

    modbus_close();
}

void send_working_status(int control_signal){

    modbus_config(SEND_DATA, 0xd5);
    unsigned char message[255];
    memcpy(message, &control_signal, sizeof(int));

    modbus_send(message, 1);
    int size = modbus_receive(message, 254);
    if(size == -1){
        printf("CRC RECEBIDO INVALIDO\n");
    }

    modbus_close();
}

void send_time(float control_signal){

    modbus_config(SEND_DATA, 0xd6);
    unsigned char message[255];
    memcpy(message, &control_signal, sizeof(float));

    modbus_send(message, 1);
    int size = modbus_receive(message, 254);
    if(size == -1){
        printf("CRC RECEBIDO INVALIDO\n");
    }

    modbus_close();
}

float get_potenciometro_temp(){

    modbus_config(GET_DATA, 0xc2);
    modbus_send(NULL, 0);
    unsigned char message[255];

    int size = modbus_receive(message, 254);
    size += 0;
    float temp = *(float *) &message[3];

    modbus_close();
    return temp;
}
