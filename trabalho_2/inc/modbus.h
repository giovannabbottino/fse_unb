#ifndef MODBUS_H_
#define MODBUS_H_

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "crc16.h"
#include "uart.h"
// Codigos
#define SEND_COD 0x16
#define REQUEST_COD 0x23
#define INT_REQUEST_SUB_COD 0xA1
#define FLOAT_REQUEST_SUB_COD 0xA2
#define STR_REQUEST_SUB_COD 0xA3
#define INT_SEND_SUB_COD 0xB1
#define FLOAT_SEND_SUB_COD 0xB2
#define STR_SEND_SUB_COD 0xB3

// Funções
void modbus_close();
void modbus_config(unsigned char cod, unsigned char sub_cod);
int modbus_receive(unsigned char *message, unsigned char size);
int modbus_send(unsigned char *message, unsigned char size);

#endif 
