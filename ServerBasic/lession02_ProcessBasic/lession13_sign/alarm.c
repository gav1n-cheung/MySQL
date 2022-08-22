/*
    #include <unistd.h>
    unsigned int alarm(unsigned int seconds);
        -功能：设置定时器，函数调用开始倒计时，当倒计时为0，函数会给当前的进程发送一个信号:SIGALARM
        -参数：seconds：倒计时的时长，单位:s.如果参数为0，定时器无效(不进行倒计时，不发信号)
            取消一个定时器，通过alarm(0)
        -返回值：
            -之前没有定时器，返回0
            -之前有定时器，返回之前的定时器剩余的时间
        -SIGALARM:默认终止当前的信号，每个进程都有且只有唯一的一个定时器
            alarm(10);->返回0
            过一秒
            alarm(5);返回9
        该函数是非阻塞的
*/
#include<unistd.h>
#include<stdio.h>

int main(){
    int seconds = alarm(5);
    printf("seconds = %d\n",seconds);
    sleep(2);
    seconds = alarm(10);
    printf("seconds = %d\n",seconds);
    while(1){

    }
    return 0;
}