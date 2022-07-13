#include "semaforo.h"

void pwmLigarLed(int led, int frequencia){
    printf(">> Ligando Led: %d <<\n", led);
    for(int i=0; i<frequencia + 1; i++) {
        softPwmWrite(led, i);
        printf(">> Valor Led %d: %d <<\n", led, i);
        delay(100);
    }
}

void pwmDesligarLed(int led, int frequencia){
    printf(">> Desligando Led: %d <<\n", led);
    for(int i=frequencia + 1; i>0; i--) {
        softPwmWrite(led, i);
        printf(">> Valor Led %d: %d <<\n", led, i);
        delay(100);
    }
}

void verdeParaVermelho(int * leds, int frequencia){
    pid_t process = fork();

    if (process == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (process > 0 ) {
        pwmDesligarLed(leds[0], frequencia ); // desliga o verde
        pwmLigarLed(leds[2], frequencia); // liga o vermelho
    } else {
        pwmLigarLed(leds[1], frequencia); // liga o amarelo
        pwmDesligarLed(leds[1], frequencia); // desliga o amarelo
    }
}

void ligarLed(int led){
    printf(">> Led %d Ligado<<\n", led);
    digitalWrite(led, HIGH);
}

int main(int argc, char *argv[]){
    if (argc<5) {
      die("Modo de uso: semaforo pinVerde pinAmarelo pinVermelho pinBotao frequencia");
	  exit(0);       
    }
    int leds [] = {atoi(argv[1]), atoi(argv[2]), atoi(argv[3])};
    // int botao = atoi(argv[4]); 
    int frequencia = atoi(argv[5]);

    wiringPiSetup();

    for (int i=0; i<3; i++){
        pinMode(leds[i], OUTPUT);
        softPwmCreate (leds[i], 0, frequencia) ;
    }

    ligarLed(leds[0]); // liga led verde

    verdeParaVermelho(leds, frequencia);
    return 0;
}
