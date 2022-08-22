#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

int main(){
    int ret = access("fifo1",F_OK);
    if(ret==-1){
        printf("fifo not exist, will create the file\n");
        //2.如果管道不存在则创建管道文件
        ret = mkfifo("fifo1",0664);
        if(ret==-1){
            perror("mkfifo");
            exit(0);
        }
    }
    ret = access("fifo2",F_OK);
    if(ret==-1){
        printf("fifo not exist, will create the file\n");
        //2.如果管道不存在则创建管道文件
        ret = mkfifo("fifo2",0664);
        if(ret==-1){
            perror("mkfifo2");
            exit(0);
        }
    }
    int fd = open("fifo1",O_WRONLY);
    int fd1 = open("fifo2",O_RDONLY);
    if(fd==-1){
        perror("fd open");
        exit(0);
    }
    printf("打开管道fifo1成功，等待写入....\n");
    if(fd1==-1){
        perror("fd1 open");
        exit(0);
    }
    printf("打开管道fifo2成功，等待读取....\n");    
    pid_t pid = fork();
    char buf[128]={0};
    while(1){
        if(pid>0){
            memset(buf,0,128);
            printf("请输入消息\n");
            fgets(buf,128,stdin);
            ret = write(fd,buf,sizeof(buf));
            if(ret==-1){
                perror("write");
                exit(0);
            }
            printf("发送成功%s\n",buf);
        }else if(pid==0){
            char* recv[1024]={0};
            ret = read(fd1,recv,sizeof(recv));
            if(ret<=0){
                perror("read");
                exit(0);            
            }
            printf("收到消息%s\n",recv);
        }else{
            exit(0);
        }
    }
    close(fd);
    close(fd1);
    return 0;
}