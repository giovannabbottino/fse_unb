#include "semaforo.h"


void configuraSemaforo(int *leds, int botao){
    wiringPiSetup();

    for (int i=0; i<3; i++){
        pinMode(leds[i], OUTPUT);
    }

    pinMode(botao, INPUT);
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
