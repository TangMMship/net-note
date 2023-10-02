#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <winsock2.h>
#include <unistd.h>

#pragma comment(lib, "ws2_32.lib")
int main() {
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

    int sockfd;     //用于保存sock的返回值，返回值是一个文件描述符
    //创建socket，用于udp网络编程  protocol为0表示自动选择与socket类型对应的协议
    //if用来判断创建是否成功
    sockfd=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
    if(sockfd==-1)
    {
        printf("创建socket错误\n");
        exit(1);
    }
    printf("套接字sockfd=%d\n",sockfd);

    //服务器信息结构体
    struct sockaddr_in serveraddr;
    int tolenip=sizeof (serveraddr);
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_addr.s_addr= inet_addr("192.168.177.1");
    serveraddr.sin_port= htons(7788);
    sendto(sockfd,"你好",8,0,(struct sockaddr *)&serveraddr,tolenip);
    char sendbuffer[128]="";
    char recvbuffer[128]="";
    while(1)
    {
        fgets(sendbuffer,128,stdin);
        sendbuffer[strlen(sendbuffer)-1]='\0';      //手动加结束符
        if(sendto(sockfd,sendbuffer,sizeof(sendbuffer),0,(struct sockaddr *)&serveraddr,tolenip)==-1)
        {
            printf("send_erro");
            exit(1);
        }
        if(recvfrom(sockfd,recvbuffer,sizeof (recvbuffer),0,(struct sockaddr *)&serveraddr,&tolenip)==-1)
        {
            printf("recv_erro%d\n",WSAGetLastError());
            exit(1);
        }
        if(strstr(recvbuffer,"ok"))
        {
            printf("recv%s\n",recvbuffer);
            memset(recvbuffer,0,128);
            closesocket(sockfd);
            WSACleanup();
        }
    }
    close(sockfd);
    return 0;
}
