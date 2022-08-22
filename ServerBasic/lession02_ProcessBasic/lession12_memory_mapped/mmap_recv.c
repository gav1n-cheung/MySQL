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
    int size = lseek(fd,0,SEEK_END);
    void* ptr = mmap(NULL,size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    char buf[1024]={0};
    // while(1){
        stpcpy(buf,(char*) ptr);
        printf(buf);
    // }
    close(fd);
    return 0;
}