/*
    #include <unistd.h>

    int pipe(int pipefd[2]);
        功能：创建一个匿名管道，实现进程间的通信
        参数：int pipefd[2]这个数组是一个传出参数
                pipfd[0]对应的是管道的读端
                pipfd[1]对应的是管道的写端
        返回值：
                0成功；-1失败
    管道默认是阻塞的，如果管道中没有数据，read阻塞，如果管道满了,write阻塞
    注意：匿名管道只能用于具有关系的进程之间的通信
*/
#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>

//子进程发送数据给父进程，父进程读取到数据输出
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
        while(1){
            int len = read(pipefd[0],buf,sizeof(buf)); 
            if(len==0) {
                printf("no write end!\n");
                exit(0);
            }
            printf("parent receive:%s,pid:%d,len:%d\n",buf,getpid(),len);

            // char* rec= "hello i am parent ";
            // int ret = write(pipefd[1],rec,strlen(rec));
            // sleep(1);
        }
    }else if(pid==0){
        // sleep(10);//如果加上这句，则父进程的输出在read执行完毕后。因为read默认是阻塞的
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
            // sleep(100);
            close(pipefd[1]);

            // int ret = read(pipefd[0],rec,sizeof(rec)); 
            // printf("child receive:%s,pid:%d\n",rec,getpid());
            // bzero(buf,1024);
        }
    }

    return 0;
}
