/*
    #include <stdlib.h>
        void exit(int status);
    #include <unistd.h>
        void _exit(int status);
    status参数：进程退出时的一个状态信息，父进程回收子线程资源的时候可以获取到；
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(){
    printf("hello\n");
    printf("world\n");
    // pid_t pid = fork();
    //exit(0);
    _exit(0);
    return 0;
}