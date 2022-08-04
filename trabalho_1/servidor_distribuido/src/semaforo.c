#include "semaforo.h"
#include "info.h"

int apagaLeds(Semaforo * semaforo){
    for(int i=0; i<=2; i++){
        desligarLed(semaforo->leds[i]);
    }
    return 3;
}

Semaforo * configuraSemaforo(int leds[], int botao, int sensor_passagem, int sensor_velocidade[]){
    Semaforo * semaforo = (Semaforo *) malloc((Semaforo *) sizeof(Semaforo *));
    semaforo = (Semaforo *) realloc(semaforo, sizeof(Semaforo));
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

int verdeParaVermelho(Semaforo * semaforo){
    desligarLed(semaforo->leds[0]); // desliga led verde
    ligarLed(semaforo->leds[1]); // liga led amarelo
    delay(DELAY_AMARELO);

    desligarLed(semaforo->leds[1]); // desliga led amarelo
    ligarLed(semaforo->leds[2]); // liga led vermelho
    delay(DELAY_VERMELHO_TOTAL);
    
    return 2;
}

int vermelhoParaVerde(Semaforo * semaforo){
    desligarLed(semaforo->leds[2]); // desliga led vermelho
    ligarLed(semaforo->leds[0]); // liga led verde
    return 0;
}

void ligarLed(int led){
    digitalWrite(led, HIGH);
    return led;
}

void desligarLed(int led){
    digitalWrite(led, LOW);
}

void soarAlarme(){
    if (system("omxplayer example.mp3") < 0){
        printf("Erro para soar alarme\n");
    }
}
