#include "menu.h"
#include "server.h"

void cancela() {
    printf("\nVoltando ao menu...\n");
    escreveMenu();
}

void * escreveMenu(){
    printf("\n>>>[MENU]<<<\n");
    printf("[1] Monitoramento\n");
    printf("[2] Modo de emergência\n");
    printf("[3] Modo noturno\n");
    for(;;){
        handleUser();
    }
}
void handleUser(){
    char messagem[200];
	bzero(messagem, 200); /* apaga a informacao*/
            
	fgets(messagem, sizeof(messagem), stdin);
    messagem[strcspn(messagem, "\n")] = '\0';

    if (strcmp(messagem, "1") == 0){
        handlerSendMessage("1");
    } else if (strcmp(messagem, "2") == 0){
        handlerSendMessage("2");
        escreveMenu();
    } else if (strcmp(messagem, "3") == 0){
        handlerSendMessage("3");
        escreveMenu();
    } else {
        printf("\n>>>Escolha um item adequado<<<\n");
        escreveMenu();
    }
}
