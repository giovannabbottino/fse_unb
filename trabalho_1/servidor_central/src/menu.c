#include "menu.h"
#include "server.h"

void cancela() {
    printf("\nVoltando ao menu...\n");
    escreveMenu();
}

void escreveMenu(){
    printf("\n>>>[MENU]<<<\n");
    printf("[1] Monitoramento\n");
    printf("[2] Modo noturno\n");
    printf("[3] Modo de emergência\n");
}
void handleUser(){
    char messagem[200];
	bzero(messagem, 200); /* apaga a informacao*/
            
	fgets(messagem, sizeof(messagem), stdin);

    if (strcmp(messagem, "1") == 0){
        printf("\n>>>Não implementado<<<\n");
    } else if (strcmp(messagem, "2") == 0){
        handlerSendMessage("2");
    } else if (strcmp(messagem, "3") == 0){
        handlerSendMessage("3");
    } else {
        printf("\n>>>Escolha um item adequado<<<\n");
        escreveMenu();
    }
}
