/*
int pthread_attr_init(pthread_attr_t *attr);
    -初始化线程属性变量
int pthread_attr_destroy(pthread_attr_t *attr);
    -释放线程属性的资源
int pthread_attr_getdetachstate(const pthread_attr_t *attr, int *detachstate);
    -获取线程分离的状态属性
int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate);
    -设置线程分离的状态属性
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
    //创建一个线程属性变量
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    //设置属性
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

    //创建一个子线程
    pthread_t tid;
    int ret = pthread_create(&tid,&attr,callback,NULL);
    if(ret!=0){
        printf("erro1:%s\n",strerror(ret));
    }
    //输出主线程和子线程的tid
    printf("tid:%ld,main tid:%ld\n",tid,pthread_self());
    //设置子线程分离,子线程分离后，就不需要主线程来回收子线程的相关资源了
    //获取线程栈的大小
    size_t size;
    pthread_attr_getstacksize(&attr,&size);
    printf("thread stack size = %d\n",size);
    if(ret!=0){
        printf("error2:%s\n",strerror(ret));
    }
    ret = pthread_join(tid,NULL);
    if(ret!=0){
        printf("error3:%s\n",strerror(ret));
    }
    //释放线程属性资源
    pthread_attr_destroy(&attr);
    pthread_exit(NULL);
    return 0;
}