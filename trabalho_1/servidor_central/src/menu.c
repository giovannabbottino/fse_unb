#include "menu.h"

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

    if (strcmp(messagem, "1") == 0  || strcmp(messagem, "2") == 0 || strcmp(messagem, "3") == 0){
        strcpy(messagemServer, messagem);
        enviar = 1;

    } else {
        printf("\n>>>Escolha um item adequado<<<\n"); 
    }
    escreveMenu();
}
