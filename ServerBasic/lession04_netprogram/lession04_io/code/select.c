#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/types.h>

int main()
{

    //创建监听socket
    int l_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (l_fd == -1)
    {
        perror("socket");
        exit(-1);
    }
    // bind
    struct sockaddr_in sevaddr;
    sevaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sevaddr.sin_family = AF_INET;
    sevaddr.sin_port = htons(9999);
    int ret = bind(l_fd, (struct sockaddr *)&sevaddr, sizeof(sevaddr));
    if (ret == -1)
    {
        perror("bind");
        exit(-1);
    }
    // listen
    ret = listen(l_fd, 5);
    if (ret == -1)
    {
        perror("listen");
        exit(-1);
    }
    //创建一个fd_set的集合，存放的是要检测的文件描述符
    fd_set rdset,temp;         //本质上是一个1024位的缓冲区
    FD_ZERO(&rdset);      //初始化
    FD_SET(l_fd, &rdset); //设置监听
    int maxfd = l_fd;
    //开启传输
    while (1)
    {
        temp=rdset;
        //调用select系统函数，让内核帮忙检测哪些文件描述符有数据
        ret = select(maxfd + 1, &temp, NULL, NULL, NULL);
        if (ret == -1)
        {
            perror("select");
            exit(-1);
        }
        else if (ret == 0)
        {
            //设置永久阻塞，如果是没有检测到变化就不会推出阻塞，不会产生返回值==0的情况
            continue;
        }
        else if (ret > 0)
        {
            //说明检测到了有文件描述符对应的缓冲区数据发生了改变
            if (FD_ISSET(l_fd, &temp))
            {
                //表示有新的客户端链接进来了
                struct sockaddr_in cliaddr;
                int len = sizeof(cliaddr);
                int c_fd = accept(l_fd, (struct sockaddr *)&cliaddr, &len);
                //将新的文件描述符加入到集合中
                FD_SET(c_fd, &rdset);
                //更新最大的文件描述符
                maxfd = maxfd > c_fd ? maxfd : c_fd;
            }
            for (int i = l_fd + 1; i < maxfd + 1; i++)
            {
                if (FD_ISSET(i, &temp))
                {
                    //说明这个文件描述符对应的客户端发送了数据
                    char buf[1024] = {0};
                    int read_ret = read(i, buf, sizeof(buf));
                    if (read_ret == -1)
                    {
                        perror("read");
                        exit(-1);
                    }
                    else if (read_ret == 0)
                    {
                        printf("client closed\n");
                        close(i);
                        FD_CLR(i, &rdset);
                        continue;
                    }
                    else if (read_ret > 0)
                    {
                        printf("receive data:%s\n", buf);
                        write(i, buf, strlen(buf) + 1);
                    }
                }
            }
        }
    }
    close(l_fd);
    return 0;
}