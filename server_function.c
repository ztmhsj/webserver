#include"server_f.h"
char *read_cmd(int sockcnfd,char *cmd)
{
	char buf[MAXSIZE];
	FILE *rfp=fdopen(sockcnfd,"r");
	char *ermess="the client is error\n";
	if(fgets(cmd,MAXSIZE,rfp)!=NULL){
		fputs("recive is \n",stdout);
		fputs(cmd,stdout);
		while(fgets(buf,MAXSIZE,rfp)!=NULL){
			fputs(buf,stdout);
			if(strcmp(buf,"\r\n")==0)
				return cmd;
		}
	}
	fputs(ermess,stdout);
	return NULL;
}
void process_cmd(int sockcnfd,char *cmd)
{
	char url[MAXSIZE]="./www";
	char buf[MAXSIZE];
	if(get_url(sockcnfd,cmd,url)!=-1){
		printf("get url is %s\n",url);
		if(is_noexit(url))
			send_404(sockcnfd);
		else if(is_dir(url))
			re_ls(sockcnfd,url);
		else
			re_file(sockcnfd,url);
	}
	close(sockcnfd);
}
int is_noexit(char *url)
{
	return access(url,F_OK)<0?1:0;
}
void send_404(int sockcnfd)
{
	char *head="HTTP/1.1 404 Not Foun\r\n\r\n";
	char *content="<h1 style=color:red align=center>\
		       404: Not found</h1>";
	if(access("./mess_404",0)>=9){
		//write(sockcnfd,head,strlen(head));
		answer(sockcnfd,404,"Not Found","text/html",NULL);
		re_file(sockcnfd,"./mess_404");
	}
	else
		answer(sockcnfd,404,"Not Found","text/html",content);
}
int is_dir(char *url)
{
	struct stat st;
	if(stat(url,&st)<0)
		p_error("error in is_dir logic error",5);
	return S_ISDIR(st.st_mode)?1:0;
}
void re_ls(int sockcnfd,char *url)
{
	char buf[MAXSIZE]="ls ";
	strcat(buf,url);
	FILE *fp=popen(buf,"r");
	while(fgets(buf,MAXSIZE,fp))
		write(sockcnfd,buf,strlen(buf));
	pclose(fp);
}
void re_file(int sockcnfd,char *url)
{
	char buf[MAXSIZE];
	FILE *fp=fopen(url,"r");
	if(strcmp(url,"./mess_404"))
		answer(sockcnfd,200,"OK",NULL,NULL);
	while(fgets(buf,MAXSIZE,fp))
		write(sockcnfd,buf,strlen(buf));

}
void answer(int sockcnfd,int code,char *code_mes,char *type,char *content)
{
	FILE *fp=fdopen(sockcnfd,"w+");
	fprintf(fp,"HTTP/1.1 %d %s\r\n",code,code_mes);
	if(type)
		fprintf(fp,"Content-type: %s\r\n",type);
	fprintf(fp,"\r\n");
	if(content)
		fprintf(fp,"%s\r\n",content);
	fflush(fp); //fflush can be flush
}
int get_url(int sockcnfd,char *cmd,char *url)
{
	char *cpt;
	char buf[MAXSIZE];
	if(strncmp(cmd,"GET",3)!=0){
		answer(sockcnfd,501,"not implemented",
			"text/plain","request error");
		printf("request error \n");
		return -1;
	}
	cpt=strchr(cmd,'/');
	sscanf(cpt,"%s",buf);
	strcat(url,buf);
	return 0;
}
	
