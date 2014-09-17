#ifndef NETH
#define NETH
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<errno.h>
#include<stdlib.h>
#include<stdio.h>
#include<netinet/in.h>
#define SERVER_PORT 9999
#define SERVER_LISNUM 99
void p_error(char *x,int y);
int make_server_socket(int port,int listen);
int server_accept(int sockfd,struct sockaddr_in* soad);
#endif
