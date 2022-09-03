#ifndef TEMPO_H_
#define TEMPO_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

float duracao;
void * tempoHandler();
void add_tempo(float minutos);
void rm_tempo(float minutos);
float get_tempo_restante();
float time_diff(struct timeval *start, struct timeval *end);

#endif
