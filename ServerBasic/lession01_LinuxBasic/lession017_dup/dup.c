/*
    #include <unistd.h>
    int dup(int oldfd);
        作用：复制一个新的文件描述符
        fd=3,int fd1 = dup(fd)
        fd1指向的是a.txt,fd1也是指向a.txt
        从空闲的文件描述符中找一个最小的，作为一个新的文件描述符

    int dup2(int oldfd, int newfd);
*/
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>

int main(){
    int fd = open("a.txt",O_RDWR | O_CREAT,0664);
    int fd1 = dup(fd);

    if(fd1==-1){
        perror("open");
        return -1;
    }
    printf("fd:%d,fd1:%d\n",fd,fd1);
    close(fd);
    char *str = "hello world";
    int ret = write(fd1,str,strlen(str));
    if(ret==-1){
        perror("write");
        return -1;
    }
    char *str1 = "hello";
    int ret1 = write(fd1,str1,strlen(str1));
    if(ret1==-1){
        perror("write");
        return -1;
    }
    close(fd1);
    printf("fd:%d,fd1:%d\n",fd,fd1);
    return 0;
}