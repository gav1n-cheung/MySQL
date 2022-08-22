/*
    #include <pthread.h>
    int pthread_cancel(pthread_t thread);
        -功能：取消线程(让线程终止)
            取消某个线程，可以终止某个线程的运行，但是不是立马终止，而是当子线程执行到一个取消点，线程才会终止
            取消点：系统规定好的一些系统调用，我们可以粗略的理解为用户区到内核区的切换，这个位置称之为取消点
*/
#include<stdio.h>
#include<pthread.h>
#include<string.h>
#include<unistd.h>

void* callback(void* arg){
    printf("child thread tid:%ld\n",pthread_self());
    for(int i=0;i<100;i++){
        printf("child %d\n",i);
    }
    return  NULL;
}

int main(){
    pthread_t tid;
    int ret = pthread_create(&tid,NULL,callback,NULL);
    if(ret!=0){
        printf("erro1:%s\n",strerror(ret));
    }
    printf("tid:%ld,main tid:%ld\n",tid,pthread_self());
    ret = pthread_cancel(tid);
    if(ret!=0){
        printf("erro1:%s\n",strerror(ret));
    }
    for(int i=0;i<5;i++){
        printf("%d\n",i);
    }
    pthread_exit(NULL);
    return 0;
}