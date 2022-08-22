/*
    信号量的类型 sem_t
    int sem_init(sem_t *sem, int pshared, unsigned int value);
        -初始化信号量
        -参数:
            -sem:信号量变量的地址
            -pshared:=0为线程间通信，其他值为进程间通信
            -value:信号量中的值
    int sem_destroy(sem_t *sem);
        -释放资源
    int sem_wait(sem_t *sem);
        -对信号量加锁，调用一次对信号量的值-1，如果信号值为0，则阻塞
    int sem_trywait(sem_t *sem);

    int sem_timedwait(sem_t *sem, const struct timespec *abs_timeout);

    int sem_post(sem_t *sem);
        -对信号量减锁，调用一次对信号量的值+1，
    int sem_getvalue(sem_t *sem, int *sval);
*/
#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include<unistd.h>

struct Node{
    int val;
    struct Node* next;
};
//创建两个信号量
sem_t csem,psem;
pthread_mutex_t mutex;
struct Node* head = NULL;

void* producer(void* arg){
    while(1){
        sem_wait(&psem);
        pthread_mutex_lock(&mutex);
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->val=rand()%100;
        newNode->next = head;
        head = newNode;
        printf("==producer,tid:%ld,num:%d\n",pthread_self(),newNode->val);
        pthread_mutex_unlock(&mutex);
        sem_post(&csem);
        usleep(100);
    }
    return NULL;
}
void* customer(void* arg){
    while(1){
        sem_wait(&csem);
        pthread_mutex_lock(&mutex);
        struct Node* tmp = head;
        head = head->next;
        printf("++customer,tid:%ld,num:%d\n",pthread_self(),tmp->val);
        free(tmp);
        pthread_mutex_unlock(&mutex);
        sem_post(&psem);
    }
    return NULL;
}


int main(){
    sem_init(&csem,0,0);
    sem_init(&psem,0,10);
    pthread_mutex_init(&mutex,NULL);
    pthread_t ptid[5],ctid[5];
    for(int i=0;i<5;i++){
        pthread_create(&ptid[i],NULL,producer,NULL);
        pthread_create(&ctid[i],NULL,customer,NULL);
    }
    for(int i=0;i<5;i++){
        pthread_detach(ptid[i]);
        pthread_detach(ctid[i]);
    }
    while(1){
        sleep(10);
    }
    sem_destroy(&csem);
    sem_destroy(&psem);
    pthread_mutex_destroy(&mutex);
    pthread_exit(NULL);
    return 0;
}


