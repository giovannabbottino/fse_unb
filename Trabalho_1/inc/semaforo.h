#ifndef SEMAFORO_H  
#define SEMAFORO_H

#include <stdio.h>
#include <stdlib.h>

#include <wiringPi.h>
#include <softPwm.h>

#include <unistd.h>

void pwmLigarLed(int led, int frequencia);

void pwmDesligarLed(int led, int frequencia);

void verdeParaVermelho(int * leds, int frequencia);

void ligarLed(int led);

int main(int argc, char *argv[]);

#endif
