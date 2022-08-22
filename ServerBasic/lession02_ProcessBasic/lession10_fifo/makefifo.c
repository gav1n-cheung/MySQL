/*
    创建fifo文件
    1.通过命令:mkfifo 名字
    2.通过系统调用:int mkfifo(const char *pathname, mode_t mode);
    #include <sys/types.h>
    #include <sys/stat.h>
    int mkfifo(const char *pathname, mode_t mode);
        参数：
            -pathname: 管道名称的路径
            -mode:文件的权限,和open的mode是一样的
        返回值：
            成功返回0，失败返回-1
*/
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
    //判断文件是否存在
    int ret = access("fifo1",F_OK);
    if(ret==-1){
        printf("fifo not exist, will create the file\n");
        ret = mkfifo("fifo1",0664);
        if(ret==-1){
            perror("mkfifo");
            exit(0);
        }
    }
    return 0;
}