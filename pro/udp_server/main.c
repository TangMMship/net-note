#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <winsock2.h>
#include <unistd.h>
#pragma comment(lib, "ws2_32.lib")

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
    int sockfd= socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if(sockfd==-1)
    {
        printf("创建socket错误\n");
        exit(1);
    }
    return sockfd;
}



int main() {
    //变量初始化
    int  sockfd=0;
    char sendbuffer[128]="hello";
    char recvbuffer[128]="";
    //服务器信息结构体
    struct sockaddr_in serveraddr;
    int tolenip=sizeof (serveraddr);
    //客户端信息结构体
    struct sockaddr_in clentaddr;
    int clent_len=sizeof (clentaddr);

    Socket_Init();
    sockfd=Socket_creat();


    serveraddr.sin_family=AF_INET;
    serveraddr.sin_addr.s_addr= inet_addr("192.168.177.1");
    serveraddr.sin_port= htons(7788);
    bind(sockfd,(struct sockaddr*)&serveraddr,tolenip);


    while(1)
    {
        memset(recvbuffer,0,128);
        if(recvfrom(sockfd,recvbuffer,sizeof (recvbuffer),0,(struct sockaddr *)&clentaddr,&clent_len)==-1)
        {
            printf("recv_erro%d\n",WSAGetLastError());
            exit(1);
        }
        printf("IP=%s,port:%d   %s\n", inet_ntoa(clentaddr.sin_addr), ntohs(clentaddr.sin_port),recvbuffer);
        sendbuffer[strlen(sendbuffer) - 1] = '\0';      //手动加结束符
        sendto(sockfd, sendbuffer, sizeof(sendbuffer), 0, (struct sockaddr *) &clentaddr, clent_len);

    }
    return 0;
}
