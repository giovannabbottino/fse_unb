#ifndef SERVER_H
#define SERVER_H

#include <stdio.h> /* printf() */
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h> /* struct sockaddr_in ntohs*/
#include <sys/socket.h> /* connect() send() bind() recv() */
#include <arpa/inet.h>  /* htons(), inet_addr() */
#include <sys/types.h> /* AF_INET, SOCK_STREAM pid_t */
#include <strings.h> /* bzero() */
#include <ctype.h> /* isdigit*/

#include <string.h>
#include "menu.h"

#define VETOR 5
#define PDU 200

typedef struct args{
    char * server_ip;
    int porta;
    int client;
    int server;
}Args;

int client;
int enviar;
char messagemServer[200];

int iniciaSocket(int porta, char * server_ip);
void *serverSocketThread(void * args);
void encerraSocket(int client, int server);
void *handlerMessageReceived(void *args);
void handlerSendMessage(int client);

#endif