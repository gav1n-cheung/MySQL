/*
int sigprocmask(int how,const sigset_t *set,sigset_t *oldset);
    -功能：将自定义信号机中的数据设置到内核中(设置阻塞，解除阻塞，替换)
    -参数：
        -how:如何对内核阻塞信号集进行处理
            SIG_BLOCK:将用户设置的阻塞信号集添加到内核中，内核中原来的数据不变
                假设内核中默认的阻塞信号集为mask，则添加后为mask|set
            SIG_UNBLOCK:根据用户设置的数据，对内核中的数据进行解除阻塞
                mask &= ~set 
                eg: 原阻塞集10010 添加第2位和第4位阻塞，则为 10010 | 00101 = 10111
                    如果要解除第2位和第4位的阻塞，则为10111 & ~00101 = 10111 & 11010 = 10010
            SIG_SETMASK:覆盖内核中的值
        -set:传入参数，已经初始化的用户自定义信号集
        -oldset:保存设置之前的内核中的阻塞信号集的状态,一般设为NULL

    -返回值：
        成功返回0，失败返回-1，EFAULT，EFAULT

int sigpending(sigset_t *set)
    -功能:获取内核中的未决信号集
    -参数:set-传出参数，保存的是内核中的未决信号集中的信息

运行程序加上 & 可以后台，使用fg将后台程序调到前台来
*/

//编写一个程序，把所有的常规信号(1-31)的未决状态打印到屏幕
//设置某些信号是阻塞的，通过键盘产生这些信号

#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<unistd.h>
int main(){
    //设置2、3号信号阻塞
    sigset_t set;
    sigemptyset(&set);
    //将2、3号信息添加到信号集中
    sigaddset(&set,SIGINT);
    sigaddset(&set,SIGQUIT);
    //修改内核中的阻塞信号集
    sigprocmask(SIG_BLOCK,&set,NULL);
    int num =0;
    while (1)
    {
        //获取当前未决信号集的数据
        sigset_t pendingset;
        sigemptyset(&pendingset);
        sigpending(&pendingset);
        //遍历前32位
        for(int i=1;i<=32;i++){
            if(sigismember(&pendingset,i)==1){
                printf("1");
            }else if(sigismember(&pendingset,i)==0){
                printf("0");
            }else{
                perror("sigismember");
                exit(0);
            }
        }
        num++;
        printf("\n");
        sleep(1);
        if(num==10){
            sigprocmask(SIG_UNBLOCK,&set,NULL);
        }
    }
    return 0;
}
