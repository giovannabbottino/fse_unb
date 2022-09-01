#include "modbus.h"
#include "crc16.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static Byte device_address_cod = 0x00;
static Byte function_cod = 0x00;
static Byte sub_cod = 0x00;
static const Byte matricula[] = {1, 2, 6, 7}; // 170011267

static unsigned int timeout_microsecond = 10000;
static Byte timeout_time = 15;


void modbus_open(){
    uart_init();
}

void modbus_init(Byte device_address_cod_, Byte function_cod_, Byte sub_cod_){
    device_address_cod = device_address_cod_;
    function_cod = function_cod_;
    sub_cod = sub_cod_;
}

int modbus_read(Byte *message, Byte message_size){

    int size = 0;
    unsigned int timeout = timeout_time;

    size = uart_read(message, message_size);
    while(size <= 0 && timeout != 0){
        usleep(timeout_microsecond);
        size = uart_read(message, message_size);
        timeout--;
    }

    if(size <= 0) return size;

    unsigned short crc;
    int length = size - sizeof(short);
    memcpy(&crc, &message[length], sizeof(short));
    unsigned short expected_crc = calculate_crc(message, length);

    if(expected_crc == crc)
        return size;
    return -1;
}

int modbus_write(const Byte *message, Byte message_size){
    
    Byte index = 0;
    Byte size = 7 * sizeof(Byte) + message_size + sizeof(short);
    Byte *buffer = malloc(size);

    memcpy(&buffer[index++], &device_address_cod, sizeof(Byte));
    memcpy(&buffer[index++], &function_cod, sizeof(Byte));
    memcpy(&buffer[index++], &sub_cod, sizeof(Byte));
    
    memcpy(&buffer[index], matricula, sizeof(matricula));
    index += sizeof(matricula);

    if(message != NULL){
        memcpy(&buffer[index], message, message_size);
        index += message_size;
    }

    unsigned short crc = calculate_crc(buffer, index);
    memcpy(&buffer[index], &crc, sizeof(short));
    index += sizeof(short);

    size = uart_write(buffer, index);
    free(buffer);

    return size;
}

void modbus_close(){
    uart_close();
}
