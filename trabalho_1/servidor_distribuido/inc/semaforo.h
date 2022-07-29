#ifndef SEMAFORO_H  
#define SEMAFORO_H

#include <stdio.h>
#include <stdlib.h>

#include <wiringPi.h>

#include <unistd.h>
#include <stdbool.h>

typedef struct semaforo{
    int leds[3];
    int botao;
    int sensor_passagem;
    int sensores_velocidade[2];
}Semaforo;

void verdeParaVermelho(int leds[]);

void vermelhoParaVerde(int leds[]);

void ligarLed(int led);

void desligarLed(int led);

Semaforo * configuraSemaforo(int leds[], int botao, int sensor_passagem, int sensor_velocidade[]);

#endif
