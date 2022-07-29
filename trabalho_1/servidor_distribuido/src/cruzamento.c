#include "cruzamento.h"

VariaveisCruzamento var = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
Cruzamento * cruzamento = {NULL};

static struct timeval ultimasMudancas;

struct timeval get_now() {
    struct timeval now;

    gettimeofday(&now, NULL);

    return now;
}

void *cruzamentoHandlerThread() {
    configuraCruzamento();
    printf("\nComecei a thread de cruzamento...\n");
    printf("\nIniciando loop...\n");

    for (int i=0; i<3; i++){
        desligarLed(cruzamento->semaforos[0]->leds[i]);
        desligarLed(cruzamento->semaforos[1]->leds[i]);
    }
    ligarLed(cruzamento->semaforos[0]->leds[0]); // liga semaforo principal led verde 
    ligarLed(cruzamento->semaforos[1]->leds[2]); // liga semaforo auxiliar led vermelho
    ultimasMudancas = get_now();

    for(;;){
        botao_apertado();
        handle();
    }
}

void handle(){
    struct timeval agora = get_now();
    long int soma = 1000000;
    unsigned long duracao = (agora.tv_sec + soma + agora.tv_usec) - (ultimasMudancas.tv_sec + soma + ultimasMudancas.tv_usec);
    switch (cruzamento->estado[0]) {
        case 1:
            if( duracao >= DELAY_PRINCIPAL_VERDE_MINIMO && duracao <= DELAY_PRINCIPAL_VERDE_MAXIMO){
                printf("\n>> Duracao : %d\n",duracao );
                printf(">> Mudando semaforo principal para vermelho\n");
                verdeParaVermelho(cruzamento->semaforos[0]->leds);
                printf(">> Mudando semaforo auxiliar para verde\n");
                vermelhoParaVerde(cruzamento->semaforos[1]->leds);
                cruzamento->estado[0] = 0;
                cruzamento->estado[1] = 1;
                ultimasMudancas = agora;
                delay(DELAY_PRINCIPAL_VERDE_MINIMO);
            }
            break;
        case 0:
            if( duracao >= DELAY_AUXILIAR_VERDE_MINIMO && duracao <= DELAY_AUXILIAR_VERDE_MAXIMO){
                printf("\n>> Duracao : %d\n",duracao );
                printf(">> Mudando semaforo auxiliar para vermelho\n");
                verdeParaVermelho(cruzamento->semaforos[1]->leds);
                printf(">> Mudando semaforo principal para verde\n");
                vermelhoParaVerde(cruzamento->semaforos[0]->leds);
                cruzamento->estado[0] = 1;
                cruzamento->estado[1] = 0;
                ultimasMudancas = agora;
                delay(DELAY_AUXILIAR_VERDE_MINIMO);
            }
            break;
    }
}


void configuraCruzamento(){ 
    printf("\nConfigurando cruzamento...\n");
    cruzamento = (Cruzamento*)realloc(cruzamento, sizeof(Cruzamento));
    
    int semaforos1[3] = {var.semaforo_1_verde, var.semaforo_1_amarelo, var.semaforo_1_vermelho};
    int velocidade1[2] = {var.sensor_velocidade_1_A, var.sensor_velocidade_1_B};

    Semaforo * s1 = configuraSemaforo(
            semaforos1,
            var.botao_pedestre_1,
            var.sensor_passagem_1,
            velocidade1
        );

    cruzamento->semaforos[0] = s1;
    cruzamento->estado[0] = 1; // ligado

    int semaforos2[3] = {var.semaforo_2_verde, var.semaforo_2_amarelo, var.semaforo_2_vermelho};
    int velocidade2[2] = {var.sensor_velocidade_2_A, var.sensor_velocidade_2_B};
    Semaforo * s2 = configuraSemaforo(
            semaforos2,
            var.botao_pedestre_2,
            var.sensor_passagem_2,
            velocidade2
        );
    cruzamento->semaforos[1] = s2;
    cruzamento->estado[1] = 0; // desligado
}

