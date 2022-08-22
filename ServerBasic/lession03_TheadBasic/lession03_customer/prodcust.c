/*
    生产者消费者模型
*/
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>

//创建一个互斥量
pthread_mutex_t mutex;

struct Node{
    int val;
    struct Node* next;
};

struct Node* head = NULL;

void* producer(void* arg){
    while(1){
        pthread_mutex_lock(&mutex);
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->next = head;
        head = newNode;
        newNode->val = rand()%1000;
        printf("add node,num:%d,tid:%ld\n",newNode->val,pthread_self());
        pthread_mutex_unlock(&mutex);
        usleep(100);
    }
    return NULL;
}

void* customer(void* arg){
    while(1){
        pthread_mutex_lock(&mutex);
        //保存头节点指针
        struct Node* tmp = head;
        //判断容器是否有数据
        if(head!=NULL){
            //有数据
            head = head->next;
            printf("del node,num :%d,tid:%ld\n",tmp->val,pthread_self());
            free(tmp);
            usleep(100);
        }
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}


int main(){
    pthread_mutex_init(&mutex,NULL);
    //创建5个生产者线程，和5个消费者线程
    pthread_t ptids[5],ctids[5];
    for(int i=0;i<5;i++){
        pthread_create(&ptids[i],NULL,producer,NULL);
        pthread_create(&ctids[i],NULL,customer,NULL);
    }
    for(int i=0;i<5;i++){
        pthread_detach(ptids[i]);
        pthread_detach(ctids[i]);
    }
    while(1){
        sleep(10);
    }
    pthread_mutex_destroy(&mutex);
    pthread_exit(NULL);
    return 0;
}