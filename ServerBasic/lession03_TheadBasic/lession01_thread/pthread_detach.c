/*
    #include <pthread.h>

    int pthread_detach(pthread_t thread);
        功能：分离一个线程。被分离的线程在终止的时候，会自动释放资源返回给系统。
            1.不能多次分离，会产生不可预料的行为
            2.不能去连接一个已经分类的线程，会报错。
        参数：需要分离的线程的ID
        返回值：
            成功0，失败返回错误号
*/
#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<unistd.h>

void* callback(void* arg){
    printf("child thread tid:%ld\n",pthread_self());
    return  NULL;
}

int main(){
    //创建一个子线程
    pthread_t tid;
    int ret = pthread_create(&tid,NULL,callback,NULL);
    if(ret!=0){
        printf("erro1:%s\n",strerror(ret));
    }
    //输出主线程和子线程的tid
    printf("tid:%ld,main tid:%ld\n",tid,pthread_self());
    //设置子线程分离,子线程分离后，就不需要主线程来回收子线程的相关资源了
    ret = pthread_detach(tid);
    if(ret!=0){
        printf("error2:%s\n",strerror(ret));
    }
    //设置分离后再连接子线程会报错
    // ret = pthread_join(tid,NULL);
    // if(ret!=0){
    //     printf("error3:%s\n",strerror(ret));
    // }
    pthread_exit(NULL);
    return 0;
}