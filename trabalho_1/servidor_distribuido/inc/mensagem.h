#ifndef MENSAGEM_H
#define MENSAGEM_H

#include <stdio.h> /* printf() */
#include <stdlib.h>
#include <strings.h> /* bzero() */
#include <time.h>


typedef struct mensagem{
    struct Mensagem * proxima;
    int cruzamento;
    int passagem_carro;
    int acima_velocidade;
    int avanco_vermelho;
    struct timespec * timestamp;
}Mensagem;

Mensagem * mensagens;


void esvaziaMensagens();
void handlerMensagem(char *message);
    
#endif