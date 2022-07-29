#include "server.h"
#include <string.h>

struct sockaddr_in serverSocket; /* socket do servidor */
char *server_ip;
unsigned short porta;
int server;
char clientMessagem[PDU];

void iniciaSocket(int porta, char * server_ip) {
    server_ip = server_ip;
    porta = porta;
    /* Criacao do socket TCP */
    server = socket(AF_INET, SOCK_STREAM, 0);
    if (server == 0){ 
        /*
        * ARPA INTERNET PROTOCOLS -- IPv4
        * SOCK_STREAM orientado a conexão com transmissão de fluxos de bytes, sequencial e bidirecional
        * 0 - protocolo padrao para o tipo escolhido -- TCP
        */
        perror("\n[SERVER] Criação do socket falhou");
        fechaSocket(server);
    }
    printf("\n[SERVER] Criacao do socket TCP\n");

    memset(&clientMessagem, 0, sizeof(clientMessagem));

	/* Preenchendo informacoes sobre o cliente */
	serverSocket.sin_family = AF_INET;
	serverSocket.sin_addr.s_addr = inet_addr(server_ip); 
	serverSocket.sin_port = htons(porta);

	/* Inicia a conexão no socket */
	if (connect(client, (struct sockaddr *)&server, sizeof(server))<0){
		perror("\n[SERVER] Não pode conectar no Socket\n");
		exit(0);
	}

    memset(clientMessagem, '\0', sizeof(clientMessagem));
	criaServerSocket();

	int bindingPort = 0;
	bindingPort = bind(server, (struct sockaddr *)&serverSocket, sizeof(serverSocket));

	if(bindingPort < 0) {
		printf("\n[SERVER] Não pode conectar na porta %d\n", porta);
		exit(1);
	}

	if(listen(server, 10) < 0) {
		printf("\n[SERVER] Não pode escutar server socket\n");
		exit(1);
	}
}