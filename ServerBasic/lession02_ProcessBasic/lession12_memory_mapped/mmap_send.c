#include<stdio.h>
#include<sys/mman.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<wait.h>
#include<stdlib.h>

int main(){
    int fd = open("mmap.txt",O_RDWR);
    if(fd==-1){
        perror("open");
        exit(0);
    }
    int size = lseek(fd,0,SEEK_END);
    void* ptr = mmap(NULL,size,PROT_WRITE|PROT_READ,MAP_SHARED,fd,0);
    while(1){
        stpcpy((char*) ptr,"helloworld");
        printf("send success!\n");
        sleep(1);
    }
    close(fd);
    return 0;
}