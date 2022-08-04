#include <pthread.h>
#include <signal.h>

#include "server.h"
#include "menu.h"

pthread_t socket_1_Thread, socket_2_Thread, socket_3_Thread, socket_4_Thread, menuThread;

void cancelaExecucao() {
    printf("\nCancelando execução...\n");
    pthread_cancel(socket_1_Thread);
    pthread_cancel(socket_2_Thread);
    pthread_cancel(socket_3_Thread);
    pthread_cancel(socket_4_Thread);
    pthread_cancel(menuThread);
    exit(0);
}

int main(int argc, char **argv) {
    /* Verifica se a porta foi enviado pelo argc  */
    if (argc<6) {
	  printf("[SERVER] Digite as portas e o ip");
	  exit(0);       
    }

    /* Verifica se a porta é um número */
    if (!isdigit(*argv[2])  || !isdigit(*argv[3]) || !isdigit(*argv[4]) || !isdigit(*argv[5])){
        printf("[SERVER] A porta deve ser um número");
		exit(0);
    }
    signal(SIGINT, cancelaExecucao);

    printf("\nVou começar as threads...\n");

    Args * args_1 = (Args *) malloc((Args *) sizeof(Args));
    args_1->porta = atoi(argv[2]);
    args_1->server_ip = argv[1];
    pthread_create(&socket_1_Thread, NULL, &serverSocketThread, args_1);
    pthread_detach(socket_1_Thread);

    Args * args_2 = (Args *) malloc((Args *) sizeof(Args *));
    args_2->porta = atoi(argv[3]);
    args_2->server_ip = argv[1];
    pthread_create(&socket_2_Thread, NULL, &serverSocketThread, args_2);
    pthread_detach(socket_2_Thread);

    Args * args_3 = (Args *) malloc((Args *) sizeof(Args *));
    args_3->porta = atoi(argv[4]);
    args_3->server_ip = argv[1];
    pthread_create(&socket_3_Thread, NULL, &serverSocketThread, args_3);
    pthread_detach(socket_3_Thread);

    Args * args_4 = (Args *) malloc((Args *) sizeof(Args *));
    args_4->porta = atoi(argv[5]);
    args_4->server_ip = argv[1];
    pthread_create(&socket_4_Thread, NULL, &serverSocketThread, args_4);
    pthread_detach(socket_4_Thread);

    pthread_create(&menuThread, NULL, &escreveMenu, NULL);
    pthread_detach(menuThread);

    while(1) {
        sleep(1);
    }
    return 0;
}