#include "tempo.h"

static struct timeval inicio;
float duracao = 0.0;

void * tempoHandler(){
    ultimaMudanca();
    for(;;){

    }
}

void ultimaMudanca(){
    gettimeofday(&inicio, NULL);
}

void add_tempo(float minutos){
    printf("Aumentando tempo %.2f em %.2f", duracao, minutos);
    duracao = duracao + minutos;
}
void rm_tempo(float minutos){
    printf("Diminuindo tempo %.2f em %.2f", duracao, minutos);
    duracao = duracao + minutos;
}
float get_tempo_restante(){
    struct timeval agora;
    gettimeofday(&agora, NULL);

    float durou = time_diff(&inicio, &agora);

    return duracao - durou;
}

float time_diff(struct timeval *start, struct timeval *end){
    return ((end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec) )* 1000.0;
}