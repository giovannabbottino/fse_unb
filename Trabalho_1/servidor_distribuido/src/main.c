#include <pthread.h>
#include <signal.h>

pthread_t socketThread, semaforoThread;

void cancelaExecucao() {
    printf("\nCancelando execução...\n");
    pthread_cancel(semaforoThread);
    pthread_cancel(socketThread);
    exit(0);
}

int main(int argc, char **argv) {
    signal(SIGINT, cancelaExecucao);
    // vai dar erro pq n existe
    // pthread_create(&socketThread, NULL, &cruzamentoThread, NULL);
    // pthread_detach(semaforoThread);

    // pthread_create(&socketThread, NULL, &clientSocketThread, NULL);
    // pthread_detach(socketThread);

    while(1) {
        sleep(1);
    }
    return 0;
}