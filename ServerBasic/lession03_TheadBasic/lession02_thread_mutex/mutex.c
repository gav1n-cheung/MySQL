/*
◼ 互斥量的类型 pthread_mutex_t
◼ int pthread_mutex_init(pthread_mutex_t *restrict mutex,const pthread_mutexattr_t *restrict attr);
    -初始化互斥量
    -参数：
        -mutex：需要初始化得互斥量变量
        -attr：互斥量相关属性，NULL
    -restrict:C语言的修饰符，被修饰的指针，不能被另外的一个指针进行操作 
        pthread_mutexattr_t *restrict mutex = xxx;
        pthread_mutexattr_t * mutex1 = mutex;
        如果使用metex1操作mutex指向的数据，则报错；restrict保证了只有被该修饰符修饰了的指针能够操作指向区域。
◼ int pthread_mutex_destroy(pthread_mutex_t *mutex);
    -释放互斥量的资源
◼ int pthread_mutex_lock(pthread_mutex_t *mutex);
    -加锁，阻塞的，如果有一个线程加锁了，那么其他的线程只能阻塞等待
◼ int pthread_mutex_trylock(pthread_mutex_t *mutex);
    -尝试加锁，如果加锁失败，则不会阻塞，会直接返回
◼ int pthread_mutex_unlock(pthread_mutex_t *mutex);
    -释放锁，解锁
*/
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

//全局变量，所有得线程都共享同一份资源
int tickets = 100;
//创建一个互斥量
pthread_mutex_t mutex;

void* sellticket(void* arg){
    //卖票
    while(1){
        //临界区加锁
        pthread_mutex_lock(&mutex);
        if(tickets>0){
            printf("%ld 正在卖第%d张门票\n",pthread_self(),tickets);
            tickets--;
        }else{
            //解锁
            pthread_mutex_unlock(&mutex);
            break;
        }
        //解锁
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(){
    //初始化互斥量
    pthread_mutex_init(&mutex,NULL);

    //创建3个子线程
    pthread_t tid1,tid2,tid3;
    pthread_create(&tid1,NULL,sellticket,NULL);
    pthread_create(&tid2,NULL,sellticket,NULL);
    pthread_create(&tid3,NULL,sellticket,NULL);

    //回收子线程得资源,阻塞
    pthread_join(tid1,NULL);    
    pthread_join(tid2,NULL);    
    pthread_join(tid3,NULL);    
    pthread_exit(NULL);//退出主线程

    //释放互斥量资源
    pthread_mutex_destroy(&mutex);
    return 0;
}
