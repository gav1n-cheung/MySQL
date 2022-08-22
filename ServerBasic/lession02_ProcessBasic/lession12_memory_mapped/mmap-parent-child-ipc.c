/*
#include <sys/mman.h>
    void *mmap(void *addr, size_t length, int prot, int flags,int fd, off_t offset);
         功能：将一个文件或者设备的数据映射到内存中
         参数：
            void *addr:NULL,由内核指定
            length：要映射的数据的长度，这个值不能为零，建议使用文件的长度
                    （获取文件的长度）：stat lseek
            prot：对申请的内存映射区的操作权限
                    PROT_EXEC  可执行权限
                    PROT_READ  读权限
                    PROT_WRITE 写权限
                    PROT_NONE  无权限
                    要操作映射内存，必须要有读的权限 PROT_READ、PROT_READ|PROT_WRITE
            flags：
                    MAP_SHARED：映射区的数据会自动和磁盘文件进行同步，进程间通信也必须设置这个选项
                    MAP_PRIVATE：不同步，映射区的文件改变了，对原来的文件不修改，会创建一个新的文件（copy on write）
            fd:需要映射的那个文件的文件描述符
                通过open得到，open的是一个磁盘文件
                -注意：文件的大小不能为0，open指定的权限不能和prot参数有冲突
                        prot：PROT_READ                 open:只读/读写
                        prot：PROT_READ|PROT_WRITE      open：读写
            offset: 偏移量,一般不用，必须指定的是4K的整数倍，0表示不偏移

        返回值：
                成功返回创建的内存的首地址，失败返回MAP_FAILED,(void*)-1

     int munmap(void *addr, size_t length);
        功能：释放内存映射
        参数：
                -addr：要释放的内存的首地址
                -length:要释放的内存的大小，要和mmap中的函数的length一致
*/

/*
使用内存映射实现进程间通信
1.有关系的进程(父子进程)
        -还没有子进程的时候
                -通过唯一的父进程，先创建内存映射区
        -有了内存映射区以后，创建子进程
        -父子进程共享创建的内存映射区
2.没有关系的进程间的通信
        -准备一个大小不是0的磁盘文件
        -进程1 通过磁盘文件创建内存映射区
                -得到操作这块内存的指针
        -进程2 通过磁盘文件创建内存映射区
                -得到操作这块内存的指针
        -使用内存映射区通信
注意：内存映射区通信，是非阻塞的
*/
#include<stdio.h>
#include<sys/mman.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<wait.h>
#include<stdlib.h>

int main(){
    //打开一个文件获取其大小
    int fd = open("test.txt",O_RDWR);
    int size = lseek(fd,0,SEEK_END);
    //创建内存映射
    void* ptr = mmap(NULL,size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if(ptr==MAP_FAILED){
        perror("mmap");
        exit(0);
    }
    //创建子进程
    pid_t pid = fork();
    if(pid>0){
        wait(NULL);
        char buf[1024];
        stpcpy(buf,(char*) ptr);
        printf("%s",buf);
    }else if(pid==0){
        strcpy((char*) ptr,"hello\n");
    }else{
        perror("fork");
    }
    munmap(ptr,size);
    return 0;
}

