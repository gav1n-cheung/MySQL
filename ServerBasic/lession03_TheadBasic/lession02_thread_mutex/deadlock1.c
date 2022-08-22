#include<pthread.h>
#include<stdio.h>
#include<unistd.h>

int num1;
int num2;

pthread_mutex_t lock1;
pthread_mutex_t lock2;

void* callback1(void* arg){
    pthread_mutex_lock(&lock1);
    sleep(1);
    //由于线程2lock了lock2,因此被阻塞
    pthread_mutex_lock(&lock2);
    printf("workA....\n");
    pthread_mutex_unlock(&lock2);
    pthread_mutex_unlock(&lock1);
    return NULL;
}

void* callback2(void* arg){
    pthread_mutex_lock(&lock2);
    //由于线程1lock了lock1，因此被阻塞，最终形成了死锁
    pthread_mutex_lock(&lock1);
    printf("workB....\n");
    pthread_mutex_unlock(&lock1);
    pthread_mutex_unlock(&lock2);
    return NULL;
}

int main(){
    num1=0;
    num2=0;
    pthread_mutex_init(&lock1,NULL);
    pthread_mutex_init(&lock2,NULL);
    pthread_t tid1,tid2;
    pthread_create(&tid1,NULL,callback1,NULL);
    pthread_create(&tid2,NULL,callback2,NULL);
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    pthread_mutex_destroy(&lock1);
    pthread_mutex_destroy(&lock2);
    return 0;
}