#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>

#include "menu.h"

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

    if(lcd_init() == -1){
        perror("Error ao iniciar lcd")
        exit(1);
    }
    lcd_clear();
    lcd_type_line("    SISTEMA");
    lcd_set_line(LCD_LINE2);
    lcd_type_line(" INICIALIZANDO");

    return 0;
}
