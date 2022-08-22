/*
    #include <unistd.h>

    int chdir(const char *path);
        作用: 修改进程的工作目录
        参数:
            - path : 需要修改的工作目录
    
    #include <unistd.h>

    char *getcwd(char *buf, size_t size);
        作用：获取当前的工作目录
        参数：
            - buf : 存储的路径，指向的是一个数组
            - size: 数组的大小
        返回值：
            返回的指向的一块内存，这个数据就是第一个参数
*/
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(){

    //获取当前的工作目录
    char path[1024];
    getcwd(path,sizeof(path));
    printf("currnt work path : %s\n",path);
    int ret = chdir("../");
    if(ret==-1){
        perror("chdir");
        return -1;
    }
    int newFile = open("chdir.txt",O_RDWR|O_CREAT,0664);
    if(newFile==-1){
        perror("open");
        return -1;
    }
    char buf[1024];
    getcwd(buf,sizeof(buf));
    printf("currnt work path : %s\n",buf);
    return 0;
}