#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
//有名管道的注意事项
/*
    有名管道的注意事项：
        1.一个打开一个只读管道的进程会阻塞，直到另外一个为只写的进程打开管道
        2.一个打开一个只写管道的进程会阻塞，直到另外一个为只写的进程打开管道
    读写特性：
    读管道：
        管道中有数据，read会返回实际读到的字节数
        管道中无数据：
            管道写端被全部关闭，read返回0，相当于读到文件末尾
            管道写端没有全部关闭，read会阻塞等待
    写管道：
        管道读端被全部关闭，进程会异常终止(收到一个SIGPIPE信号)
        管道读端没有全部关闭：
            管道已经满了，write会阻塞
            管道没有满，write会将数据写入，并返回实际写入的字节数


*/


int main(){
    //1.判断文件是否存在
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
    //3.打开管道文件
    int fd = open("fifo1",O_WRONLY);
    if(fd==-1){
        perror("open");
        exit(0);
    }
    for(int i=0;i<100;i++){
        char buf[1024]={0};
        sprintf(buf,"hello,%d\n",i);
        printf("write data:%s\n",buf);
        ret = write(fd,buf,strlen(buf));
        if(ret==-1){
            perror("write");
            exit(0);
        }
        sleep(1);
    }
    close(fd);

    return 0;
}