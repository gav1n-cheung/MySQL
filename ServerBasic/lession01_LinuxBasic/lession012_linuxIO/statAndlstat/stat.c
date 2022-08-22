/*
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <unistd.h>

    int stat(const char *pathname, struct stat *statbuf);
        作用：获取一个文件相关的信息
        参数: 
            - pathname : 操作的文件路径
            - statbuf: 结构体变量，传出参数，保存获取的文件信息
        返回值：
            成功：返回0
            失败：返回-1,设置errno
        如果想知道文件是否是某些权限，应该与该权限对应的宏做与操作，如果结果仍然是宏，则有该权限
        而判断文件类型，需要先和掩码进行按位与，在与文件类型宏判断相等与否
        如果用stat获取软连接的信息，则会获取到连接到的文件信息，而如果想要获取该软连接的信息，
        则需要使用lstat
    int fstat(int fd, struct stat *statbuf);
    int lstat(const char *pathname, struct stat *statbuf);
*/

#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdio.h>

int main(){
    struct stat statbuf;
    int ret = stat("a.txt",&statbuf);
    if(ret==-1){
        perror("stat error");
        return -1;
    }
    printf("size: %ld\n",statbuf.st_size);
    return 0;
}