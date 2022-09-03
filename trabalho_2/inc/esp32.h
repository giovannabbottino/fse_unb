#ifndef ESP32_H
#define ESP32_H

#include <stdio.h>
#include <string.h>

#include "modbus.h"

#define GET_DATA 0x23
#define SEND_DATA 0x16

float get_TI();
int get_comando();
void send_int();
void send_float(float control_signal);

#endif
