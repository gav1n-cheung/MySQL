#include<stdio.h>

void change1(int a){
    a=10;
}
void change2(int* a){
    *a=20;
}
void change3(int** a){
    *a=30;
}

int main(){
    int a = 0;
    int *p = &a;
    int *t = p;
    change1(a);
    printf("%d\n",a);
    change2(p);
    printf("%d\n",a);
    change3(&p);
    printf("%d\n",p);
}