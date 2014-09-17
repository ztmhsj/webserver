#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#define MAXSIZE 4096
extern void p_error(char *,int );
char *read_cmd(int sockcnfd,char *cmd);
void process_cmd(int sockcnfd,char *cmd);
int is_noexit(char *url);
int is_dir(char *url);
void send_404(int sockcnfd);
void re_ls(int sockcnfd,char *url);
void re_file(int sockcnfd,char *url);
void answer(int sockcnfd,int code,char *code_mess,char *type,char *content);
int get_url(int sockcnfd,char *cmd,char *url);
