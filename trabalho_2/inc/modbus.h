#ifndef MODBUS_H_
#define MODBUS_H_

#include "uart.h"
#include "definicoes.h"

void modbus_open();
void modbus_init(Byte address, Byte func_cod, Byte sub_cod);
int modbus_read(Byte *message, Byte message_size);
int modbus_write(const Byte *message, Byte message_size);
void modbus_close();

#endif 
