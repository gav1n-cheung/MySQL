#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>

/*
    设置管道非阻塞
    int flags = fcntl(fd[0],F_GETFL);//获取原来的flag
    flags |= O_NONBLOCK;//修改flag的值
    fcntl(fd[0],F_SETFL,flags);//设置新的flag
*/
int main(){
    //在fork之前创建管道
    int pipefd[2];
    int ret = pipe(pipefd);
    if(ret==-1){
        perror("pipe");
        exit(0);
    }
    //创建子进程
    pid_t pid = fork();
    if(pid>0){
        //父进程

        //关闭写端
        close(pipefd[1]);

        char buf[1024] ={0};
        int flags = fcntl(pipefd[0],F_GETFL);//获取原来的flag
        flags |= O_NONBLOCK;//修改flag的值
        fcntl(pipefd[0],F_SETFL,flags);//设置新的flag
        while(1){
            int len = read(pipefd[0],buf,sizeof(buf)); 
            printf("parent receive:%s,pid:%d,len:%d\n",buf,getpid(),len);
            memset(buf,0,1024);
            sleep(1);
        }
    }else if(pid==0){
        //子进程
        //从管道的读取端读取数据
        printf("child process,pid:%d\n",getpid());
        //关闭读端
        close(pipefd[0]);
        char rec[1024]={0};
        while(1){
            //向管道中写数据
            char* buf= "hello i am child";
            int len = write(pipefd[1],buf,strlen(buf));
            sleep(10);
        }
    }

    return 0;
}
