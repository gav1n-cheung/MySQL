#include <iostream>
#include "MySQLManager.h"
#include "Server.h"
#include "test.pb.h"
using namespace std;

MySQLManager mysql;
int socket_server;
sockaddr_in clnt_addr;
//数据库信息
struct MysqlInformation{
    const char* host;
    const char* user;
    const char* pwd;
    const char* db_name;
    int port;
};

//socket信息
struct SocketInformation
{
    TcpServer* s;
    TcpSocket* tcp;
    sockaddr_in addr;
};

int BuildMySQL(){
    ConnectionInfo info;
    info.host = "localhost";
    info.user = "cheung";
    info.password = "128veg8A@";
    info.database = "COAL_DATA";
    info.port = 3306;
    if(!mysql.Init(info)) {
        cout<<"MySQL  Init failed!"<<endl;
        return -1;
    }
    else {
        cout<<"\tMySQL  Init Success!"<<endl;
        return 0;
    }
}

string GetPointCloudData(){
    string x,y,z;
    string sql_x = "select x from table2";
    string sql_y = "select y from table2";
    string sql_z = "select z from table2";
    vector<string> tmp;
    mysql.QueryData(sql_x);
    tmp = mysql.PrintQueryRes();
    for(auto item:tmp) {
        x+=item;
        // cout<<item.size()<<endl;
    }
    cout<<"x size:"<<x.size()<<endl;
    // cout<<"x size:"<<tmp.size()<<endl;
    
    mysql.QueryData(sql_y);
    tmp = mysql.PrintQueryRes();
    for(auto item:tmp) {
        y+=item;
        // cout<<item.size()<<endl;
    }
    cout<<"y size:"<<y.size()<<endl;
    // cout<<"y size:"<<tmp.size()<<endl;

    mysql.QueryData(sql_z);
    tmp = mysql.PrintQueryRes();
    for(auto item:tmp) {
        z+=item;
        // cout<<item.size()<<endl;
    }
    cout<<"z size:"<<z.size()<<endl;
    // cout<<"z size:"<<tmp.size()<<endl;
    PointCloud pointcloud;
    pointcloud.set_x(x);
    pointcloud.set_y(y);
    pointcloud.set_z(z);
    string str;
    pointcloud.AppendToString(&str);
    return str;
}

int BuildSocket(){
    socket_server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
        serv_addr.sin_family= AF_INET;
        serv_addr.sin_port = htons(8001);   //端口号 该端口号需要网络与安全->安全组中先创建好
        inet_aton("10.0.16.8",&serv_addr.sin_addr); 
    if(bind(socket_server, (struct sockaddr*)&serv_addr, sizeof(serv_addr))) {
        cout<<"bind failed"<<endl;
        return -1;
    }
}

void ListenClient(){
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    int clnt_sock = accept(socket_server, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    if(clnt_sock==-1) cout<<"Client connect Failed!"<<endl;
    else{
        cout<<"Client connect success!\n"
            <<"Client IP : "<<inet_ntoa(clnt_addr.sin_addr)<<"\t"
            <<"Client Port : "<<clnt_addr.sin_port<<endl;
        string send_str = GetPointCloudData();
        // string send_str = "hello";
        const char*  data_ptr = send_str.data();
        size_t data_size = send_str.size();
        int bytes_sent;
        // cout<<send_str.size()<<endl;
        // char str[send_str.size()+1];
        // strcpy(str,send_str.c_str());
        // int length_sum=0;
        while(data_size>0){
            bytes_sent = write(clnt_sock,data_ptr,data_size);
            cout<<bytes_sent<<endl;
            if(bytes_sent<0) return;
            data_ptr += bytes_sent;
            data_size -= bytes_sent;
        }
    }
    close(clnt_sock);
}

int main(){
    cout<<"======================================================"<<endl;
    cout<<"             "<<"Liu Gong Server Software"<<"         "<<endl;
    cout<<"======================================================"<<endl;
    cout<<"step 1: Start socket Init ...."<<endl;
    if(BuildSocket()==-1) return 0;
    cout<<"\tSocket Init Success!"<<endl;
    cout<<"step 2: Start MySQL  Init ...."<<endl;
    if(BuildMySQL()==-1) return 0;
    GetPointCloudData();
    listen(socket_server,20);
    cout<<"Server software build Success!"<<endl;
    while(1){
        cout<<"\n"<<"Start Accpet Client Connect..."<<endl;
        ListenClient();
    }
    
    close(socket_server);
    return 0;
}