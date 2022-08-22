#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/epoll.h>

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
            if (epevs[i].data.fd == l_fd)
            {
                //监听的文件描述符有数据到达，有客户端连接
                struct sockaddr_in cliaddr;
                int len = sizeof(cliaddr);
                int c_fd = accept(l_fd, (struct sockaddr *)&cliaddr, &len);
                epev.events = EPOLLIN | EPOLLOUT;
                epev.data.fd = c_fd;
                epoll_ctl(epfd, EPOLL_CTL_ADD, c_fd, &epev);
            }
            else
            {
                if(epevs[i].events & EPOLLOUT) continue;
                //有数据到达，需要通信
                char buf[1024] = {0};
                int read_ret = read(curfd, buf, sizeof(buf));
                if (read_ret == -1)
                {
                    perror("read");
                    exit(-1);
                }
                else if (read_ret == 0)
                {
                    printf("client closed\n");
                    close(i);
                    epoll_ctl(epfd,EPOLL_CTL_DEL,curfd,NULL);
                    continue;
                }
                else if (read_ret > 0)
                {
                    printf("receive data:%s\n", buf);
                    write(curfd, buf, strlen(buf) + 1);
                }
            }
        }
    }
    close(l_fd);
    close(epfd);
    return 0;
}