void tipoCruzamento(int tipo){
    printf("\nCruzamento %d...\n", tipo);
    if (tipo == 1){
        var.semaforo_1_verde = CRUZAMENTO_1_SEMAFORO_1_VERDE;
        var.semaforo_1_amarelo = CRUZAMENTO_1_SEMAFORO_1_AMARELO;
        var.semaforo_1_vermelho = CRUZAMENTO_1_SEMAFORO_1_VERMELHO;
        var.semaforo_2_verde = CRUZAMENTO_1_SEMAFORO_2_VERDE;
        var.semaforo_2_amarelo = CRUZAMENTO_1_SEMAFORO_2_AMARELO;
        var.semaforo_2_vermelho = CRUZAMENTO_1_SEMAFORO_2_VERMELHO;
        var.botao_pedestre_1 = CRUZAMENTO_1_BOTAO_PEDESTRE_1;
        var.botao_pedestre_2 = CRUZAMENTO_1_BOTAO_PEDESTRE_2;
        var.sensor_passagem_1 = CRUZAMENTO_1_SENSOR_PASSAGEM_1;
        var.sensor_passagem_2 = CRUZAMENTO_1_SENSOR_PASSAGEM_2;
        var.sensor_velocidade_1_A = CRUZAMENTO_1_SENSOR_VELOCIDADE_1_A;
        var.sensor_velocidade_1_B = CRUZAMENTO_1_SENSOR_VELOCIDADE_1_B;
        var.sensor_velocidade_2_A = CRUZAMENTO_1_SENSOR_VELOCIDADE_2_A;
        var.sensor_velocidade_2_B = CRUZAMENTO_1_SENSOR_VELOCIDADE_2_B;
    } else {
        var.semaforo_1_verde = CRUZAMENTO_2_SEMAFORO_1_VERDE;
        var.semaforo_1_amarelo = CRUZAMENTO_2_SEMAFORO_1_AMARELO;
        var.semaforo_1_vermelho = CRUZAMENTO_2_SEMAFORO_1_VERMELHO;
        var.semaforo_2_verde = CRUZAMENTO_2_SEMAFORO_2_VERDE;
        var.semaforo_2_amarelo = CRUZAMENTO_2_SEMAFORO_2_AMARELO;
        var.semaforo_2_vermelho = CRUZAMENTO_2_SEMAFORO_2_VERMELHO;
        var.botao_pedestre_1 = CRUZAMENTO_2_BOTAO_PEDESTRE_1;
        var.botao_pedestre_2 = CRUZAMENTO_2_BOTAO_PEDESTRE_2;
        var.sensor_passagem_1 = CRUZAMENTO_2_SENSOR_PASSAGEM_1;
        var.sensor_passagem_2 = CRUZAMENTO_2_SENSOR_PASSAGEM_2;
        var.sensor_velocidade_1_A = CRUZAMENTO_2_SENSOR_VELOCIDADE_1_A;
        var.sensor_velocidade_1_B = CRUZAMENTO_2_SENSOR_VELOCIDADE_1_B;
        var.sensor_velocidade_2_A = CRUZAMENTO_2_SENSOR_VELOCIDADE_2_A;
        var.sensor_velocidade_2_B = CRUZAMENTO_2_SENSOR_VELOCIDADE_2_B;
    }
}

void botao_apertado(){
    long int soma = 1000000;
    struct timeval agora = get_now();
    struct timeval botao_pressionado = agora;;
    unsigned long duracao;

    int botao_1 = digitalRead(cruzamento->semaforos[0]->botao);

    int botao_2 = digitalRead(cruzamento->semaforos[1]->botao);

    if (botao_1==HIGH || botao_2==HIGH){
        botao_pressionado = get_now();
    }
    
    duracao = (agora.tv_sec + soma + agora.tv_usec) - (botao_pressionado.tv_sec + soma + botao_pressionado.tv_usec);
    if (duracao >= 300 ) {
        printf("\nDuracao %d\n", duracao);
        printf(">>Botão apertado!<<\n");
        while (!cruzamento->estado[0] && !cruzamento->estado[1]){
            handle();
        }            
    }
}
