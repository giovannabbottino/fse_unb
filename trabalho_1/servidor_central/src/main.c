#include <pthread.h>
#include <signal.h>

#include "server.h"

pthread_t socketThread;

void cancelaExecucao() {
    printf("\nCancelando execução...\n");
    pthread_cancel(socketThread);
    exit(0);
}

int main(int argc, char **argv) {
    /* Verifica se a porta foi enviado pelo argc  */
    if (argc<3) {
	  printf("[SERVER] Digite a porta e o ip");
	  exit(0);       
    }

    /* Verifica se a porta é um número */
    if (!isdigit(*argv[1])){
        printf("[SERVER] A porta deve ser um número");
		exit(0);
    }
    signal(SIGINT, cancelaExecucao);

    printf("\nVou começar as threads...\n");

    iniciaSocket(atoi(argv[1]), argv[2]);
    pthread_create(&socketThread, NULL, &serverSocketThread, NULL);
    pthread_detach(socketThread);

    while(1) {
        sleep(1);
    }
    return 0;
}