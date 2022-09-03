#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "menu.h"

void cancelaExecucao() {
    printf("\nCancelando execução...\n");
    exit(0);
}

int main(int argc, const char * argv[]) {
    signal(SIGINT, cancelaExecucao);

    menu_inicial();
    return 0;
}
