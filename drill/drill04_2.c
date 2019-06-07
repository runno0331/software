#include <stdio.h>

int main(){
    int a,b,c,i = 0,num = 0;
    char buf[1024];
    while(fgets(buf,sizeof(buf),stdin)){
        sscanf(buf,"%d,%d,%d",&a,&b,&c);
        if(a*a + b*b == c*c || a*a + c*c == b*c || b*b + c*c == a*a){
            num++;
        }
    }
    printf("number of right triangle = %d\n",num);
    return 0;
}