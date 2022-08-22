/*
    #include <pthread.h>

    void pthread_exit(void *retval);
        功能：终止一个线程，在那个线程中调用，就表示终止那个线程
        参数：
            retval:需要传递一个指针，作为一个返回值，可以在pthread_join()中获取到
    pthread_h pthread_self(void);
        功能：返回当前的线程ID
    int pthread_equal(pthread_t t1,pthread_t t2);
        功能：比较两个线程ID是否相等
        不同的操作系统，pthread_t类型的实现不一样，有的是无符号的长整型，有的是用结构体实现的
    
*/
#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>

void *callback(void* arg){
    printf("child thread create!id:%ld\n",pthread_self());
    return NULL;//相当于pthread_exit(NULL);
}

int main(){
    pthread_t tid;
    int ret = pthread_create(&tid,NULL,callback,NULL);
    if(ret!=0) {
        printf("%s\n",strerror(ret));
    }
    for(int i=0;i<5;i++){
        printf("%d\n",i);
    }
    printf("main thread id:%ld,tid:%ld\n",pthread_self(),tid);
    pthread_exit(NULL);//让主线程退出，不会影响其他正常运行的线程
    printf("main thread exit\n");
    return 0;
}