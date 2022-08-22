/*
    #include <unistd.h>
    #include <fcntl.h>

    int fcntl(int fd, int cmd, ...  arg );
    参数：
        fd: 表示需要操作的文件描述符
        cmd: 表示对文件描述符如何进行操作
            1.复制文件描述符
                - F_DUPFD:复制文件描述符，复制的是第一个参数fd
                    int ret = fcntl(fd,F_DUPFD);返回的就是复制的新的文件描述符

                - F_GETFL:获取指定的文件描述符文件状态flag
                    获取的flag和我们通过open函数传递的flag是一个东西，可以有只读、只写和可读写
                
                - F_SETFL:设置文件描述符文件状态flag
                    必选项：O_RDONLY, O_WRONLY, O_RDWR不可以被修改
                    可选项： O_APPEND,O_NONBLOCK
                        O_APPEND 表示追加数据
                        O_NONBLOCK 设置为非阻塞
        阻塞和非阻塞：描述的是函数调用的行为。如果是阻塞，则函数得到返回值前都不会结束
*/

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int main(){
    //1.复制文件描述符
    int fd = open("a.txt",O_RDWR);
    if(fd==-1){
        perror("open");
        return 0;
    }
    // int fd1 =fcntl(fd,F_DUPFD);
    // printf("fd:%d,fd1:%d\n",fd,fd1);//不是创建当前可使用的最小的文件描述符
    // close(fd);
    //2.修改文件描述符状态的flag,给flag加入O_APPEND标记从而添加新的信息到文件中
    int flag = fcntl(fd,F_GETFL);
    flag |=O_APPEND;
    int ret = fcntl(fd,F_SETFL,flag);//如果直接将参数设为O_APPEND会将原来的flag覆盖掉，因此需要先获取原来的flag然后与我们添加的flag做按位或
    if(ret==-1){
        perror("fcntl");
        return -1;
    }
    char *str ="hello";
    int write_ret= write(fd,str,strlen(str));
    if(write_ret==-1){
        perror("write");
        return -1;
    }
    close(fd);
    return 0;
}