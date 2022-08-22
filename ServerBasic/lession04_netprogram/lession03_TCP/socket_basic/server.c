//TCP服务器端
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

int main(){
    //1.创建socket套接字(用于监听的)
    int l_fd = socket(AF_INET,SOCK_STREAM,0);
    if(l_fd==-1){
        perror("socket");
        exit(-1);
    }
    //2.绑定当前的IP和端口
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    // inet_pton(AF_INET,"127.0.0.1",saddr.sin_addr.s_addr);
    saddr.sin_addr.s_addr = 0;//0.0.0.0 表示任意地址
    // saddr.sin_addr.s_addr = INADDR_ANY;//0.0.0.0 表示任意地址,INADDR_ANY为其宏表示
    saddr.sin_port  = htons(9999);
    int ret = bind(l_fd,(struct sockaddr*)&saddr,sizeof(saddr));
    if(ret==-1){
        perror("bind");
        exit(-1);
    }
    //3.监听
    ret = listen(l_fd,8);
    if(ret==-1){
        perror("bind");
        exit(-1);
    }
    //4. 接收客户端连接
    struct sockaddr_in clientaddr;
    socklen_t len = sizeof(clientaddr);
    int cfd = accept(l_fd,(struct sockaddr*)&clientaddr,&len);
    if(cfd==-1){
        perror("accept");
        exit(-1);
    }
    //输出客户端的信息
    char clientIP[16];
    inet_ntop(AF_INET,&clientaddr.sin_addr.s_addr,clientIP,sizeof(clientIP));
    unsigned short clientPort = ntohs(clientaddr.sin_port);
    printf("client ip :%s,port:%d\n",clientIP,clientPort);
    //5. 进行通信
    //获取客户端数据
    char recvBuf[1024]= {0};
    while(1){
        int c_len = read(cfd,recvBuf,sizeof(recvBuf));
        if(c_len==-1){
        perror("read");
        exit(-1);
        }else if(c_len>0){
            printf("recv client data:%s\n",recvBuf);
        }else if(c_len==0){
            //表示客户端断开连接
            printf("client closed...\n");
            break;
        }
        //向客户端发送数据
        ret = write(cfd,recvBuf,sizeof(recvBuf));
        if(ret==-1){
            perror("write");
            exit(-1);
        }
    }
    //关闭文件描述符
    close(l_fd);
    close(cfd);
    return 0;
}