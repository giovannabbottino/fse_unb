#include "server.h"
#include <string.h>

struct sockaddr_in serverSocket, clientSocket; /* socket do servidor */
char *server_ip;
unsigned short porta;
int server, client;
char clientMessagem[PDU];

void iniciaSocket(int porta, char * server_ip) {
    server_ip = server_ip;
    porta = porta;
    /* Criacao do socket TCP */
    server = socket(AF_INET, SOCK_STREAM, 0);
        /*
        * ARPA INTERNET PROTOCOLS -- IPv4
        * SOCK_STREAM orientado a conexão com transmissão de fluxos de bytes, sequencial e bidirecional
        * 0 - protocolo padrao para o tipo escolhido -- TCP
        */
    if (server < 0){ 
        perror("\n[SERVER] Criação do socket falhou");
        exit(1);
    }
    printf("\n[SERVER] Criacao do socket TCP\n");

	/* Preenchendo informacoes sobre o cliente */
	serverSocket.sin_family = AF_INET;
	serverSocket.sin_addr.s_addr = inet_addr(server_ip); 
	serverSocket.sin_port = htons(porta);

	/* Inicia a conexão no socket */
	if (bind(server, (struct sockaddr *)&serverSocket, sizeof(serverSocket))<0){
		perror("\n[SERVER] Não pode conectar no Socket\n");
		exit(1);
	}

    memset(clientMessagem, '\0', sizeof(clientMessagem));

	if(listen(server, 10) < 0) {
		perror("\n[SERVER] Não pode escutar server socket\n");
		exit(1);
	}
}

void *serverSocketThread(){
	
	if(listen(server, 10) < 0) {
		perror("[SERVER] Não é possivel escutar server socket\n");
		exit(1);
	}
	 /* Aceita conexoes direta entre o servidor e cliente */
    socklen_t client_size = sizeof(clientSocket);
    client = accept(server, (struct sockaddr *) &clientSocket, &client_size);
    if ( client == -1 ){
        perror("[SERVER] Não pode dar accept na PORT");
        exit(0);
    } 
    printf("[SERVER] Aceita conexoes direta\n");

	pthread_t recebeThread, enviaThread;

	pthread_create(&recebeThread, NULL, &handlerMessageReceived, NULL);
    pthread_detach(recebeThread);

	pthread_create(&enviaThread, NULL, &handlerSendMessage, NULL);
    pthread_detach(enviaThread);

	return 0;
}

void encerraSocket() {
	close(client);
	close(server);
}

void * handlerMessageReceived() {
	int count;
	
	while (1) {
		bzero(clientMessagem, sizeof(clientMessagem));

		if (count > 20) break;

		if((recv(client, clientMessagem, sizeof(clientMessagem), 0)) < 0) {
			printf("[SERVER] Não é possivel ler a mensagem\n");
			count++;
		}

		else if (clientMessagem[0] == '\0') count++;

		else {
			printf("[SERVER] Recebi a mensagem:\n\n%s\n", clientMessagem);
		}
	}
	handlerMessageReceived();
}

void * handlerSendMessage() {
	char messagem[PDU];
	bzero(messagem, PDU); /* apaga a informacao*/
            
	/* Menu de interação */
	printf("\n>>>[MENU] Esperando por mensagem<<<\n");
	fgets(messagem, sizeof(messagem), stdin);
            
	if(send(client, messagem, sizeof(messagem), 0) < 0){
		perror("[SERVER] Falha no envio");
	} else{
		printf("[SERVER] Mensagem enviada foi: %s\n", messagem);
	}
	handlerSendMessage();
}
