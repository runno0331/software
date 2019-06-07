#include <stdio.h>
int main(){
    int i;
    char a[6] = "123456";
    char j;
    for(i=0;i<5;i++){
        j = a[i]*a[i+1];
        printf("%c\n",j);
        printf("%c*%c\n",a[i],a[i+1]);
    } 
    return 0;
}