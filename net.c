#include"net.h"
int make_server_socket(int port,int listenum)
{
	struct sockaddr_in soadd;
	int sockfd,setval=1;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
        if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&setval,sizeof(setval))<0)
		p_error("error in setsockopt",5);
	soadd.sin_family=AF_INET;
	soadd.sin_port=htons(port);
	soadd.sin_addr.s_addr=INADDR_ANY;
	if(bind(sockfd,(struct sockaddr*)&soadd,sizeof(soadd))<0)
		p_error("error in server bind",1);
	if(listen(sockfd,listenum)<0)
		p_error("error in listen",2);
	return sockfd;
}
int server_accept(int sockfd,struct sockaddr_in *soad)
{
	int rv;
	int sizesoadd=sizeof(*soad);
	rv=accept(sockfd,(struct sockaddr *)soad,&sizesoadd);
	if(rv<0)
		p_error("error in accept",3);
	else printf("alrealy accept\n");
	printf("connect ip is %s\n",inet_ntoa(soad->sin_addr));
	return rv;
}
void p_error(char *x,int y)
{
	perror(x);
	exit(y);
}
