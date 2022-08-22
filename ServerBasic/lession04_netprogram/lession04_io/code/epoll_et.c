#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>

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
    //调用epoll_create()创建一个epoll实例
    int epfd = epoll_create(100);
    //将监听的文件描述符相关的检测信息添加到epoll实例中
    struct epoll_event epev;
    epev.events = EPOLLIN;
    epev.data.fd = l_fd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, l_fd, &epev);
    struct epoll_event epevs[1024];
    while (1)
    {
        ret = epoll_wait(epfd, epevs, 1024, -1);
        if (ret == -1)
        {
            perror("epoll");
            exit(-1);
        }
        printf("ret = %d\n", ret);
        for (int i = 0; i < ret; i++)
        {
            int curfd = epevs[i].data.fd;
            if (curfd == l_fd)
            {
                //监听的文件描述符有数据到达，有客户端连接
                struct sockaddr_in cliaddr;
                int len = sizeof(cliaddr);
                int c_fd = accept(l_fd, (struct sockaddr *)&cliaddr, &len);
                //设置c_fd非阻塞
                int flag = fcntl(c_fd, F_GETFL);
                flag = flag | O_NONBLOCK;
                fcntl(c_fd, F_SETFL, flag);
                epev.events = EPOLLIN | EPOLLET;
                epev.data.fd = c_fd;
                epoll_ctl(epfd, EPOLL_CTL_ADD, c_fd, &epev);
            }
            else
            {
                if (epevs[i].events & EPOLLOUT)
                    continue;
                //循环读取所有数据
                char buf[5] = {0};
                int len = 0;
                while ((len = read(curfd, buf, sizeof(buf))) > 0)
                {
                    //打印数据
                    // printf("recv data:%s\n", buf);
                    write(STDOUT_FILENO,buf,len);
                    write(curfd, buf, len);
                }
                if (len == 0)
                {
                    printf("客户端断开了连接..\n");
                }
                else if (len == -1)
                {
                    if (errno==EAGAIN) printf("data over...\n");
                    else{
                        perror("read");
                        exit(-1);
                    }
                }
            }
        }
    }
    close(l_fd);
    close(epfd);
    return 0;
}