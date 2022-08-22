#include<stdio.h>
#include<arpa/inet.h>

int main(){
    //创建一个点分十进制的ip地址字符串
    char ip[] = "192.168.1.3";
    unsigned int num = 0;
    //将点分十进制转换为int类型的整数
    int ret = inet_pton(AF_INET,ip, &num);
    if(ret!=1){
        perror("inet_pton");
    }
    unsigned char* p = (unsigned char*) &num;
    printf("%d.%d.%d.%d\n",*p,*(p+1),*(p+2),*(p+3));
    //将网络字节序的整数转换为点分十进制的IP字符串
    char buffer[20];
    inet_ntop(AF_INET,&num,buffer,20);
    printf("%s\n",buffer);
    return 0;
}