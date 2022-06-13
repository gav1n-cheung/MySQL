#include <mysql/mysql.h>
#include <iostream>
#include <string.h>
#include <vector>
struct ConnectionInfo
{
    /* data */
    const char* host;
    const char* user;
    const char* password;
    const char* database;
    const char* unix_socket;
    long client_flag;
    int port;

    ConnectionInfo():
    host("127.0.01"),port(3306),unix_socket(nullptr),client_flag(0){};
};

class MySQLManager{
    public:
        bool Init(ConnectionInfo& info);
        bool FreeConnect();
        bool ExecuteSql(std::string sql);
        MYSQL_RES* QueryData(std::string sql);
        std::vector<std::string> PrintQueryRes();
    private:
        MYSQL m_mysql;
        MYSQL_RES* m_res;
};
