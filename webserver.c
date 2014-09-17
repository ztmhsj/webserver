#include<stdio.h>
#include<unistd.h>
#include"net.h"
#include<string.h>
#include"server_f.h"
#include<pthread.h>
#define CUN "connect is over\n"
void *process_accept(void *);
long long server_byte_sent=0;
int server_request=0;
int main(void)
{
	pthread_t worker;
	pthread_attr_t attrt;
	pthread_attr_init(&attrt);
	pthread_attr_setdetachstate(&attrt,PTHREAD_CREATE_DETACHED);
	int sockfd,sockcnfd;
	FILE *sockfp;
	struct sockaddr_in clsockaddr;
	sockfd=make_server_socket(SERVER_PORT,SERVER_LISNUM);
	while(1){
		sockcnfd=server_accept(sockfd,&clsockaddr);
		pthread_create(&worker,&attrt,process_accept,&sockcnfd);
	}
	return 0;
}
void *process_accept(void *ptsockcnfd)
{
	char cmd[MAXSIZE];
	int sockcnfd=*(int *)ptsockcnfd;
	printf("sockcnfd %d\n",sockcnfd);
	if(read_cmd(sockcnfd,cmd)!=NULL)
		printf("get cmd is %s\n",cmd);
	else{
		printf("nothing recive\n");
		close(sockcnfd);
		return NULL;
	}
	process_cmd(sockcnfd,cmd);
}
