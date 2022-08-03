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

#define VETOR 4
#define PDU 200

void iniciaSocket(int porta, char * server_ip);
void *serverSocketThread();
void encerraSocket();
void handlerMessageReceived();
void handlerSendMessage();

#endif