/*
    #include <pthread.h>

    int pthread_join(pthread_t thread, void **retval);
        -功能：和一个已经终止的线程进行连接
            回收子线程的资源
            特点：是阻塞函数，调用一次回收一个子线程
                一般在主线程中使用，
        -参数：
            -thread：需要回收的子线程的Id
            -retval:接受子线程退出时的返回值
                为什么这里是二级指针？因为调用该方法的传出参数是指针类型*
                而如果我们想要对传入的指针类型进行修改，则需要是指针类型的按地址传递才行；
                int* data = 10;
                void change(int* a){
                    a = 20;
                }
                change(&data);//此时是形参，并不会改变外部的data
                void change(int** a){
                    a =20;
                }
                change(&data);//此时是按地址传递，会改变data值
        -返回值：
            成功0，失败错误号
*/
#include<pthread.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>

int value = 10;

void *callback(void* arg){
    printf("child thread create!id:%ld\n",pthread_self());
    sleep(1);
    // return NULL;//pthread_exit(NULL);
    // int value = 10;//局部变量，由于线程被回收，栈空间也被释放了，因此返回值是随机值
    pthread_exit((void*)&value);//同return (void*)&value;
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
    int * thread_retval;
    ret = pthread_join(tid,(void**)&thread_retval);
    if(ret!=0) {
        printf("%s\n",strerror(ret));
    }
    printf("exit data:%d\n",*thread_retval);
    printf("回收子线程资源成功\n");
    pthread_exit(NULL);//让主线程退出，不会影响其他正常运行的线程
    printf("main thread exit\n");
    return 0;
}
