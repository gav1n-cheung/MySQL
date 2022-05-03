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
