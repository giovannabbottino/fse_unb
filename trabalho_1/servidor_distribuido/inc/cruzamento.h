#ifndef CRUZAMENTO_H
#define CRUZAMENTO_H

#include "semaforo.h"
#include "info.h"
#include <sys/time.h>
#include <time.h>
#include <pthread.h>
#include <stdbool.h>

#define IGNORE_CHANGE_BELOW_USEC 400

typedef struct cruzamento{
    Semaforo * semaforos[2];
    int estado;
} Cruzamento;


typedef struct variaveisCruzamento{
    int semaforo_1_verde;
    int semaforo_1_amarelo;
    int semaforo_1_vermelho;
    int semaforo_2_verde;
    int semaforo_2_amarelo;
    int semaforo_2_vermelho;
    int botao_pedestre_1;
    int botao_pedestre_2;
    int sensor_passagem_1;
    int sensor_passagem_2;
    int sensor_velocidade_1_A;
    int sensor_velocidade_1_B;
    int sensor_velocidade_2_A;
    int sensor_velocidade_2_B;
}VariaveisCruzamento;

Cruzamento * cruzamento;
int tipo;

void *cruzamentoHandlerThread();
void botao_apertado();
void sensor_passagem();
void ultimaMudanca();
void handle();
float time_diff(struct timeval *start, struct timeval *end);
void limpaCruzamento();
void configuraCruzamento();
void tipoCruzamento(int tipo);

#endif