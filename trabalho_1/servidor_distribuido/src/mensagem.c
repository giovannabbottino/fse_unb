#include "mensagem.h"

Mensagem * mensagens = {NULL};

void esvaziaMensagens(){
    mensagens = realloc(mensagens, sizeof(Mensagem));
    mensagens->cruzamento = tipo;
    mensagens->passagem_carro = 0;
    mensagens->acima_velocidade = 0;
    mensagens->avanco_vermelho = 0;
}

void handlerMensagem(char * mensagem){
    /*
        estado 
        2 = emergencia
        3 = noturno
        */
    if (strcmp(mensagem, "1") == 0){
        printf("\n[CLIENT] Enviando logs\n");
        int mensagem[VETOR] = {mensagens->cruzamento,  mensagens->passagem_carro, mensagens->acima_velocidade,  mensagens->avanco_vermelho};
        enviaMensagem(mensagem);
    }
    else if (strcmp(mensagem, "2") == 0){
        if (cruzamento->estado != 2){
            printf("\n[CLIENT] Entrando do modo emergencia\n");
            limpaCruzamento(cruzamento);
            cruzamento->estado = 2;
        }
        else if (cruzamento->estado == 2) {
            printf("\n[CLIENT] Saindo do modo emergencia\n");
            cruzamento->estado = 0;
            verdeParaVermelho(cruzamento->semaforos[0]->leds);
            ligarLed(cruzamento->semaforos[1]->leds[0]); // liga semaforo auxiliar led verde 
            ultimaMudanca();
        }
            
    } else if (strcmp(mensagem, "3") == 0){
        if (cruzamento->estado != 3){
            printf("\n[CLIENT] Entrando do modo noturno\n");
            limpaCruzamento(cruzamento);
            cruzamento->estado = 3;
        }   
        else if (cruzamento->estado == 3){
            printf("\n[CLIENT] Saindo do modo noturno\n");
            limpaCruzamento(cruzamento);
            ligarLed(cruzamento->semaforos[1]->leds[2]); // liga semaforo Auxiliar led vermelho 
            ligarLed(cruzamento->semaforos[0]->leds[0]); // liga semaforo principal led verde 
            cruzamento->estado = 1;
            ultimaMudanca();
        }
    } else {
        printf("\n[CLIENT] A mensagem é invalida\n");
    }
}
