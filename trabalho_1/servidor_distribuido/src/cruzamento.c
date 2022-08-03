#include "cruzamento.h"
#include "mensagem.h"

VariaveisCruzamento var = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
Cruzamento * cruzamento = {NULL};
int tipo;

static struct timeval ultimasMudancas;

float duracao;

void *cruzamentoHandlerThread() {
    printf("\nComecei a thread de cruzamento...\n");

    limpaCruzamento(cruzamento);

    ligarLed(cruzamento->semaforos[0]->leds[0]); // liga semaforo principal led verde 
    ligarLed(cruzamento->semaforos[1]->leds[2]); // liga semaforo auxiliar led vermelho
    cruzamento->estado = 1;

    esvaziaMensagens();
    mensagens->cruzamento = 2;
    mensagens->passagem_carro = 0;
    mensagens->acima_velocidade = 2;
    mensagens->avanco_vermelho = 3;
    
    ultimaMudanca(); 
    printf("\nIniciando loop...\n");
    for(;;){
        handle();
    }
}

void botao_apertado(){
    printf("\n>>Botão apertado!<<\n");
    printf("Duracao %d\n", duracao);
}

void handle(){
    struct timeval agora;
    gettimeofday(&agora, NULL); 
    duracao = time_diff(&ultimasMudancas, &agora);
    switch (cruzamento->estado) {
        /*
        estado 
        1 = ligado
        0 = desligado
        2 = emergencia
        3 = noturno
        */
        case 1: // ligado
            if( duracao >= DELAY_PRINCIPAL_VERDE_MINIMO && duracao <= DELAY_PRINCIPAL_VERDE_MAXIMO){
                verdeParaVermelho(cruzamento->semaforos[0]->leds);
                vermelhoParaVerde(cruzamento->semaforos[1]->leds);
                cruzamento->estado = 0;
                ultimaMudanca();
            }
            break;
        case 0: // desligado
            if( duracao >= DELAY_AUXILIAR_VERDE_MINIMO && duracao <= DELAY_PRINCIPAL_VERDE_MAXIMO){
                verdeParaVermelho(cruzamento->semaforos[1]->leds);
                vermelhoParaVerde(cruzamento->semaforos[0]->leds);
                cruzamento->estado = 1; // ligado
                ultimaMudanca();
            }
            break;
        case 2: // emergencia    
            ligarLed(cruzamento->semaforos[0]->leds[0]);
            ligarLed(cruzamento->semaforos[1]->leds[2]);
            cruzamento->estado = 2;
            ultimaMudanca();
            break;
        case 3: // noturno
            limpaCruzamento(cruzamento);
            if( duracao >= DELAY_AMARELO ){
            ligarLed(cruzamento->semaforos[0]->leds[1]);
            ligarLed(cruzamento->semaforos[1]->leds[1]);
            cruzamento->estado = 3;
            delay(DELAY_AMARELO);
            ultimaMudanca();
            }
            break;
    }
}

float time_diff(struct timeval *start, struct timeval *end){
    return ((end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec) )* 1000.0;
}

void ultimaMudanca(){
    gettimeofday(&ultimasMudancas, NULL);
}

void limpaCruzamento(Cruzamento * cruzamento){
    apagaLeds(cruzamento->semaforos[0]);
    apagaLeds(cruzamento->semaforos[1]);
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

    int semaforos2[3] = {var.semaforo_2_verde, var.semaforo_2_amarelo, var.semaforo_2_vermelho};
    int velocidade2[2] = {var.sensor_velocidade_2_A, var.sensor_velocidade_2_B};
    Semaforo * s2 = configuraSemaforo(
            semaforos2,
            var.botao_pedestre_2,
            var.sensor_passagem_2,
            velocidade2
        );

    wiringPiISR(s1->botao, INT_EDGE_FALLING, botao_apertado);
    wiringPiISR(s2->botao, INT_EDGE_FALLING, botao_apertado);

    cruzamento->semaforos[0] = s2;
    cruzamento->semaforos[1] = s1;
    cruzamento->estado = 1; // ligado o cruzamento 0
}

void tipoCruzamento(int t){
    tipo = t;
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
