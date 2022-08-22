/*
    一般情况下，main函数执行的线程为主线程，其余创建的线程称之为子线程。
    程序中默认只有一个进程，fork()函数调用，2进程
    程序中默认只有一个线程，pthread_create()函数调用，2个线程
    #include <pthread.h>

    int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
                       void *(*start_routine) (void *), void *arg);
        -功能：创建一个子线程
        -参数：
            -thread:传出参数，线程创建成功后，子线程的线程id被写到该变量中
            -attr:需要设置线程的属性，一般使用默认值-NULL
            -start_routine:函数指针，这个函数是子线程需要处理的逻辑代码
            -arg:给第三个参数使用，传参
        -返回值：
            成功返回0，失败返回错误号，和之前的errno不太一样。
            回去错误号信息: char* strerrot(int errnum);
*/
#include<pthread.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>

void* callback(void* arg){
    printf("child thread...%d\n",*(int *)arg);
    return NULL;
}

int main(){
    //创建一个子线程
    pthread_t thread;
    int num = 10;
    int ret = pthread_create(&thread,NULL,callback,(void *)&num);
    if(ret!=0){
        printf("error:%s\n",strerror(ret));
    }
    for(int i=0;i<5;i++){
        printf("%d\n",i);
    }
    sleep(1);
    return 0;
}