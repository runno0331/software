#include <stdio.h>
#include <math.h>

int main(){
    float pi = 3.14;
    int i;
    float delta = pi/100;
    float pi_x;
    for(i=0;i<=1000;i++){
        pi_x = -5*pi + delta*i;
        if(pi_x != 0){
            printf("%f %f\n",pi_x,sin(pi*pi_x)/pi*pi_x);
        }else{
            printf("%f %f\n",pi_x,1.0);
        }
    }
    printf("%f\n",sin(15.7)/15.7);
    return 0;
}