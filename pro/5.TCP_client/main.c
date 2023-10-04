#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <winsock2.h>
#include <unistd.h>
#pragma comment(lib, "ws2_32.lib")

//缓冲区大小
#define N 128

void Socket_Init();
int Socket_creat();




int main() {
    //变量定义区
    int sockfd;
    struct sockaddr_in serveraddr;    //服务器信息结构体
    int slen=sizeof (serveraddr);
    struct sockaddr_in clentaddr;    //客户端信息结构体
    int clent_len=sizeof (clentaddr);
    char sendbuffer[N]="";
    char recvbuffer[N]="";

    //初始化
    Socket_Init();
    sockfd=Socket_creat();

    serveraddr.sin_family=AF_INET;
    serveraddr.sin_addr.s_addr= inet_addr("192.168.177.1");
    serveraddr.sin_port= htons(7788);
    connect(sockfd,(struct sockaddr* )&serveraddr,slen);

    fgets(sendbuffer,N,stdin);
    sendbuffer[strlen(sendbuffer)-1]='\0';//结束符
    if(send(sockfd,sendbuffer,N,0)==-1)
    {
        printf("send_erro%d\n",WSAGetLastError());
        exit(1);
    }

    if(recv(sockfd,recvbuffer,N,0)==-1)
    {
        printf("recv_erro%d\n",WSAGetLastError());
        exit(1);
    }
    printf("server IP=%s,port:%d   %s\n",inet_ntoa(serveraddr.sin_addr), ntohs(serveraddr.sin_port),recvbuffer);

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