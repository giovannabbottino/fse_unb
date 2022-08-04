#include "server.h"

int client;

int vetor[VETOR] = {0};
int enviar = 0;
char messagemServer[PDU] = "";

int iniciaSocket(int porta, char * server_ip) {
    /* Criacao do socket TCP */
    int server = socket(AF_INET, SOCK_STREAM, 0);
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
	
	struct sockaddr_in serverSocket;

	/* Preenchendo informacoes sobre o cliente */
	serverSocket.sin_family = AF_INET;
	serverSocket.sin_addr.s_addr = inet_addr(server_ip); 
	serverSocket.sin_port = htons(porta);

	/* Inicia a conexão no socket */
	if (bind(server, (struct sockaddr *)&serverSocket, sizeof(serverSocket))<0){
		perror("\n[SERVER] Não pode conectar no Socket\n");
		exit(1);
	}

	if(listen(server, 10) < 0) {
		perror("\n[SERVER] Não pode escutar server socket\n");
		exit(1);
	}

	return server;
}

void *serverSocketThread(void *args){
	Args *actual_args = args;
	struct sockaddr_in clientSocket;
	int server = iniciaSocket(actual_args->porta, actual_args->server_ip);
	int size = sizeof(clientSocket);
	 /* Aceita conexoes direta entre o servidor e cliente */
    client = accept(server, (struct sockaddr *) &clientSocket, &size);
    if ( client == -1 ){
        perror("[SERVER] Não pode dar accept na PORT");
        exit(0);
    } 
    printf("[SERVER] Aceita conexoes direta\n");
	
	pthread_t receberThread;

	Args * args_1 = (Args *) malloc((Args *) sizeof(Args));
	
    args_1->client = client;
    args_1->server = server;

	pthread_create(&receberThread, NULL, &handlerMessageReceived, args_1);
    pthread_detach(receberThread);

	handlerSendMessage(client);
}

void encerraSocket(int client, int server) {
	close(client);
	close(server);
}

void *handlerMessageReceived(void *args) {
	Args *actual_args = args;
	int client = actual_args->client;
	int server = actual_args->server;
	int retorno_msg;
	while (1) {
		retorno_msg = recv(client, vetor, VETOR * sizeof(int), 0);
		
		if(retorno_msg == 0){
			printf("[SERVER] Conexão Encerrada!\n");
			encerraSocket(client, server);
			exit(0);
		}else if (retorno_msg < 0){
			printf("[SERVER] Não foi possivel receber a mensagem");
		} else{ 
			printf("[SERVER] Cruzamento: %d\n", vetor[0]);
			printf("\t\t\tPassagem de carros: %d\n", vetor[1]);
			printf("\t\t\tAcima da velocidade: %d\n", vetor[2]);
			printf("\t\t\tAvanço no vermelho: %d\n", vetor[3]);
			printf("\t\t\tVelocidade média: %f\n", vetor[4]);
		}
	}
}

void handlerSendMessage(int client) {
	while (1) {
		if (enviar == 1){
			if(send(client, messagemServer, sizeof(messagemServer), 0) < 0){
				perror("[SERVER] Falha no envio");
			} else{
				printf("[SERVER] Mensagem enviada foi: %s\n", messagemServer);
			}
			enviar = 0;
		}
	}
}
