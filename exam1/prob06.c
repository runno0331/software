#include <stdio.h>
#include <math.h>

int main(){
    double a,b,c;
    double space,max = -1,min = 1000000,total = 0;
    char buf[1024];
    while(fgets(buf,sizeof(buf),stdin)){
        sscanf(buf,"%lf,%lf,%lf",&a,&b,&c);
        space = sqrt((a+b+c)*(-a+b+c)*(a-b+c)*(a+b-c))/4;
        if(space>max){
            max = space;
        }
        if(space<min){
            min = space;
        }
        total += space;
    }
    total /= 100000;
    printf("max = %lf\n",min);
    printf("mean = %lf\n",total);
    printf("max = %lf\n",max);
    return 0;
}