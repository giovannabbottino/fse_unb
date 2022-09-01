#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>

pthread_t menuThread;

void cancelaExecucao() {
    printf("\nCancelando execução...\n");
    pthread_cancel(menuThread);
    exit(0);
}

int main(int argc, const char * argv[]) {
   signal(SIGINT, cancelaExecucao);

   pthread_create(&menuThread, NULL, &menuHandlerThread, NULL);
   pthread_detach(menuThread);

   return 0;
}
