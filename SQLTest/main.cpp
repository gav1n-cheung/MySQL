#include <iostream>
#include <mysql/mysql.h>
#include <thread>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/cloud_viewer.h>
#include <iomanip>

using namespace std;

int main() {
    cout<<setiosflags(ios::fixed)<<setprecision(2);
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::io::loadPCDFile("scans.pcd", *cloud);
//    pcl::visualization::CloudViewer viewer("input file visualization");
//    viewer.showCloud(cloud);
//    while(!viewer.wasStopped()){}
    MYSQL mysql;
    mysql_init(&mysql);
    const string host = "43.138.55.15";
    const string user = "cheung";
    const string password = "128veg8A@";
    const string db = "COAL_DATA";
    if (!mysql_real_connect(&mysql, host.c_str(), user.c_str(), password.c_str(), db.c_str(), 3306, 0, 0))
        cout << "connect mysql failed!" << mysql_error(&mysql) << endl;
    else
        cout << "connect mysql success!" << endl;
    int index = 0;
    string sql = "insert into table3(x,y,z) values";
    for (auto item: *cloud) {
        char tmp[8*100];
        sprintf(tmp,"(%f,%f,%f),",item.x,item.y,item.z);
        sql+=tmp;
        index++;
//        cout<<sql<<endl;
//        string sql = "insert into table3(x,y,z) values("+item.x+","+item.y+","+item.z+")";
//        else cout << "mysql_real_query success! " << endl;
//        break;
        if(index>100000) {
            cout<<index<<endl;
            sql.pop_back();
            if (mysql_query(&mysql, sql.c_str())) cout << "mysql_real_query faild!" << endl;
            else cout<<"query success"<<endl;
            sql = "insert into table3(x,y,z) values";
            index=0;
        }
    }
    sql.pop_back();
    if (mysql_query(&mysql, sql.c_str())) cout << "mysql_real_query faild!" << endl;
    else cout<<"query success"<<endl;
    sql = "insert into table3(x,y,z) values";

//    cout<<sql<<endl;

//    cout << x.size() << endl;
//    cout<<x<<endl;
//    string sql = "insert into table2(x) values('"+x+"')";
//    int res = mysql_real_query(&mysql,sql.c_str(),sizeof(sql));
//    res =mysql_query(&mysql,sql.c_str());
//    if(!res) cout<<"mysql_real_query faild!"<<sql<<endl;
//    else cout<<"mysql_real_query success! "<<sql<<endl;
//
//    string sql1 = "select * from table2";
//    int res1 = mysql_real_query(&mysql,sql1.c_str(),sizeof(sql1));
//    res1 =mysql_query(&mysql,sql.c_str());
//    if(!res1) cout<<"mysql_real_query faild!"<<sql1<<" "<<mysql_error(&mysql)<<endl;
//    else cout<<"mysql_real_query success! "<<sql1<<endl;
//
//
//    MYSQL_RES* result = mysql_use_result(&mysql);
//    // MYSQL_RES* result = mysql_store_result(&mysql);
//    if(!result) cout<<"mysql_use_result failed! "<<mysql_error(&mysql)<<endl;
//    MYSQL_FIELD *field = 0;
//    while(field=mysql_fetch_field(result)) cout<<"key: "<<field->name<<endl;
//    int fnum = mysql_num_fields(result);
//
//    MYSQL_ROW row;
//    while(row=mysql_fetch_row(result)){
//        unsigned long * lens = mysql_fetch_lengths(result);
//        for(int i=0;i<fnum;i++){
//            cout<<mysql_fetch_field_direct(result,i)->name<<":";
//            if(row[i]) cout<<row[i];
//            else cout<<"NULL";
//            cout<<",";
//        }
//        cout<<"\n==============================="<<endl;
//    }
    mysql_close(&mysql);
    return 0;
}
