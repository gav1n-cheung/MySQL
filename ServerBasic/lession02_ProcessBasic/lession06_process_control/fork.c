/*
    #include <sys/types.h>
    #include <unistd.h>

    pid_t fork(void);
        作用：用于创建子进程
        返回值：
            fork()的返回值会返回两次。一次在父进程中，一次在子进程中。
            在父进程中返回创建的子进程的ID,
            在子进程中返回0
            如何区分父进程和子进程，通过fork的返回值
            在父进程中返回-1，表示创建子进程失败，并且设置errno
        失败的两个原因：
            1.当前系统的进程数已经达到了系统规定的上限，这时errno的值被设置为EAGAIN
            2.系统内存不足，这时errno的值被设置为ENOMEM  
*/
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(){
    int num = 10;
    printf("process run!%d\n",getpid());
    printf("hello!\n");
    //创建子进程
    pid_t pid = fork();
    //判断是父进程还是子进程
    if(pid>0){
        printf("i am parent process , pid:%d,ppid:%d\n",getpid(),getppid());
        
    }else if(pid==0){
        sleep(1);
        printf("i am child process,pid:%d,ppid:%d\n",getpid(),getppid());
    }
    for(int i=0;i<5;i++){
        printf("i:%d,pid:%d\n",i,getpid());
    }
    return 0;
}