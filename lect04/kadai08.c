#include <stdio.h>

int strcmp1(char*,char*);

int main(){
    char *s = "hoge hoge";
    char *t = "hogehoge";
    printf("strcmp1 = %d\n",strcmp1(s,t));
    return 0;
}

int strcmp1(char *s,char *t){
    int i;
    for(;*s == *t;s++,t++){
        if(*s == '\0'){
            return 0;
        }
    }
    return *s-*t;
}