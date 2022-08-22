/*
    #include <sys/types.h>
    #include <signal.h>
    int kill(pid_t pid,int sig);
        -功能：给某个进程或者进程组Pid,发送任何的信号sig
        -参数：
            -pid:需要发送给的进程id
                >0:将信号发送给指定的进程
                =0:将信号发送给当前的进程组
                =-1:将信号发送给每一个有权限权限接受这个信号的进程
                <-1:这个pid=某个进程组的id取反(-12345)
            -sig:需要发送的信号的编号或者宏值，表示不发送信号
        kill(getppid(),9);  -kill 父进程
        kill(getpid(),9);   -kill 本进程
    int raise(int sig);
        -功能：给当前进程发送信号
        -参数：
            -sig:要发送的信号
        -返回值：
            -成功 0
            -失败 非0
    void abort(void);
        -功能：发送SIGABRT信号给当前的进程,杀死当前的进程
*/

#include<sys/types.h>
#include<signal.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/wait.h>

int main(){
    pid_t pid = fork();
    if(pid==0){
        for(int i=0;i<5;i++){
            printf("child process\n");
            sleep(1);
        }
    }else if(pid>0){
        printf("parent process\n");
        sleep(3);
        printf("kill child process\n");
        kill(pid,SIGABRT);
        wait(NULL);
    }else{
        perror("fork");
        return -1;
    }
    return 0;
}