/*
    标准C库
        #include <stdio.h>

        int fseek(FILE *stream, long offset, int whence);
    
    Linux 系统函数
        #include <sys/types.h>
        #include <unistd.h>

        off_t lseek(int fd, off_t offset, int whence);
            参数:
                - fd: 文件描述符，通过open得到，通过fd操作某个文件
                - offset: 偏移量
                - whence:
                    SEEK_SET 设置文件指针的偏移量
                    SEEK_CUR 设置偏移量，从当前位置+第二个参数offset的值
                    SEEK_END 设置偏移量，文件大小+第二个参数offset的值       
            返回值:返回文件指针的位置
            作用：
                1.移动文件指针到头文件 lseek(fd,0,SEEK_SET);
                2.获取当前文件指针的位置 lseek(fd,0,SEEK_CUR);
                3.获取文件的长度 lseek(fd,0,SEKK_END);
                4.拓展文件的长度，当前文件10b，110b，增加了100个字节
                    lseek(fd,100,SEEK_END);
                    需要写一次空数据才能生效
*/
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdio.h>

int main(){
    int srctxt = open("hello.txt",O_RDWR);
    if(srctxt==-1){
        perror("open");
        return -1;
    }
    int length = lseek(srctxt,100,SEEK_END);
    if(length==-1){
        perror("lseek");
        return -1;
    }
    write(srctxt," ",1);
    close(srctxt);
    return 0;
}