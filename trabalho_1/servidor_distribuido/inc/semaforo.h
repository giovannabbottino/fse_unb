#ifndef SEMAFORO_H  
#define SEMAFORO_H

#include <stdio.h>
#include <stdlib.h>

#include <wiringPi.h>

#include <unistd.h>

#define ESTADO 0

#define DELAY_AMARELO 300

#define DELAY_PRINCIPAL_VERDE_MINIMO 1000
#define DELAY_AUXILIAR_VERDE_MINIMO 500

#define DELAY_PRINCIPAL_VERDE_MAXIMO 2000
#define DELAY_AUXILIAR_VERDE_MAXIMO 1000

#define DELAY_PRINCIPAL_VERMELHO_MINIMO 800
#define DELAY_AUXILIAR_VERMELHO_MINIMO 1300

#define DELAY_PRINCIPAL_VERMELHO_MAXIMO 1300
#define DELAY_AUXILIAR_VERMELHO_MAXIMO 2300

#define DELAY_VERMELHO_TOTAL 100

void verdeParaVermelho(int * leds);

void vermelhoParaVerde(int * leds);

void ligarLed(int led);

void desligarLed(int led);

void configuraSemaforo(int *leds, int botao);

#endif
