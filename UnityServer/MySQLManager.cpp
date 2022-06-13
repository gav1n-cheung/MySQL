#include "MySQLManager.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <typeinfo>
using namespace std;
bool MySQLManager::Init(ConnectionInfo& info){
    mysql_init(&m_mysql);
    if(!mysql_real_connect(&m_mysql,info.host,info.user,info.password,info.database,info.port,info.unix_socket,info.client_flag)){
        // std::cout<<"MySQL connect failed!"<<std::endl;
        return false;
    }
    // std::cout<<"MySQL connect success!"<<std::endl;
    return true;
}

bool MySQLManager::FreeConnect(){
    mysql_free_result(m_res);
    mysql_close(&m_mysql);
    return false;
}

bool MySQLManager::ExecuteSql(std::string sql){
    if(mysql_query(&m_mysql,sql.c_str())){
        std::cerr<<"MySQL execute failed! Error info :"<<mysql_error(&m_mysql)<<std::endl;
        return false;
    }
    std::cout<<"MySQL execute success!"<<std::endl;
    return true;
}

MYSQL_RES* MySQLManager::QueryData(std::string sql){
    if(mysql_query(&m_mysql,sql.c_str())){
        cout<<"error"<<endl;
        // std::cerr<<"MySQL query failed! Error info :"<<mysql_error(&m_mysql)<<std::endl;
        return nullptr;
    }
    std::cout<<"MySQL query success!"<<std::endl;
    m_res = mysql_store_result(&m_mysql);
    return m_res;
}

std::vector<string> MySQLManager::PrintQueryRes(){
    std::vector<string> res;
    if(!m_res){
        std::cout<<"There are no results!"<<std::endl;
        return res;
    }

    MYSQL_FIELD* field = nullptr;
    char field_name[64][32];
    for(int i=0;field = mysql_fetch_field(m_res);i++){
        strcpy(field_name[i],field->name);       
    }
    int columns = mysql_num_fields(m_res);
    // for(int i=0;i<columns;i++) std::cout<<"\t"<<field_name[i];
    // std::cout<<"\n"<<std::endl;
    MYSQL_ROW row;
    while(row=mysql_fetch_row(m_res)){
        for(int i=0;i<columns;i++) {
            // std::cout<<"\t"<<row[i];
            res.push_back(row[i]);
        }
        // std::cout<<"\n"<<std::endl;
    }
    return res;
}