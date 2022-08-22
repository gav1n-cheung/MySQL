#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/types.h>
#include <poll.h>

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
    int optval = 1;
    setsockopt(l_fd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));

    // listen
    ret = listen(l_fd, 5);
    if (ret == -1)
    {
        perror("listen");
        exit(-1);
    }
    //初始化检测的文件描述符数组
    struct pollfd fds[1024];
    for (int i = 0; i < 1024; i++)
    {
        fds[i].fd = -1;
        fds[i].events=POLLIN;   
    }
    fds[0].fd=l_fd;
    int nfds = 0;
    //开启传输
    while (1)
    {
        //调用poll系统函数，让内核帮忙检测哪些文件描述符有数据
        ret = poll(fds,nfds+1,-1);
        if (ret == -1)
        {
            perror("poll");
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
            if (fds[0].revents & POLLIN)
            {
                //表示有新的客户端链接进来了
                struct sockaddr_in cliaddr;
                int len = sizeof(cliaddr);
                int c_fd = accept(l_fd, (struct sockaddr *)&cliaddr, &len);
                //将新的文件描述符加入到集合中
                for(int i=1;i<1024;i++){
                    if(fds[i].fd==-1){
                        fds[i].fd=c_fd;
                        fds[i].events=POLLIN;
                        break;
                    }
                }
                //更新最大的文件描述符
                nfds = nfds > c_fd ? nfds : c_fd;
            }
            for (int i = 1; i <= nfds; i++)
            {
                if (fds[i].revents&POLLIN)
                {
                    //说明这个文件描述符对应的客户端发送了数据
                    char buf[1024] = {0};
                    int read_ret = read(fds[i].fd, buf, sizeof(buf));
                    if (read_ret == -1)
                    {
                        perror("read");
                        exit(-1);
                    }
                    else if (read_ret == 0)
                    {
                        printf("client closed\n");
                        close(fds[i].fd);
                        fds[i].fd = -1;
                        continue;
                    }
                    else if (read_ret > 0)
                    {
                        printf("receive data:%s\n", buf);
                        write(fds[i].fd, buf, strlen(buf) + 1);
                    }
                }
            }
        }
    }
    close(l_fd);
    return 0;
}