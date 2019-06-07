#include <stdio.h>
#include <stdlib.h>
#define NUMALPHA 26

int main(){
    char *str;
    int i;
    str = (char*)malloc(sizeof(char)*NUMALPHA);
    for(i=0;i<NUMALPHA;i++){
        *(str+i) = i+'A';
    }
    *(str+i) = '\0';
    printf("Alphabet: %s\n",str);
    free(str);
    return 0;
}