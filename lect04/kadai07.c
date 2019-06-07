#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 30

void strcpy1(char*,char*);

int main(){
    char *s = "Hello World";
    char *t;
    t = (char*)malloc(sizeof(char)*MAXLEN);
    strcpy1(s,t);
    printf("s = %s\n",s);
    printf("t = %s\n",t);
    free(t);
    return 0;
}

void strcpy1(char *s,char *t){
    while((*(t++) = *(s++)) != '\0'){
        ;
    }
}