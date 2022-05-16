# 使用腾讯云搭建服务器(MySQL)
## 去腾讯云买一个云服务器
挑个最便宜的先试试
我选用的是CentOs7的系统
## 连接你的服务器
我还是喜欢喜欢终端ssh，不想配其他的工具，则连接==公网ip==即可，默认用户为root，去管理界面修改密码后登录使用
```
ssh root@yourIp
enter your password
input "yes"
```
## 将你的服务器终端切换为zsh
(bash不是狗都不用?)安装zsh并安装oh-my-zsh，傻瓜操作
```
yum install zsh -y
chsh -s /bin/zsh root
echo $SHELL
yum install wget git -y
wget https://github.com/robbyrussell/oh-my-zsh/raw/master/tools/install.sh -O - | zsh

/bin/cp ~/.oh-my-zsh/templates/zshrc.zsh-template ~/.zshrc
source ~/.zshrc
```
切换zsh主题，花里胡哨的例如这种
![zsh theme bullet-train](https://github.com/gav1n-cheung/MySQL/blob/main/Picture/2022-05-03_14-51.png)
正常一点的例如这种
![zsh theme jonathan](https://github.com/gav1n-cheung/MySQL/blob/main/Picture/2022-05-03_14-56.png)
## 安装MySQL
[来自segmentfault的强力小磊哥](https://segmentfault.com/a/1190000022843273)
按照这个来会有点问题，在安装MySQL时会不成功，请参考[这个(打不开就翻墙)](https://forums.cpanel.net/threads/cpanel-whm-update-failure-in-upcp-script-mysql-5-7-community-server-yum-issue.697225/)
按照思否的教程来的话，你的新建账户已经开启了权限，可以远程访问，那下面就要开启远程访问
## 远程访问腾讯云上的MySQL
### 开放3306端口
[来自Laravel社区的truesnow](https://learnku.com/articles/13551/tencent-cloud-server-mysql-remote-connection-settings)
在你自己的主机上安装MySQL后，使用以下命令来远程连接云服务器上的MySQL
```
mysql -h ipaddress -uusrname -ppassword
```
例如下面这样
![MySQL remote](https://github.com/gav1n-cheung/MySQL/blob/main/Picture/2022-05-03_15-12.png)
如果你装过Oracle，你会感叹这个安装真是太简单，太现代化了(想起来oracle的监听程序我就想吐)。
## 使用可视化软件远程管理MySQL
如果是轻量化的操作可以选择[Beekeeper Studio](https://www.beekeeperstudio.io/)
如果是有其他的需求，可以看一下这个推荐[来自卡拉云的蒋川](https://kalacloud.com/blog/best-mysql-gui-tools/)
![Beekeeper Studio](https://github.com/gav1n-cheung/MySQL/blob/main/Picture/2022-05-03_15-17.png)
## 使用编程语言远程连接MySQL
这里指的是Linux下Cmake编译的CPP项目
这里我使用的客户端是Ubuntu 20.04LTS
请先安装MySQL,不推荐自己编译
```
#include <iostream>
#include <mysql/mysql.h> //mysql提供的函数接口头文件

using namespace std;

int main() {
    const char* host = "yourIP"; //主机名
    const char* user = "yourUsrName"; //用户名
    const char* pwd = "yourPassword"; //密码
    const char* dbName = "yourDBName"; //数据库名称
    int port = 3306; //端口号

    // 创建mysql对象
    MYSQL *sql = nullptr;
    sql = mysql_init(sql);
    if (!sql) {
        cout << "MySql init error!" << endl;
    }

    // 连接mysql
    sql = mysql_real_connect(sql, host, user, pwd, dbName, port, nullptr, 0);
    if (sql) {
        cout << "MySql Connect success!" << endl;
    }
    string command = "select * from runoob_tbl";
    int res = mysql_query(sql,command.c_str());
    cout<<res<<endl;
    // 关闭mysql
    mysql_close(sql);
    return 0;
}
```
CMakeLists.txt如下：
```
cmake_minimum_required(VERSION 3.20)
project(TestConnect)

set(CMAKE_CXX_STANDARD 14)

add_executable(TestConnect main.cpp)
target_link_libraries(${PROJECT_NAME} libmysqlclient.so)
```

# 使用VSCode进行远程开发
## 安装VSCode
这没啥好说的
## 安装Remote Develop插件  
![安装插件](https://github.com/gav1n-cheung/MySQL/blob/main/Picture/2022-05-16_09-15.png)  
进行测试
```
F1
搜索 remote-ssh->Add new ssh host
输入 ssh命令:usr@xx.xx.xx.xx
提示输入密码
输入密码完成连接，在左侧选择远程文件夹进行开发
如果提示远程计算机也需要安装插件，则按照提示安装即可，如果安装较慢(这取决于你本机的网络)，
可以在网页上下载离线包，拖到远程计算机内离线安装
```
## 使用公私钥配对进行远程连接
```
本机生成密钥后将.pub内容复制到远程计算机下~/.ssh/authorized_keys中即可，没有这个文件就新建一个
本机F1
搜索remote-ssh->open ssh con..
选择第一个配置文件即可
修改其内容为

Host (连接名称)
    HostName (ssh_ip地址)
    User (ssh用户名)
    Port 22(ssh连接端口，默认为22，如果你用其他端口实现别的操作，例如穿透，修改为你使用的端口)
    IdentityFile "~/.ssh/id_rsa"(你创建的私钥的位置，默认就是这个)
```
这样配完了之后，在这里找到你的远程连接,右键选择连接方式即可  
![配置完成的连接](https://github.com/gav1n-cheung/MySQL/blob/main/Picture/2022-05-16_09-28.png)
# 使用socket进行数据传输
这里使用的是C风格的代码
## 本地测试
### server端
```
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(){

    //创建套接字
    int serv_socket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    /*AF_INET      -- 使用IPV4地址
      SOCK_STREAM  -- 使用面向连接的数据传输方式
      IPPROTO_TCP  -- 使用TCP协议
    */

    //bind
    struct sockaddr_in serv_address;                          //创建服务端对象
    memset(&serv_address,0,sizeof(serv_address));             //初始化
    serv_address.sin_family = AF_INET;                        //设定使用IPV4地址
    serv_address.sin_addr.s_addr = inet_addr("127.0.0.1");    //设定地址
    serv_address.sin_port = htons(1234);                      //设定端口
    //将serv_socket与设定的IP地址和端口绑定，IP地址和端口都保存在sockaddr_in结构体中
    bind(serv_socket,(struct sockaddr*)&serv_address,sizeof(serv_address)); 


    //进入被动监听(socket处于休眠状态，收到客户端请求才会被唤醒)，等待客户端请求
    listen(serv_socket,20);


    //接受客户端请求
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    //接收客户端的请求，程序一旦执行到accpet就被阻塞，直至客户端发起请求
    int clnt_sock = accept(serv_socket,(struct sockaddr*)&clnt_addr,&clnt_addr_size);

    //向客户端发送数据
    char str[] = "Hello World!";
    write(clnt_sock,str,sizeof(str));
    
    //关闭套接字
    close(serv_socket);
    close(clnt_sock);
    return 0;
}
```
### client端
```
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main(){
    int sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(1234);
    connect(sock,(sockaddr*)&serv_addr,sizeof(serv_addr));

    char buffer[40];
    read(sock,buffer,sizeof(buffer)-1);

    printf(buffer);

    close(sock);
    return 0;
}
```
选择你的编译方式编译出来即可

## 进行公网的传输
参考csdn的来杯开水，点击[这里](https://blog.csdn.net/HHHSSD/article/details/117410122)查看原文
### 开启你的8000端口用于传输数据
```
开启8000端口：
firewall-cmd --zone=public --add-port=8000/tcp --permanent
重新载入防火墙
firewall-cmd --reload
查看8000端口是否已经开放
firewall-cmd --list-ports
最后在你的云服务器上开启对应8000端口的安全组即可
```
### server端
放在你的云服务器上
```
#include<stdio.h>
#include <unistd.h>
#include<sys/types.h>
 
#include<sys/socket.h>
 
#include<netinet/in.h>
 
#include<arpa/inet.h>
 
#include<stdlib.h>
 
#include<string.h>
 
 
int main()
{
 
        int s_fd;
        int c_fd;
        int n_read;
        char readBuf[128];
        // char *msg = "I get your connect";
        char msg[128] = {0};
 
        struct sockaddr_in s_addr;
        struct sockaddr_in c_addr;
 
        memset(&s_addr,0,sizeof(struct sockaddr_in));   //数据的清空,清空完配置
        memset(&c_addr,0,sizeof(struct sockaddr_in));
 
        //1.socket
 
        s_fd=socket(AF_INET,SOCK_STREAM,0);
 
        if(s_fd == -1){
                perror("socket");
                exit(-1);
        }
 
        s_addr.sin_family= AF_INET;
        s_addr.sin_port = htons(8000);   //端口号 该端口号需要网络与安全->安全组中先创建好
        inet_aton("10.0.16.8",&s_addr.sin_addr); //IP地址 注意ip地址是内网的ip地址,把字符串形式的“192.168**”转化为网络能识别的格式
 
        //2.bind
 
 
        bind(s_fd,(struct sockaddr *)&s_addr,sizeof(struct sockaddr_in));//Bind()函数：IP号端口号与相应描述字赋值函数，用于绑定IP地址和端口号到socketfd
        //3.listen
        listen(s_fd,10);                            //监听设置函数
 
        //4.accept
 
        socklen_t  length = sizeof(struct sockaddr_in);   //计算长度
 
        while(1)                                    //循环等候连接服务器
        {
                c_fd =accept(s_fd,(struct sockaddr *)&c_addr,&length); //accept函数由TCP服务器调用，用于从已完成的连接队列对头返回下一个已完成连接，如果已完成的队列为空，那么进程被投入睡眠。
                if(c_fd == -1){
 
                        perror("accept");
                }
 
                if(fork() == 0)    //创建一个子进程使他和服务器进行read的操作
                {
                        while(1)
                        {
                                printf("gte connect: %s\n",inet_ntoa(c_addr.sin_addr));
                                n_read = read(c_fd,readBuf,128); //在套接字通性中进行字节读取函数： read();
                                if(n_read == -1)
                                {
                                        perror("read");
                                }else{
                                        printf("get message:%d %s\n",n_read,readBuf);
 
                                }
                        }
                }
                if(fork()==0)                   //创建一个子进程使它和服务器进行write的操作
                {
                        while(1)
                        {
                                memset(msg,0,sizeof(msg));
                                printf("Input:");
                                fgets(msg,sizeof(msg),stdin);
                                write(c_fd,msg,strlen(msg));
                        }
                }
        }
        return 0;
 
}
```
### client端
```
#include<stdio.h>
#include <unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
 
#include<netinet/in.h>
 
#include<arpa/inet.h>
 
#include<stdlib.h>
 
#include<string.h>
 
 
int main()
{
        int c_fd;
        int n_read;
        char readBuf[128];
        char msg[128]= {0} ;
        struct sockaddr_in c_addr;
        memset(&c_addr,0,sizeof(struct sockaddr_in));
        c_fd = socket(AF_INET,SOCK_STREAM,0);      //创建套接字
        if(c_fd == -1)
        {
                perror("connect");
                exit(-1);
        }
        c_addr.sin_family = AF_INET;
        c_addr.sin_port = htons(8000);      //这里要填自己写在服务器里已经添加过的端口号
 
        inet_aton("43.138.55.15",&c_addr.sin_addr);
 
        if(connect(c_fd,(struct sockaddr *)&c_addr,sizeof(struct sockaddr))== -1)  //客户端的connect函数该函数用于绑定之后的client端（客户端），与服务器建立连接
        {
                perror("connect");
        }
        while(1)
        {
 
 
                //3.write()
                if(fork() == 0)      //创建一个子进程与服务端进行write的操作
                {
                        while(1)
                        {
                                memset(msg,0,sizeof(msg));
                                printf("Input:\n");
                                fgets(msg,sizeof(msg),stdin);
                                write(c_fd,msg,strlen(msg));
                        }
                }
                //4
                //
                n_read  = read(c_fd,readBuf,sizeof(readBuf));    //客户端对服务端进行read的读取
 
                if(n_read == -1){
                        perror("read");
                }else{
                        printf("get message from server:%d,%s\n",n_read,readBuf);
 
 
                }
 
        }
        return 0;
}
```
