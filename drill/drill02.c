#include <stdio.h>

int gcd(int a,int b){
    int r;
    if(b > a){
        r = a;
        a = b;
        b = r;
    }
    while((r = a%b) != 0){
        a = b;
        b = r;
    }
    return b;
}

int array[3] = {1496,34,374};

int main(){
    printf("%d\n",gcd(array[0],gcd(array[1],array[2])));
    return 0;
}