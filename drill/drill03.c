#include <stdio.h>
#include <stdlib.h>

int main(){
    int a,b,c,i = 0;
    while(i<10000){
        a = (rand()%100+1);
        b = (rand()%100+1);
        c = (rand()%100+1);
        if(a+b>c && b+c>a && c+a>b){
            printf("%d,%d,%d\n",a,b,c);
            i++;
        }
    }
    return 0;
}