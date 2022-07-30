#include "client.h"
#include <string.h>

struct sockaddr_in server; /* socket do servidor */
char *server_ip;
unsigned short porta;
int client;

void iniciaSocket(int porta, char * server_ip) {
    server_ip = server_ip;
    porta = porta;
    /* Criacao do socket TCP */
    client = socket(AF_INET, SOCK_STREAM, 0);
    if (client == 0){ 
        /*
        * ARPA INTERNET PROTOCOLS -- IPv4
        * SOCK_STREAM orientado a conexão com transmissão de fluxos de bytes, sequencial e bidirecional
        * 0 - protocolo padrao para o tipo escolhido -- TCP
        */
        perror("\n[CLIENT] Criação do socket falhou");
        fechaSocket(client);
    }
    printf("\n[CLIENT] Criacao do socket TCP\n");

    memset(&server, 0, sizeof(server));

	/* Preenchendo informacoes sobre o cliente */
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(server_ip); 
	server.sin_port = htons(porta);

	/* Inicia a conexão no socket */
	if (connect(client, (struct sockaddr *)&server, sizeof(server))<0){
		perror("\n[CLIENT] Não pode conectar no Socket");
		exit(0);
	}
}

void *clientSocketThread() {
    char mensagem[PDU];
	while (1) {
		bzero(mensagem, sizeof(mensagem));

        if((recv(client, mensagem, sizeof(mensagem), 0)) < 0) {
			printf("\nERRO: Não é possível ler a mensagem enviada ao cliente!\n");
		}
		else if (mensagem[0] != '\0'){
			printf("\n[CLIENT] Recebi uma mensagem %s\n", mensagem);
        }
        usleep(100000);
    }
}

void enviaMensagem(char *mensagem) {
    if (client < 0) {
        printf("\nERRO: Não consigo enviar a mensagem!\n");
    }
    else {
        int response = send(client, mensagem, strlen(mensagem), 0);
        if (!response)
            printf("\nERRO: Não foi possivel enviar a mensagem!\n");
    }
}

void fechaSocket(){
    enviaMensagem("exit");
    close(client);
}