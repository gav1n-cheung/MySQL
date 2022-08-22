/*
    使用多线程实现买票得案例
    有三个窗口，一共是一百张票
*/
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

//全局变量，所有得线程都共享同一份资源
int tickets = 100;

void* sellticket(void* arg){
    //卖票
    while(tickets>0){
        usleep(5000);
        printf("%ld 正在卖第%d张门票\n",pthread_self(),tickets);
        tickets--;
    }
    return NULL;
}

int main(){
    //创建3个子线程
    pthread_t tid1,tid2,tid3;
    pthread_create(&tid1,NULL,sellticket,NULL);
    pthread_create(&tid2,NULL,sellticket,NULL);
    pthread_create(&tid3,NULL,sellticket,NULL);

    //回收子线程得资源,阻塞
    pthread_join(tid1,NULL);    
    pthread_join(tid2,NULL);    
    pthread_join(tid3,NULL);    
    //设置线程分离，非阻塞
    // pthread_detach(tid1);
    // pthread_detach(tid2);
    // pthread_detach(tid3);
    pthread_exit(NULL);//退出主线程

    return 0;
}
