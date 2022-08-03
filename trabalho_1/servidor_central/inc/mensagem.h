#ifndef MENSAGEM_H
#define MENSAGEM_H

#include <time.h>


typedef struct mensagem{
    struct Mensagem * proxima;
    int cruzamento;
    int passagem_carro;
    int acima_velocidade;
    int avanco_vermelho;
    struct timespec * timestamp;
}Mensagem;

#endif