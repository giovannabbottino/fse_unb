#include "mensagem.h"

void handlerMensagem(char * mensagem){
    /*
        estado 
        2 = emergencia
        3 = noturno
        */
    if (strcmp(mensagem, "2") == 0){
        if (cruzamento->estado != 2)
            cruzamento->estado = 2;
        else
            cruzamento->estado = 0;
    } else if (strcmp(mensagem, "3") == 0){
        if (cruzamento->estado != 3)
            cruzamento->estado = 3;
        else
            cruzamento->estado = 1;
    } else {
        printf("\n[CLIENT] A mensagem é invalida\n");
    }
}