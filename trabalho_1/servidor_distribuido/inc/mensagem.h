#ifndef MENSAGEM_H
#define MENSAGEM_H

#include <stdio.h> /* printf() */
#include <stdlib.h>
#include <strings.h> /* bzero() */
#include <time.h>

#include "cruzamento.h"
#include "client.h"


typedef struct mensagem{
    int cruzamento;
    int passagem_carro;
    int acima_velocidade;
    int avanco_vermelho;
    float velocidade_media;
}Mensagem;

Mensagem * mensagens;


void esvaziaMensagens();
void handlerMensagem(char *message);
    
#endif