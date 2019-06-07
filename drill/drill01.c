#include <stdio.h>

int getmax(int numbers[],int N){
    int i,max;
    max = numbers[0];
    for(i=1;i<N;i++){
        if(numbers[i]>max){
            max = numbers[i];
        }
    }
    return max;
}

int numbers[] = {12,34,56,78,91};

int main(){
    int N = sizeof(numbers)/sizeof(numbers[0]);
    printf("max=%d\n",getmax(numbers,N));
    return 0;
}