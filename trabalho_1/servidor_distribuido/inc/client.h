#ifndef CLIENT_H
#define CLIENT_H

#include <stdio.h> /* printf() */
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h> /* struct sockaddr_in */
#include <sys/socket.h> /* connect() send() bind() recv() */
#include <arpa/inet.h>  /* htons(), inet_addr() */
#include <sys/types.h> /* AF_INET, SOCK_STREAM pid_t */
#include <strings.h> /* bzero() */
#include <ctype.h> /* isdigit*/

#include "mensagem.h"

#define VETOR 5
#define PDU 200

void iniciaSocket(int porta, char * server_ip) ;
void *clientSocketThread();
void enviaMensagem(int * mensagem);
void fechaSocket();

#endif