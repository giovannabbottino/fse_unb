#include "cruzamento.h"

struct cruzamento{
    struct semaforos * semaforos[2];
};

void *cruzamentoHandlerThread() {
    run(1);
}

void run(int tipo){
    struct cruzamento * cruzamento = configuraCruzamento(tipo);
    for(;;){
        ligarLed(cruzamento->semaforos[0].leds[0]); // liga semaforo principal led verde 
        ligarLed(cruzamento->semaforos[1].leds[2]); // liga semaforo auxiliar led vermelho

        delay(DELAY_PRINCIPAL_VERDE_MINIMO); 
        verdeParaVermelho(cruzamento->semaforos[0].leds);
        vermelhoParaVerde(cruzamento->semaforos[1].leds);

        delay(DELAY_PRINCIPAL_VERMELHO_MINIMO);
        vermelhoParaVerde(cruzamento->semaforos[0].leds);
        vermelhoParaVerde(cruzamento->semaforos[1].leds);
    }
}

struct cruzamento * configuraCruzamento(int tipo){
    tipoCruzamento(tipo); 
    struct cruzamento * cruzamento = (cruzamento *) malloc(sizeof(cruzamento));

    wiringPiSetup();
    
    struct semaforo * cruzamento->semaforos[0] = configuraSemaforo(
            [SEMAFORO_1_VERDE, SEMAFORO_1_AMARELO, SEMAFORO_1_VERMELHO],
            BOTAO_PEDESTRE_1,
            SENSOR_PASSAGEM_1,
            [SENSOR_VELOCIDADE_1_A, SENSOR_VELOCIDADE_1_B]
        );
    struct semaforo * cruzamento->semaforos[1] = configuraSemaforo(
            [SEMAFORO_2_VERDE, SEMAFORO_2_AMARELO, SEMAFORO_2_VERMELHO],
            BOTAO_PEDESTRE_2,
            SENSOR_PASSAGEM_2,
            [SENSOR_VELOCIDADE_2_A, SENSOR_VELOCIDADE_2_B]
        );

    return cruzamento;
}

void tipoCruzamento(int tipo){
    if (tipo == 1){
        SEMAFORO_1_VERDE = CRUZAMENTO_1_SEMAFORO_1_VERDE;
        SEMAFORO_1_AMARELO = CRUZAMENTO_1_SEMAFORO_1_AMARELO;
        SEMAFORO_1_VERMELHO = CRUZAMENTO_1_SEMAFORO_1_VERMELHO;
        SEMAFORO_2_VERDE = CRUZAMENTO_1_SEMAFORO_2_VERDE;
        SEMAFORO_2_AMARELO = CRUZAMENTO_1_SEMAFORO_2_AMARELO;
        SEMAFORO_2_VERMELHO = CRUZAMENTO_1_SEMAFORO_2_VERMELHO;
        BOTAO_PEDESTRE_1 = CRUZAMENTO_1_BOTAO_PEDESTRE_1;
        BOTAO_PEDESTRE_2 = CRUZAMENTO_1_BOTAO_PEDESTRE_2;
        SENSOR_PASSAGEM_1 = CRUZAMENTO_1_SENSOR_PASSAGEM_1;
        SENSOR_PASSAGEM_2 = CRUZAMENTO_1_SENSOR_PASSAGEM_2;
        SENSOR_VELOCIDADE_1_A = CRUZAMENTO_1_SENSOR_VELOCIDADE_1_A;
        SENSOR_VELOCIDADE_1_B = CRUZAMENTO_1_SENSOR_VELOCIDADE_1_B;
        SENSOR_VELOCIDADE_2_A = CRUZAMENTO_1_SENSOR_VELOCIDADE_2_A;
        SENSOR_VELOCIDADE_2_B = CRUZAMENTO_1_SENSOR_VELOCIDADE_2_B;
    } else {
        SEMAFORO_1_VERDE = CRUZAMENTO_2_SEMAFORO_1_VERDE;
        SEMAFORO_1_AMARELO = CRUZAMENTO_2_SEMAFORO_1_AMARELO;
        SEMAFORO_1_VERMELHO = CRUZAMENTO_2_SEMAFORO_1_VERMELHO;
        SEMAFORO_2_VERDE = CRUZAMENTO_2_SEMAFORO_2_VERDE;
        SEMAFORO_2_AMARELO = CRUZAMENTO_2_SEMAFORO_2_AMARELO;
        SEMAFORO_2_VERMELHO = CRUZAMENTO_2_SEMAFORO_2_VERMELHO;
        BOTAO_PEDESTRE_1 = CRUZAMENTO_2_BOTAO_PEDESTRE_1;
        BOTAO_PEDESTRE_2 = CRUZAMENTO_2_BOTAO_PEDESTRE_2;
        SENSOR_PASSAGEM_1 = CRUZAMENTO_2_SENSOR_PASSAGEM_1;
        SENSOR_PASSAGEM_2 = CRUZAMENTO_2_SENSOR_PASSAGEM_2;
        SENSOR_VELOCIDADE_1_A = CRUZAMENTO_2_SENSOR_VELOCIDADE_1_A;
        SENSOR_VELOCIDADE_1_B = CRUZAMENTO_2_SENSOR_VELOCIDADE_1_B;
        SENSOR_VELOCIDADE_2_A = CRUZAMENTO_2_SENSOR_VELOCIDADE_2_A;
        SENSOR_VELOCIDADE_2_B = CRUZAMENTO_2_SENSOR_VELOCIDADE_2_B;
    }
}