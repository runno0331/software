#include <stdio.h>

int main(){
    int i=1;
    long int t=1;
    for(i=1;i<=20;++i){
        t *= i;
        printf("%d! = %ld\n",i,t);
    }
    return 0;
}