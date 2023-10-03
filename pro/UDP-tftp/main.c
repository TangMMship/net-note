#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <winsock2.h>
#include <unistd.h>
#include <io.h>
#include <fcntl.h>
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
void TFPT_clent_download(int sockfd,struct sockaddr_in serveraddr)
{
    int flag=0;
    int num=1;    //块编号
    int bytes;
    FILE *fd1;
    int fd;
    unsigned char send_cmd[1024]="";
    char filename[128]="hello.txt";
    unsigned char recvbuffer[1024]="";
    int send_cmd_len=0;
    struct sockaddr_in clentaddr;
    int slen=sizeof (clentaddr);

    //01下载操作数  %s文件名  0间隔 模式 0间隔   构建发送指令
    send_cmd_len=sprintf(send_cmd,"%c%c%s%c%s%c",0,1,filename,0,"octet",0);
    if(sendto(sockfd,send_cmd,send_cmd_len,0,(struct sockaddr *)&serveraddr,slen)==-1)
    {
        printf("send_cmd_erro\n");
        exit(1);
    }
    while(1)
    {
        memset(recvbuffer,0,sizeof (recvbuffer));
        bytes=recvfrom(sockfd,recvbuffer,sizeof (recvbuffer),0,(struct sockaddr *)&clentaddr,&slen);
        if(bytes==-1)
        {
            printf("recv_erro%d\n",WSAGetLastError());
            exit(1);
        }
        if(recvbuffer[1]==5)
        {
            printf("erro:5 %s\n", recvbuffer+4);//打印差错信息
        }
        if(recvbuffer[1]==3)
        {
            //成功接收到数据包
            if(flag==0)         //判断是否是第一次接收到数据包
            {
                flag=1;
                //O_WRONLY  只写模式
                //O_CREAT   如果指定文件不存在，则创建这个文件
                //O_TRUNC   如果文件存在，并且以只写/读写方式打开，则清空文件全部内容(即将其长度截短为0)
                if((fd=open(filename,O_WRONLY|O_CREAT|O_TRUNC,0664))==-1)
                {
                    printf("erro_filecreat\n");
                    exit(1);
                }
            }
            if((num==ntohs(*(unsigned short *) (recvbuffer+2)))&&(bytes==516))
            {
                num=num+1;
                if(write(fd,recvbuffer+4,bytes-4)<0)     //前4个字节是命令，后面才是数据
                {
                    printf("erro_write_erro\n");
                    exit(1);
                }

                //发送ack包
                recvbuffer[1]=4;    //操作数=4
                printf("IP=%s,port:%d\n", inet_ntoa(clentaddr.sin_addr), ntohs(clentaddr.sin_port));
                if(sendto(sockfd,recvbuffer,4,0,(struct sockaddr *)&clentaddr,slen)==-1)
                {
                    printf("erro_ack_erro\n");
                    exit(1);
                }

            }
            if((num==ntohs(*(unsigned short *) (recvbuffer+2)))&&(bytes<516)) {
                if (write(fd, recvbuffer + 4, bytes - 4) == -1)     //前4个字节是命令，后面才是数据
                {
                    printf("erro_write_erro\n");
                    exit(1);
                }
                //发送ack包
                recvbuffer[1]=4;    //操作数=4
                if(sendto(sockfd,recvbuffer,4,0,(struct sockaddr *)&serveraddr,slen)==-1)
                {
                    printf("erro_ack_erro\n");
                    exit(1);
                }
                printf("下载完成\n");
                return;
            }
        }

    }

}

int main() {
    int  sockfd=0;
    //服务器信息结构体
    struct sockaddr_in serveraddr;
    int tolenip=sizeof (serveraddr);


    Socket_Init();
    sockfd=Socket_creat();

    //服务器信息初始化
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_addr.s_addr= inet_addr("192.168.79.1");
    serveraddr.sin_port= htons(69);     //tftp固定端口号69
    TFPT_clent_download(sockfd,serveraddr);
    return 0;
}
