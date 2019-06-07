#include <stdio.h>

long int gcd(long int a,long int b){
    long int r;
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

long int array[3] = {5142121089, 50202019, 1298080777};

int main(){
    printf("%ld\n",gcd(array[0],gcd(array[1],array[2])));
    return 0;
}
