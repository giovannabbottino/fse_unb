#ifndef HANDLER_H
#define HANDLER_H

#include <stdio.h>
#include <stdlib.h>

#include "bme280_driver.h"
#include "pid.h"
#include "temperatura.h"
#include "lcd_16x2_driver.h"
#include "esp32.h"
#include "menu.h"
#include "csv.h"
#include "tempo.h"

int comando;
float tr;

void desligarHandler();
void userHandler(int comando);
void uartHandler();
void terminalHandler();

#endif
