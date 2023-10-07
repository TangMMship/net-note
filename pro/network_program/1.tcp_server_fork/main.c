#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>          
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

#define N 128
 
void handler(){
    //处理僵尸进程
	wait(NULL);
}
 
 
int main(int argc , char *argv[])
{  
  	if(argc<3)
	{
		printf("fail : lose ip port\n");
		exit(1);
		
	}
 
    int sockfd;

    signal(SIGCHLD,handler);


    if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1)
    {
        perror("fail to sockfd");
        exit(1);
    }
    struct sockaddr_in serveraddr;
    struct sockaddr_in clientaddr;

    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port = htons(atoi(argv[2]));
    serveraddr.sin_addr.s_addr =inet_addr(argv[1]);
    socklen_t addrlen =sizeof(serveraddr);


    if(bind(sockfd,(struct sockaddr *)&serveraddr,addrlen)==-1)
    {
        perror("fail to bind");
        exit(1);
    }

    if(listen(sockfd,5)==-1)
    {
        perror("fail to listen");
        exit(1);
    }
    

    pid_t pid;
    int acceptfd;
    while(1)
    {
        
        if((acceptfd=accept(sockfd,(struct sockaddr*)&clientaddr,&addrlen))==-1)
        {
            perror("fail to acceptfd");
            exit(1);
            
        }
        printf("reciver from ip = %s ,port:%d\n",inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));


        pid=fork();

        if(pid<0)
        {

            perror("fail to fork");
            exit(1);

        }

        //父进程空，直接运行到accept等待下一个客户端连接
        else if(pid>0)
        {

        }
        //每个连接的客户端都通过一个子进程通信
        else
        {

                ssize_t byte;

            while(1)
            {
                char text[N]="";
                char buf[N]="";
                if((byte=recv(acceptfd,buf,N,0))==-1)
                {					
                    perror("fail to recv");
                    exit(1);
                }

                else if(byte==0)
                {
                    printf("the client quit\n");
                    exit(1);
                }
                    

                printf("from client :%s\n",buf);

                    
                strcat(text,"^_^") ;

                if(send(acceptfd,text,N,0)==-1)
                {
                    perror("fail to ssend");
                    exit(1);
                }

            } 
        }	   
    }  
	
 
	return 0;
}