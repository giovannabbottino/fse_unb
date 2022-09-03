#ifndef HANDLER_H
#define HANDLER_H

#include <stdio.h>
#include <stdlib.h>

#include "bme280_driver.h"
#include "pid.h"
#include "temperatura.h"
#include "lcd_16x2_driver.h"
#include "esp32.h"

void uartHandler();
void terminalHandler(float tr);

#endif
