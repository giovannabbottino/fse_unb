#include "semaforo.h"
#include "info.h"

Semaforo * configuraSemaforo(int leds[], int botao, int sensor_passagem, int sensor_velocidade[]){
    Semaforo * semaforo = (Semaforo *) malloc(sizeof(Semaforo));
    semaforo->botao = botao;
    semaforo->sensor_passagem = sensor_passagem;

    wiringPiSetup();

    pinMode(semaforo->botao, INPUT);

    pinMode(semaforo->sensor_passagem, INPUT);

    for (int i=0; i<3; i++){
        semaforo->leds[i] = leds[i];
        pinMode(semaforo->leds[i], OUTPUT);
    }
    
    for (int i=0; i<2; i++){
        semaforo->sensores_velocidade[i] = sensor_velocidade[i];
        pinMode(semaforo->sensores_velocidade[i], INPUT);
    }

    return semaforo;
}

void verdeParaVermelho(int leds[]){
    desligarLed(leds[0]); // desliga led verde
    ligarLed(leds[1]); // liga led amarelo
    delay(DELAY_AMARELO);

    desligarLed(leds[1]); // desliga led amarelo
    ligarLed(leds[2]); // liga led vermelho
}

void vermelhoParaVerde(int leds[]){
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
