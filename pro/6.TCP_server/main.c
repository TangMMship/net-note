#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <winsock2.h>
#include <unistd.h>
#pragma comment(lib, "ws2_32.lib")

#define N 128

void Socket_Init();
int Socket_creat();
void erroinf(char* erro_type);



int main() {
    //变量定义区
    int sockfd;
    char sendbuffer[N]="";
    char recvbuffer[N]="";
    struct sockaddr_in serveraddr;    //服务器信息结构体
    int tolenip=sizeof (serveraddr);
    struct sockaddr_in clentaddr;    //客户端信息结构体
    int clent_len=sizeof (clentaddr);
    int acceptfd;

    //初始化
    Socket_Init();
    sockfd=Socket_creat();

    serveraddr.sin_family=AF_INET;
    serveraddr.sin_addr.s_addr= inet_addr("192.168.177.1");
    serveraddr.sin_port= htons(7788);
    if(bind(sockfd,(struct sockaddr*)&serveraddr,tolenip)==-1)
    {
        printf("bind_erro%d\n",WSAGetLastError());
        exit(1);
    }
    if(listen(sockfd,10)==-1)
    {
        erroinf("listen");
    }
    if((acceptfd=accept(sockfd,(struct sockaddr*)&clentaddr,&clent_len))==-1)
    {
        erroinf("accept");
    }

    if(recv(acceptfd,recvbuffer,N,0)==-1)
    {
        erroinf("recv");
    }
    printf("IP=%s,port:%d   %s\n", inet_ntoa(clentaddr.sin_addr), ntohs(clentaddr.sin_port),recvbuffer);


    fgets(sendbuffer,N,stdin);
    sendbuffer[strlen(sendbuffer)-1]='\0';//结束符
    if(send(acceptfd,sendbuffer,N,0)==-1)
    {
        erroinf("send");
    }

    closesocket(sockfd);
    return 0;
}




void Socket_Init()
{
    //启动socket
    WORD wVersionRequested;
    WSADATA wsaData;
    int err;
    wVersionRequested = MAKEWORD(2, 2);
    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        printf("WSAStartup failed with error: %d\n", err);
        system("pause");
        exit(1);
    }
}

int Socket_creat()
{
    int sockfd= socket(AF_INET,SOCK_STREAM,0);//tcp是字节流式协议 用流式套接字SOCK_STREAM
    if(sockfd==-1)
    {
        printf("创建socket错误\n");
        exit(1);
    }
    return sockfd;
}

void erroinf(char* erro_type)
{
    printf("%s_erro%d\n",erro_type,WSAGetLastError());
    exit(1);
}