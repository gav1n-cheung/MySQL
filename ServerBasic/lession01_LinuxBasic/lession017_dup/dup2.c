/*
    #include <unistd.h>
    int dup2(int oldfd, int newfd);
        作用：重定向文件描述符
            oldfd指向了a.txt,newfd指向了b.txt
            调用函数成功后，newfd和b.txt做close,newfd 指向了a.txt
            oldfd必须是一个有效的文件描述符，如果newfd和oldfd值相同，则相当于什么都没有做
        返回值：
            就是newfd的文件描述符
*/
#include<unistd.h>
#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>

int main(){
    int fd = open("1.txt",O_RDWR | O_CREAT,0664);
    if(fd==-1){
        perror("open");
        return -1;
    }
    int fd1 = open("2.txt",O_RDONLY|O_CREAT,0664);
    if(fd==-1){
        perror("open");
        return -1;
    }
    printf("fd1:%d,fd2:%d\n",fd,fd1);
    int ret = dup2(fd,fd1);
    if(ret==-1){
        perror("dup2");
        return -1;
    }
    //通过fd1去写数据，实际操作的是1.txt,而非2.txt
    printf("fd1:%d,fd2:%d,new fd:%d\n",fd,fd1,ret);
    //因为ret=fd，因此关闭fd1或者fd2就可以了
    close(fd1);
    char *buf = "hello";
    int wirteBuf = write(fd,buf,strlen(buf));
    if(wirteBuf==-1){
        perror("write");
        return -1;
    }
    int fd2 = open("1.txt",O_RDWR | O_CREAT,0664);
    if(fd2==-1){
        perror("open");
        return -1;
    }
    printf("fd1:%d,fd2:%d,fd3:%d,new fd:%d\n",fd,fd1,fd2,ret);
    close(fd);
    close(fd2);
    return 0;
}