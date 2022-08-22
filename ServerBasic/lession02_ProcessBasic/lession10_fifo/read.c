#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
    int fd = open("fifo1",O_RDONLY);//如果不开写端，则程序在此阻塞
    if(fd==-1){
        perror("open");
        exit(0);
    }
    printf("read file open");
    char buf[1024]={0};
    int ret = -1;
    while((ret = read(fd,buf,sizeof(buf))>0)){
        printf("read %s\n",buf);
        memset(buf,0,1024);
    }
    close(fd);
    return 0;

}