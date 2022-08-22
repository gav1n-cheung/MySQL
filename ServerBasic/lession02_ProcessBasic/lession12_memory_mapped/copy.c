//使用内存映射实现文件拷贝的功能
/*
    思路：
        1.对原始文件进行内存映射
        2.创建一个新文件(拓展该文件)
        3.把文件映射到内存中
        4.通过内存拷贝将第一个文件的内存数据拷贝到新的文件内容中
        5.释放资源
*/
#include<stdio.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

int main(){
    //1.读取源文件
    int fd_write = open("english.txt",O_RDWR);
    if(fd_write==-1){
        perror("fd_write");
        exit(0);
    }

    //2.创建一个新文件(并拓展)
    int fd_read = open("copy.txt",O_RDWR|O_CREAT,0664);
    if(fd_read==-1){
        perror("fd_read");
        exit(0);
    }
    //2.1拓展新文件
    //2.1.1 获取源文件大小
    int size = lseek(fd_write,0,SEEK_END);
    //2.1.2 拓展新文件到源文件大小
    truncate("copy.txt",size);
    //2.1.3 写入任意内容使拓展生效
    write(fd_read," ",1);

    //3.分别做内存映射
    void* ptr_write = mmap(NULL,size,PROT_READ|PROT_WRITE,MAP_SHARED,fd_write,0);
    void* ptr_read = mmap(NULL,size,PROT_READ|PROT_WRITE,MAP_SHARED,fd_read,0);
    if(ptr_write==MAP_FAILED){
        perror("mmap1");
        exit(0);
    }
    if(ptr_read==MAP_FAILED){
        perror("mmap2");
        exit(0);
    }


    //4.使用内存拷贝
    memcpy(ptr_read,ptr_write,size);
    //5.释放资源,后打开先释放,先打开后释放
    munmap(ptr_read,size);
    munlock(ptr_write,size);
    close(fd_read);
    close(fd_write);
    return 0;
}
