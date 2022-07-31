#include <pthread.h>
#include <signal.h>

#include "cruzamento.h"
#include "client.h"
#include "menu.h"

pthread_t socketThread, cruzamentoThread;

void cancelaExecucao() {
    printf("\nCancelando execução...\n");
    pthread_cancel(cruzamentoThread);
    pthread_cancel(socketThread);
    exit(0);
}

int main(int argc, char **argv) {
    /* Verifica se a porta foi enviado pelo argc  */
    if (argc<4) {
	  printf("[CLIENT] Digite a porta, o ip e o cruzamento");
	  exit(0);       
    }

    /* Verifica se a porta é um número */
    if (!isdigit(*argv[1])){
        printf("[CLIENT] A porta deve ser um número");
		exit(0);
    }

    /* Verifica se o cruzamento é um número */
    if (!isdigit(*argv[3])){
        printf("[CLIENT] O cruzamento deve ser um número");
		exit(0);
    }
    signal(SIGINT, cancelaExecucao);

    printf("\nVou começar as threads...\n");

    tipoCruzamento(atoi(argv[3]));
    configuraCruzamento();
    pthread_create(&cruzamentoThread, NULL, &cruzamentoHandlerThread, NULL);
    pthread_detach(cruzamentoThread);
    
    iniciaSocket(atoi(argv[1]), argv[2]);
    pthread_create(&socketThread, NULL, &clientSocketThread, NULL);
    pthread_detach(socketThread);

    pause();
    return 0;
}