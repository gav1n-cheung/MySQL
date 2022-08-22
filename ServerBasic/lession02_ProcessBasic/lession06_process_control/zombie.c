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
        while(1){
            printf("i am parent process , pid:%d,ppid:%d\n",getpid(),getppid());
            sleep(1);
        }
    }else if(pid==0){
        sleep(1);
        printf("i am child process,pid:%d,ppid:%d\n",getpid(),getppid());
    }
    for(int i=0;i<5;i++){
        printf("i:%d,pid:%d\n",i,getpid());
    }
    return 0;
}