#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

struct sockInfo
{
    int fd;
    struct sockaddr_in addr;
    pthread_t tid;
};

struct sockInfo sockinfos[128];

void *childThread(void *arg)
{
    //子线程和客户端进行通信 cfd 客户端信息 cliaddr 线程号 tid
    //获取客户端信息
    struct sockInfo* info = (struct sockInfo*) arg;
    char cliIp[16] = {0};
    inet_ntop(AF_INET, &info->addr.sin_addr.s_addr, cliIp, sizeof(cliIp));
    unsigned short port = ntohs(info->addr.sin_port);
    printf("client connet!IP:%s,port:%d", cliIp, port);
    //通信
    char recvbuf[1024] = {0};
    while (1)
    {
        //读数据
        int len = read(info->fd, recvbuf, sizeof(recvbuf));
        if (len > 0)
        {
            printf("receive client data:%s\n", recvbuf);
        }
        else if (len == -1)
        {
            printf("read");
            exit(-1);
        }
        else
        {
            printf("client closed\n");
            break;
        }
        //写数据
        write(info->fd, recvbuf, strlen(recvbuf) + 1);
    }
    close(info->fd);
    return NULL;
}

int main()
{
    //创建套接字
    int l_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (l_fd == -1)
    {
        perror("socket");
        exit(-1);
    }
    //绑定套接字
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(9999);
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int ret = bind(l_fd, (struct sockaddr *)&saddr, sizeof(saddr));
    if (ret == -1)
    {
        perror("bind");
        exit(-1);
    }
    //开启监听
    ret = listen(l_fd, 5);
    if (ret == -1)
    {
        perror("listen");
        exit(-1);
    }
    //初始化数据
    int max = sizeof(sockinfos) / sizeof(sockinfos[0]);
    for (int i = 0; i < max; i++)
    {
        bzero(&sockinfos[i], sizeof(sockinfos[i]));
        sockinfos[i].fd = -1;
        sockinfos[i].tid = -1;
    }
    //接收客户端连接
    while (1)
    {
        struct sockaddr_in cliaddr;
        int len = sizeof(cliaddr);
        int c_fd = accept(l_fd, (struct sockaddr *)&cliaddr, &len);
        if (c_fd == -1)
        {
            perror("accpet");
            exit(-1);
        }
        struct sockInfo *pinfo;
        for (int i = 0; i < max; i++)
        {
            //从这个数组中找到一个可用的sockInfo元素
            if (sockinfos[i].tid == -1)
            {
                pinfo = &sockinfos[i];
                break;
            }
            if (i == max - 1)
            {
                sleep(1);
                i--;
            }
        }
        // pinfo->addr.sin_addr.s_addr = cliaddr.sin_addr.s_addr;//结构体不能直接赋值，要每个成员都单独赋值
        pinfo->fd = c_fd;
        memcpy(&pinfo->addr, &cliaddr, sizeof(cliaddr));
        //开启子线程
        pthread_create(&pinfo->tid, NULL, childThread, pinfo);
        //回收子线程资源，使用非阻塞的detach来分离线程，而非阻塞的join
        pthread_detach(pinfo->tid);
    }
    close(l_fd);
    return 0;
}