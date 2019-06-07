#include <stdio.h>
#include <string.h>

#define MAXLEN 1000

int check_kaibun(char[]);

int main(){
    int i = 0;
    char c;
    char str[MAXLEN];
    while((c = getchar()) != '\n' && i < MAXLEN){
        str[i++] = c;
    }
    if(check_kaibun(str)){
        printf("%s is palindrome.\n",str);
    }else{
        printf("%s is NOT palindrome.\n",str);
    }
    return 0;
}

int check_kaibun(char str[]){
    int l = strlen(str);
    int i;
    for(i=0;i<=l/2;++i){
        if(str[i] != str[l-i-1]){
            return 0;
        }
    }
    return 1;
}