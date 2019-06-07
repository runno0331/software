#include <stdio.h>

int main(){
    int i;
    for(i=1;i<=1000;i++){
        printf("%d",i);
        if(i%3 == 0 || i%10 == 3 || i%100/10 == 3 || i/100 == 3){
            printf("!!!");
        }
        printf("\n");
    }
    return 0;
}