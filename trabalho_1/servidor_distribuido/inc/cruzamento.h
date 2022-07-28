#ifndef CRUZAMENTO_H
#define CRUZAMENTO_H

#include "semaforo.h"
#include "info.h"

typedef struct cruzamento{
    Semaforo * semaforos[2];
}Cruzamento;


typedef struct variaveisCruzamento{
    int SEMAFORO_1_VERDE;
    int SEMAFORO_1_AMARELO;
    int SEMAFORO_1_VERMELHO;
    int SEMAFORO_2_VERDE;
    int SEMAFORO_2_AMARELO;
    int SEMAFORO_2_VERMELHO;
    int BOTAO_PEDESTRE_1;
    int BOTAO_PEDESTRE_2;
    int SENSOR_PASSAGEM_1;
    int SENSOR_PASSAGEM_2;
    int SENSOR_VELOCIDADE_1_A;
    int SENSOR_VELOCIDADE_1_B;
    int SENSOR_VELOCIDADE_2_A;
    int SENSOR_VELOCIDADE_2_B;
}VariaveisCruzamento;

void *cruzamentoHandlerThread();
void tipoCruzamento(int tipo);
Cruzamento * configuraCruzamento();
#endif