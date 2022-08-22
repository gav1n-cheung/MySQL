#include<signal.h>
#include<stdio.h>

int main(){
    //创建一个信号集
    sigset_t set;
    //清空信号集的内容
    int ret = sigemptyset(&set);
    //判断SIGINT是否在信号集set中
    ret = sigismember(&set,SIGINT);
    if(ret==0) printf("SIGINT 不阻塞\n");
    else if(ret == 1) printf("SIGINT阻塞\n");
    sigaddset(&set,SIGINT);
    sigaddset(&set,SIGQUIT);
    ret = sigismember(&set,SIGINT);
    if(ret==0) printf("SIGINT 不阻塞\n");
    else if(ret == 1) printf("SIGINT阻塞\n");
    sigdelset(&set,SIGQUIT);
    ret = sigismember(&set,SIGQUIT);
    if(ret==0) printf("SIGQUIT 不阻塞\n");
    else if(ret == 1) printf("SIGQUIT阻塞\n");
    return 0;
}