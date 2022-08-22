/*
条件变量的类型 pthread_cond_t
    int pthread_cond_init(pthread_cond_t *restrict cond, const pthread_condattr_t *restrict attr);
    int pthread_cond_destroy(pthread_cond_t *cond);
    int pthread_cond_wait(pthread_cond_t *restrict cond,pthread_mutex_t *restrict mutex);
        -阻塞函数，调用了该函数，线程会阻塞
    int pthread_cond_timedwait(pthread_cond_t *restrict cond,pthread_mutex_t *restrict mutex, const struct timespec *restrict abstime);
        -等待多长时间，调用了该函数，线程会阻塞设定的时间
    int pthread_cond_signal(pthread_cond_t *cond);
        -唤醒一个或多个等待的线程
    int pthread_cond_broadcast(pthread_cond_t *cond);
        -唤醒所有等待的线程
*/
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>

//创建一个互斥量
pthread_mutex_t mutex;
//创建条件变量
pthread_cond_t cond;


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
        //只要生产了一个，就通知消费者消费
        pthread_cond_signal(&cond);
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
        if(head==NULL){
            //没有数据，需要等待
            pthread_cond_wait(&cond,&mutex);//条件变量拿到互斥量会先进行解锁，不会阻塞其他互斥量锁死的临界区
        }
        head = head->next;
        printf("del node,num :%d,tid:%ld\n",tmp->val,pthread_self());
        free(tmp);
        usleep(100);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}


int main(){
    pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&cond,NULL);
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
    pthread_cond_destroy(&cond);
    pthread_exit(NULL);
    return 0;
}