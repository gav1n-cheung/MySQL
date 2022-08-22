#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

int main(){
    int fd = open("fifo1",O_RDONLY);
    int fd1 = open("fifo2",O_WRONLY);
    if(fd==-1){
        perror("fd open");
        exit(0);
    }
    printf("打开管道fifo1成功，等待读取....\n");
    if(fd1==-1){
        perror("fd1 open");
        exit(0);
    }
    printf("打开管道fifo2成功，等待写入....\n");
    pid_t pid = fork();

    char buf[128]={0};
    while(1){
        if(pid>0){
            char* recv[1024]={0};
            int ret = read(fd,recv,sizeof(recv));
            if(ret<=0){
                perror("read");
                exit(0);            
            }
            printf("收到消息%s\n",recv);
        }else if(pid==0){
            memset(buf,0,128);
            printf("请输入消息\n");
            fgets(buf,128,stdin);
            int ret = write(fd1,buf,sizeof(buf));
            if(ret==-1){
                perror("write");
                exit(0);
            }
            printf("发送成功%s\n",buf);
        }else{
            exit(0);
        }
    }
    close(fd);
    close(fd1);
    return 0;
}