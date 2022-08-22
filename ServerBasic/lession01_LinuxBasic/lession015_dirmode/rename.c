/*
    #include <stdio.h>

    int rename(const char *oldpath, const char *newpath);
*/
#include<stdio.h>

int main(){
    int ret = rename("newDir","newDir1");
    if(ret==-1){
        perror("rename");
        return -1;
    }
    return 0;
}