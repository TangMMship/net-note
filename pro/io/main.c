#include <stdio.h>
#include <io.h>
#include <fcntl.h>

int main() {
    char data[1024]="";
    int size=0;
    int fd=open("hello.txt",O_WRONLY|O_CREAT|O_TRUNC,0664);
    int fd2=open("x.txt",O_RDONLY);
    if((size=read(fd2,data,sizeof (data)))==-1)
    {
        printf("erro 0\n");
    }
    if(write(fd,data,size)==-1)
    {
        printf("erro 1\n");
    }
    return 0;
}
