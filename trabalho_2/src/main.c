#include <stdio.h>
#include <stdlib.h>

#include <signal.h>
#include <pthread.h>
#include "menu.h"
#include "tempo.h"
#include "handler.h"

pthread_t tempoThread;

void cancelaExecucao() {
    printf("\nCancelando execução...\n");
    pthread_cancel(tempoThread);
    desligarHandler();
    exit(0);
}

int main(int argc, const char * argv[]) {
    signal(SIGINT, cancelaExecucao);

    pthread_create(&tempoThread, NULL, &tempoHandler, NULL);
    pthread_detach(tempoThread);

    menu_inicial();
    return 0;
}
