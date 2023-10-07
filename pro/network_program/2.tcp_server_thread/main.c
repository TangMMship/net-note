#include<stdio.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <pthread.h>
#include<string.h>
#include<unistd.h>
 
 
#define N 128
typedef struct
{
	struct sockaddr_in addr;
	  int acceptfd ;
	
	
	}MSG;
 
void * pthread_fun(void *arg)
{
	  char buf[N]="";
	  ssize_t size ;
	 MSG msg = *(MSG *)arg;
     while(1)
	 {
		 char text[N]="";
		 if((size=recv(msg.acceptfd,buf,N,0))==-1)
		 {
			 perror("fail to recv");
			 pthread_exit(NULL);
			 }
		 else if(size ==0)
		 {
			 perror("quit client");
			 pthread_exit(NULL);
			 
			 }
		 printf("[%s ‐ %d]: %s\n", inet_ntoa(msg.addr.sin_addr), ntohs(msg.addr.sin_port), buf);
 
         strcat(text," ^_^");
 
         if(send(msg.acceptfd,text,N,0)==-1)
		 {
			 perror("fail to send");
			 exit(1);
			 }
		 }	 
	
	 }
 
int main(int argc ,char *argv[])
{ 
     if(argc <3)
	 {
		 printf("fail ; lose ip port \n");
		 exit(1);
		 }
 
	 int sockfd;
 
	 if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
	 {
		 perror("fail to socket");
		 exit(1);
 
		 }
	 int on=1;
 
	 if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on))<0)
	 {
		 perror("fail to setsockopt");
		 exit(1);
		 }
    
	struct sockaddr_in mysockaddr;
	struct sockaddr_in clientaddr;
 
	mysockaddr.sin_family=AF_INET;
	mysockaddr.sin_port = htons(atoi(argv[2]));
	mysockaddr.sin_addr.s_addr=inet_addr(argv[1]);
	socklen_t socklen = sizeof(mysockaddr);
 
    socklen_t addrlen = sizeof(clientaddr);
 
    if(bind(sockfd,(struct sockaddr *)&mysockaddr,socklen)==-1)
	{
		perror("fail to bind");
		exit(1);
		}
	
	 if(listen(sockfd,5)==-1)
	 {
		 perror("fail to listen");
		 exit(1);
		 }
	  int acceptfd;
	 while(1)
	 {
		 if((acceptfd=accept(sockfd,(struct sockaddr *)&clientaddr,&addrlen))==-1)
		 {
			  perror("fail to accept");
			  exit(1);
			   }
		  MSG msg;
		  msg.addr = clientaddr;
          msg.acceptfd=acceptfd; 
		  
          pthread_t thread;
 
		  if(pthread_create(&thread,NULL,pthread_fun,&msg)!=0)
		{
			perror("fail to pthread_create");
			exit(1);
 
 			}	  
             pthread_detach(thread);
 
		  
		 }	
	
	return 0;
	}