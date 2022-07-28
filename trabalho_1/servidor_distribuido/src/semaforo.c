#include "semaforo.h"


struct semaforo {
    int leds[3];
    int botao;
    int sensor_passagem;
    int sensores_velocidade[2];
};

struct semaforo * configuraSemaforo(int * leds, int botao, int sensor_passagem, int * sensor_velocidade){
    struct semaforo * semaforo = (semaforo *) malloc(sizeof(semaforo));
    semaforo->leds = leds;
    semaforo->botao = botao;
    semaforo->sensor_passagem = sensor_passagem;
    semaforo->sensores_velocidade = sensor_velocidade;

    pinMode(semaforo->botao, INPUT);

    pinMode(semaforo->sensor_passagem, INPUT);

    for (int i=0; i<3; i++){
        pinMode(semaforo->leds[i], OUTPUT);
    }
    
    for (int i=0; i<2; i++){
        pinMode(cruzamento->sensores_velocidade[i], INPUT);
    }

    return semaforo;
}

void verdeParaVermelho(int * leds){
    desligarLed(leds[0]); // desliga led verde
    ligarLed(leds[1]); // liga led amarelo
    delay(DELAY_AMARELO);

    desligarLed(leds[1]); // desliga led amarelo
    ligarLed(leds[2]); // liga led vermelho
}

void vermelhoParaVerde(int * leds){
    desligarLed(leds[2]); // desliga led vermelho
    ligarLed(leds[0]); // liga led verde
}

void ligarLed(int led){
    printf(">> Led %d Ligado<<\n", led);
    digitalWrite(led, HIGH);
}

void desligarLed(int led){
    printf(">> Led %d Desligado<<\n", led);
    digitalWrite(led, LOW);
}
