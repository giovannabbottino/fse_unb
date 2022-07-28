#ifndef SEMAFORO_H  
#define SEMAFORO_H

#include <stdio.h>
#include <stdlib.h>

#include <wiringPi.h>

#include <unistd.h>

#define DELAY_AMARELO 3000

#define DELAY_PRINCIPAL_VERDE_MINIMO 10000
#define DELAY_AUXILIAR_VERDE_MINIMO 5000

#define DELAY_PRINCIPAL_VERDE_MAXIMO 20000
#define DELAY_AUXILIAR_VERDE_MAXIMO 10000

#define DELAY_PRINCIPAL_VERMELHO_MINIMO 8000
#define DELAY_AUXILIAR_VERMELHO_MINIMO 13000

#define DELAY_PRINCIPAL_VERMELHO_MAXIMO 13000
#define DELAY_AUXILIAR_VERMELHO_MAXIMO 23000

#define DELAY_VERMELHO_TOTAL 1000


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
