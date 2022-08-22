/*
    一秒内电脑能计多少数？
*/
#include<stdio.h>
#include<unistd.h>
/*
    实际的时间 = 内核时间+用户时间+消耗的时间
    进行文件IO操作的时候比较浪费时间
    定时和进程的状态无关(自然定时法)。无论进程处于什么状态，alarm都会计时
*/
int main(){
    int seconds = alarm(1);
    while(1){
        printf("seconds:%d\n",seconds++);
    }
    return 0;
}