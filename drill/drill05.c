#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
    int i,j,num = 0;
    int *n,*result;
    n = (int*)malloc(sizeof(int)*1001);
    for(i=0;i<1001;i++){
        n[i] = 1;
    }
    for(i=2;i<sqrt(1000);i++){
        if(n[i] == 1){
            num++;
            for(j=i*2;j<1000;j+=i){
                n[j] = 0;
            }
        }
    }
    j = 0;
    result = (int*)malloc(sizeof(int)*num);
    for(i=2;i<1000;i++){
        if(n[i] == 1){
            printf("%d ",i);
            result[j] = i;
            j++;
        }
    }
    free(n);
    printf("\n");
    return 0;
}