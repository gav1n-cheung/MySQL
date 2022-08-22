#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

void recyleChild(int arg){
    while(1){
        int ret = waitpid(-1,NULL,WNOHANG);
        if(ret==-1){
            //所有子进程都回收完毕了
            break;
        }else if(ret==0){
            //还有子进程活着
            break;
        }else if(ret>0){
            printf("子进程%d被回收了\n",ret);
        }
    }
}

int main()
{
    struct sigaction act;
    act.sa_flags=0;
    sigemptyset(&act.sa_mask);
    act.sa_handler = recyleChild;
    //注册信号捕捉以回收子进程的资源
    sigaction(SIGCHLD,&act,NULL);


    //创建socket
    int l_fd = socket(AF_INET, SOCK_STREAM, 0);
    //绑定地址和端口
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
    ret = listen(l_fd, 128);
    if (ret == -1)
    {
        perror("listen");
        exit(-1);
    }
    //接受客户端连接
    while (1)
    {
        struct sockaddr_in cliaddr;
        int len = sizeof(cliaddr);
        //由于子进程结束产生了信号捕捉去执行回调函数，导致了软中断，当软中断执行完毕，回到accept时，accept会不再阻塞，当然这个非阻塞的返回值会是错误的，因为这不是因为客户端连接导致的非阻塞，
        //此时会产生错误号EINTR，因为当产生软中断导致的accpet非阻塞而得到报错，那我们要跳过这个错误重新执行循环。
        int c_fd = accept(l_fd, (struct sockaddr *)&cliaddr, &len);
        if (c_fd == -1)
        {
            if(errno==EINTR){
                continue;
            }
            perror("accpet");
            exit(-1);
        }
        //每一个连接进来，就创建一个子进程跟客户端通信
        int pid = fork();
        if (pid == 0)
        {
            //子进程
            //获取客户端信息
            char cliIp[16];
            inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, cliIp, sizeof(cliIp));
            unsigned short port = ntohs(cliaddr.sin_port);
            printf("client connect,ip:%s,port:%d\n", cliIp, port);
            //接收客户端发来的数据
            char recv[1024] = {0};
            while (1)
            {
                //读数据
                int read_ret = read(c_fd, recv, sizeof(recv));
                if (read_ret > 0)
                {
                    printf("recive client message:%s\n", recv);
                }
                else if (read_ret == 0)
                {
                    printf("client closed\n");
                    break;
                }
                else if (read_ret == -1)
                {
                    perror("read");
                    exit(-1);
                }
                //写数据
                int write_ret = write(c_fd,recv,strlen(recv)+1);
                if(write_ret==-1){
                    perror("write");
                    exit(-1);
                }
            }
            close(c_fd);
            exit(0);
        }
    }
    close(l_fd);
    return 0;
}