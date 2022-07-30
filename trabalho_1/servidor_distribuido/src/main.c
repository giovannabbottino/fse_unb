#include <pthread.h>
#include <signal.h>

#include "cruzamento.h"
#include "client.h"

pthread_t socketThread, cruzamento1Thread, cruzamento2Thread;

void cancelaExecucao() {
    printf("\nCancelando execução...\n");
    pthread_cancel(cruzamento1Thread);
    // pthread_cancel(cruzamento2Thread);
    pthread_cancel(socketThread);
    exit(0);
}

int main(int argc, char **argv) {
    /* Verifica se a porta foi enviado pelo argc  */
    if (argc<3) {
	  printf("[CLIENT] Digite a porta e o ip");
	  exit(0);       
    }

    /* Verifica se a porta é um número */
    if (!isdigit(*argv[1])){
        printf("[CLIENT] A porta deve ser um número");
		exit(0);
    }
    signal(SIGINT, cancelaExecucao);

    printf("\nVou começar as threads...\n");

    tipoCruzamento(2);
    pthread_create(&cruzamento1Thread, NULL, &cruzamentoHandlerThread, NULL);
    pthread_detach(cruzamento1Thread);

    // tipoCruzamento(2);
    // configuraCruzamento();
    // pthread_create(&cruzamento2Thread, NULL, &cruzamentoHandlerThread, NULL);
    // pthread_detach(cruzamento2Thread);

    iniciaSocket(atoi(argv[1]), argv[2]);
    pthread_create(&socketThread, NULL, &clientSocketThread, NULL);
    pthread_detach(socketThread);

    while(1) {
        sleep(1);
    }
    return 0;
}