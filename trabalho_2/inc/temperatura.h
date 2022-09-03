#ifndef TEMPERATURA_H_
#define TEMPERATURE_H_

#include <wiringPi.h>
#include <stdio.h>
#include <softPwm.h>

#define RESISTOR 4
#define COOLER 5

void inicia_temperatura();
void muda_temperatura(double temperatura);
void desliga();

#endif