/*
网络通信时，需要将主机字节序转换成网络字节序(大端),另外一端获取到数据之后根据情况将网络字节序转换成主机字节序
*/
#include<stdio.h>
#include<arpa/inet.h>

int main(){

    //htons 转换端口
    unsigned short a = 0x0102;
    unsigned short b = htons(a);
    printf("a: %x\n",a);
    printf("b: %x\n",b);

    //htonl 转换ip
    char buf[4] = {192,168,1,100};
    int num = *(int*) buf;
    unsigned int sum = htonl(num);
    unsigned char *p = (char *)&sum;
    printf("%d,%d,%d,%d\n",*p,*(p+1),*(p+2),*(p+3));

    //ntohs 转换端口
    unsigned char buf1[4] = {192,168,1,1};
    int num1 = *(int*)buf1;
    int sum1 = ntohl(num1);
    unsigned char *ptr = (unsigned char*) &sum1;
    unsigned char *ptr1 = (unsigned char*) &num1;
    printf("%d,%d,%d,%d\n",*ptr1++,*ptr1++,*ptr1++,*ptr1++);//192,168,1,1 这里主机默认就是小端，高地址位被存储到高地址内存中去了
    printf("%d,%d,%d,%d\n",*ptr,*(ptr+1),*(ptr+2),*(ptr+3));//1,1,168,192 因此这里将网络序转换为本机的字节序，就是将192,168,1,1作为大端来操作的
                                                        //192作为数据的高位被存储到到了内存的高位中，即最后的位置去了，
    //ntohl 
    return 0;
}