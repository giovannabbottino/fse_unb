#ifndef SEMAFORO_H  
#define SEMAFORO_H

#include <stdio.h>
#include <stdlib.h>

#include <wiringPi.h>

#include <unistd.h>

typedef struct semaforo{
    int leds[3];
    int botao;
    int sensor_passagem;
    int sensores_velocidade[2];
    int led_ligado; //0 verde 1 amarelo 2 vermelho 3 nenhum
}Semaforo;

int apagaLeds(Semaforo * semaforo);

int verdeParaVermelho(Semaforo * semaforo);

int vermelhoParaVerde(Semaforo * semaforo);

void ligarLed(int led);

void desligarLed(int led);

Semaforo * configuraSemaforo(int leds[], int botao, int sensor_passagem, int sensor_velocidade[]);

#endif
