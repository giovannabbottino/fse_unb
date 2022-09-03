#ifndef ESP32_H_
#define ESP32_H_

#include <stdio.h>
#include <string.h>

#include "modbus.h"

#define GET_DATA 0x23
#define SEND_DATA 0x16

float get_TI();
int get_comando();
void send_int();
void send_float(float control_signal);
void send_system_status(int status);
void send_working_status(int control_signal);
void send_time(float control_signal);
float get_potenciometro_temp();

#endif
