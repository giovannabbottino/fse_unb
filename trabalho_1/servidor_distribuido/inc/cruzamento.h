#ifndef CRUZAMENTO_H
#define CRUZAMENTO_H

#include "semaforo.h"
#include "info.h"

#define SEMAFORO_1_VERDE 0
#define SEMAFORO_1_AMARELO 0
#define SEMAFORO_1_VERMELHO 0

#define SEMAFORO_2_VERDE 0
#define SEMAFORO_2_AMARELO 0
#define SEMAFORO_2_VERMELHO 0

#define BOTAO_PEDESTRE_1 0
#define BOTAO_PEDESTRE_2 0
#define SENSOR_PASSAGEM_1 0
#define SENSOR_PASSAGEM_2 0

#define SENSOR_VELOCIDADE_1_A 0
#define SENSOR_VELOCIDADE_1_B 0
#define SENSOR_VELOCIDADE_2_A 0 
#define SENSOR_VELOCIDADE_2_B 0

typedef struct cruzamento Cruzamento;

void *cruzamentoHandlerThread();
void run(int tipo);
void tipoCruzamento(int tipo);
Cruzamento * configuraCruzamento();
#endif