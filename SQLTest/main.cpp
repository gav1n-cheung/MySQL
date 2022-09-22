#include <iostream>
#include <mysql/mysql.h>
#include <thread>
#include <pcl/io/pcd_io.h>
#include <pcl/visualization/cloud_viewer.h>
#include <iomanip>
#include "omp.h"

using namespace std;

int main() {
    cout<<setiosflags(ios::fixed)<<setprecision(2);
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
    pcl::io::loadPCDFile("0scans.pcd", *cloud);
    cout<<cloud->points[0].x<<" "<<cloud->points[0].y<<" "<<cloud->points[0].z<<endl;
     double t1 = omp_get_wtime();
     MYSQL mysql;
     mysql_init(&mysql);
     const string host = "43.138.104.62";
     const string user = "cheung";
     const string password = "128veg8A@";
     const string db = "lg_data";
     if (!mysql_real_connect(&mysql, host.c_str(), user.c_str(), password.c_str(), db.c_str(), 3306, 0, 0))
         cout << "connect mysql failed!" << mysql_error(&mysql) << endl;
     else
         cout << "connect mysql success!" << endl;
    double t2 = omp_get_wtime();
    int index = 0;
    string sql = "insert into env_data(x,y,z,r,g,b) values";
    for (auto item: *cloud) {
        char tmp[8*100];
        sprintf(tmp,"(%.3f,%.3f,%.3f,%d,%d,%d),",item.x,item.y,item.z,(int)item.r,(int)item.g,(int)item.b);
        sql+=tmp;
        index++;

        if(index>50000) {
            cout<<index<<endl;
            sql.pop_back();
            if (mysql_query(&mysql, sql.c_str())) perror("sql query");
            else cout<<"query success"<<endl;
            sql = "insert into point_cloud_data(x,y,z,r,g,b) values";
            index=0;
        }
    }
    sql.pop_back();
    if (mysql_query(&mysql, sql.c_str())) perror("sql query");
    else cout<<"query success"<<endl;
    sql = "insert into point_cloud_data(x,y,z,r,g,b) values";
    mysql_close(&mysql);

    return 0;
}
