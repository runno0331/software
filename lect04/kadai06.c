#include <stdio.h>

int strlen1(char*);

int main(){
    char *s = "Hello World!";
    printf("length of %s is %d\n",s,strlen1(s));
    return 0;
}

int strlen1(char *s){
    char *t = s;
    while(*t++ != '\0'){
        ;
    }
    return t-s-1;
}