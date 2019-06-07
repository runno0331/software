#include <stdio.h>
#include <math.h>

int is_prime(int i){
    int j;
    for(j=2;j<=sqrt(i);j++){
        if(i%j==0){
            return 0;
        }
    }
    return 1;
}

int main(){
    int i,j,l = 0,n = 0,index = 0,k = 0,prime_list[500000];
    long int m;
    for(i=2;i<=10;i++){
        if(is_prime(i)){
            prime_list[index] = i;
            l += log10(i)+1;
            index++;
        }
    }
    printf("number of prime = %d,total = %d\n",index,l);
    for(i=0;i<index;i++){
        for(j=i;j<index;j++){
            m = (long int)prime_list[i]*(long int)prime_list[j];
            if(m <=1000000){
                n++;
                k += log10(m)+1;
            }
        }
    }
    printf("number of half prime = %d,total = %d\n",n,k);
    return 0;
}