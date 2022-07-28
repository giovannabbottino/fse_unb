#include "cruzamento.h"
VariaveisCruzamento var = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

void *cruzamentoHandlerThread() {
    printf("\nComecei a thread de cruzamento...\n");
    Cruzamento * cruzamento = configuraCruzamento();
    printf("\nIniciando loop...\n");
    ligarLed(cruzamento->semaforos[0]->leds[0]); // liga semaforo principal led verde 
    ligarLed(cruzamento->semaforos[1]->leds[2]); // liga semaforo auxiliar led vermelho
    for(;;){
        delay(DELAY_PRINCIPAL_VERDE_MINIMO); 
        verdeParaVermelho(cruzamento->semaforos[0]->leds);
        vermelhoParaVerde(cruzamento->semaforos[1]->leds);

        delay(DELAY_PRINCIPAL_VERMELHO_MINIMO);
        verdeParaVermelho(cruzamento->semaforos[0]->leds);
        vermelhoParaVerde(cruzamento->semaforos[1]->leds);
    }
}

Cruzamento * configuraCruzamento(){ 
    printf("\nConfigurando cruzamento...\n");
    Cruzamento * c = (Cruzamento *) malloc(sizeof(Cruzamento));
    
    int semaforos1[3] = {var.SEMAFORO_1_VERDE, var.SEMAFORO_1_AMARELO, var.SEMAFORO_1_VERMELHO};
    int velocidade1[2] = {var.SENSOR_VELOCIDADE_1_A, var.SENSOR_VELOCIDADE_1_B};

    Semaforo * s1 = configuraSemaforo(
            semaforos1,
            var.BOTAO_PEDESTRE_1,
            var.SENSOR_PASSAGEM_1,
            velocidade1
        );

    c->semaforos[0] = s1;

    int semaforos2[3] = {var.SEMAFORO_2_VERDE, var.SEMAFORO_2_AMARELO, var.SEMAFORO_2_VERMELHO};
    int velocidade2[2] = {var.SENSOR_VELOCIDADE_2_A, var.SENSOR_VELOCIDADE_2_B};
    Semaforo * s2 = configuraSemaforo(
            semaforos2,
            var.BOTAO_PEDESTRE_2,
            var.SENSOR_PASSAGEM_2,
            velocidade2
        );
    c->semaforos[1] = s2;

    return c;
}

void tipoCruzamento(int tipo){
    printf("\nCruzamento %d...\n", tipo);
    if (tipo == 1){
        var.SEMAFORO_1_VERDE = CRUZAMENTO_1_SEMAFORO_1_VERDE;
        var.SEMAFORO_1_AMARELO = CRUZAMENTO_1_SEMAFORO_1_AMARELO;
        var.SEMAFORO_1_VERMELHO = CRUZAMENTO_1_SEMAFORO_1_VERMELHO;
        var.SEMAFORO_2_VERDE = CRUZAMENTO_1_SEMAFORO_2_VERDE;
        var.SEMAFORO_2_AMARELO = CRUZAMENTO_1_SEMAFORO_2_AMARELO;
        var.SEMAFORO_2_VERMELHO = CRUZAMENTO_1_SEMAFORO_2_VERMELHO;
        var.BOTAO_PEDESTRE_1 = CRUZAMENTO_1_BOTAO_PEDESTRE_1;
        var.BOTAO_PEDESTRE_2 = CRUZAMENTO_1_BOTAO_PEDESTRE_2;
        var.SENSOR_PASSAGEM_1 = CRUZAMENTO_1_SENSOR_PASSAGEM_1;
        var.SENSOR_PASSAGEM_2 = CRUZAMENTO_1_SENSOR_PASSAGEM_2;
        var.SENSOR_VELOCIDADE_1_A = CRUZAMENTO_1_SENSOR_VELOCIDADE_1_A;
        var.SENSOR_VELOCIDADE_1_B = CRUZAMENTO_1_SENSOR_VELOCIDADE_1_B;
        var.SENSOR_VELOCIDADE_2_A = CRUZAMENTO_1_SENSOR_VELOCIDADE_2_A;
        var.SENSOR_VELOCIDADE_2_B = CRUZAMENTO_1_SENSOR_VELOCIDADE_2_B;
    } else {
        var.SEMAFORO_1_VERDE = CRUZAMENTO_2_SEMAFORO_1_VERDE;
        var.SEMAFORO_1_AMARELO = CRUZAMENTO_2_SEMAFORO_1_AMARELO;
        var.SEMAFORO_1_VERMELHO = CRUZAMENTO_2_SEMAFORO_1_VERMELHO;
        var.SEMAFORO_2_VERDE = CRUZAMENTO_2_SEMAFORO_2_VERDE;
        var.SEMAFORO_2_AMARELO = CRUZAMENTO_2_SEMAFORO_2_AMARELO;
        var.SEMAFORO_2_VERMELHO = CRUZAMENTO_2_SEMAFORO_2_VERMELHO;
        var.BOTAO_PEDESTRE_1 = CRUZAMENTO_2_BOTAO_PEDESTRE_1;
        var.BOTAO_PEDESTRE_2 = CRUZAMENTO_2_BOTAO_PEDESTRE_2;
        var.SENSOR_PASSAGEM_1 = CRUZAMENTO_2_SENSOR_PASSAGEM_1;
        var.SENSOR_PASSAGEM_2 = CRUZAMENTO_2_SENSOR_PASSAGEM_2;
        var.SENSOR_VELOCIDADE_1_A = CRUZAMENTO_2_SENSOR_VELOCIDADE_1_A;
        var.SENSOR_VELOCIDADE_1_B = CRUZAMENTO_2_SENSOR_VELOCIDADE_1_B;
        var.SENSOR_VELOCIDADE_2_A = CRUZAMENTO_2_SENSOR_VELOCIDADE_2_A;
        var.SENSOR_VELOCIDADE_2_B = CRUZAMENTO_2_SENSOR_VELOCIDADE_2_B;
    }
}
