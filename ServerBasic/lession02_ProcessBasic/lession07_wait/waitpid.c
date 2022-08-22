/*
    #include <sys/types.h>
    #include <sys/wait.h>
    pid_t waitpid(pid_t pid, int *wstatus, int options);
        功能：回收指定进程号的子进程，可以设置是否阻塞
        参数：
            pid:
                pid>0: 某个子进程的pid
                pid=0: 回收当前进程组的所有子进程(一个进程组的Id默认是父进程的pid)
                pid=-1: 回收所有的子进程,相当于wait()
                pid<-1: 回收某个进程组的组id的绝对值
            options:设置阻塞和非阻塞
                0: 阻塞
                WNOHANG: 非阻塞
            返回值
                >0 返回子进程的id
                =0 options=WNOHANG 表示还有子进程或者
                =-1: 错误，或者没有子进程了          
*/
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    //有一个父进程，创建5个子进程(兄弟)
    pid_t pid;
    for(int i=0;i<5;i++){
        pid = fork();
        if(pid==0) break;//在这里,因为子进程第一步就会执行这里，(fork后的代码)，则就可以这是子进程了
    }
    if(pid>0){
        while(1){
            sleep(1);
            printf("parent,pid:%d\n",getpid());
            // int ret = wait(NULL);
            int st;
            int ret = waitpid(-1,&st,WNOHANG);
            if(ret==-1) break;
            if(ret==0){
                //说明还有子进程存在
                continue;
            }else if(ret>0){
                if(WIFEXITED(st)){
                    //是不是正常退出
                    printf("推出的状态码:%d\n",WEXITSTATUS(st));
                }
                if(WIFSIGNALED(st)){
                    //是不是异常终止
                    printf("被哪个信号干掉了:%d\n",WTERMSIG(st));
                }
                printf("child die,pid ==%d\n",ret);
            } 
        }
    }else if(pid==0){
        while(1){
            printf("child,pid:%d\n",getpid());
            sleep(1);
        }
            exit(1);
    }
    return 0;
}