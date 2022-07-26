#include <pthread.h>
#include <signal.h>

#include "cruzamento.h"
pthread_t socketThread, cruzamentoThread;

void cancelaExecucao() {
    printf("\nCancelando execução...\n");
    pthread_cancel(cruzamentoThread);
    // pthread_cancel(socketThread);
    exit(0);
}

int main(int argc, char **argv) {
    signal(SIGINT, cancelaExecucao);
    // vai dar erro pq n existe
    pthread_create(&socketThread, NULL, &cruzamentoHandlerThread, NULL);
    pthread_detach(cruzamentoThread);

    // pthread_create(&socketThread, NULL, &clientSocketThread, NULL);
    // pthread_detach(socketThread);

    while(1) {
        sleep(1);
    }
    return 0;
}