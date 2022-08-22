/*
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>

    //打开一个已经存在的文件
    int open(const char *pathname, int flags);
    //open 函数定义在<fcntl.h>中，但是其参数flags定义了很多宏，包含在另外两个头文件中
        参数：
            - pathname:要打开的文件路径
            - flags:对文件的操作权限设置还有其他的设置
                O_RDONLY 只读, O_WRONLY 只写, or  O_RDWR 可读写 这三个设置是互斥的，只能有一个权限
        返回值：返回一个新的文件描述符，如果调用失败，返回-1

        errno:属于Linux系统函数库，库里面的一个全局变量，记录的是最近的错误号

    #include <stdio.h>
    void perror(const char *s);作用：打印errno对应的错误描述
        s参数：用户描述，比如hello,最终输出的内容是 hello:xxx(实际的错误)

    int open(const char *pathname, int flags, mode_t mode);//这里并非重载而是可变参数
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(){
    //打开一个文件
    int fd =open("a.txt",O_RDONLY);
    if(fd == -1) {
        perror("open");
    }
    //读写操作
    close(fd);
    /*❯ gcc open.c -o open
      ❯ ./open
      open: No such file or directory
      ❯ touch a.txt
      ❯ ./open
    */
    return 0;
}