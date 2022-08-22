/*
    匿名映射：不需要文件实体，进行内存映射
*/
#include<stdio.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
    int length = 4096;
    void* ptr = mmap(NULL,length,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);
    if(ptr==MAP_FAILED){
        perror("mmap");
        exit(0);
    }
    //父子进程间的通信
    pid_t pid = fork();
    if(pid>0){
        strcpy((char*) ptr,"hello");
        wait(NULL);
    }else if(pid==0){
        //内存映射是非阻塞的，因此sleep子进程1s，再获取数据
        sleep(1);
        char buf[1024]={0};
        strcpy(buf,(char*)ptr);
        printf("%s\n",buf);
    }else{
        perror("fork");
        exit(0);
    }
    int ret = munmap(ptr,length);
    if(ret == -1){
        perror("munmap");
        exit(0);
    }
    return 0;
}