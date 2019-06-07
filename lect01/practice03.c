#include <stdio.h>
int main(){
    int a[8][2]={{850,1},{750,2},{2500,1},{2800,2},{630,2},{820,3},{1300,2},{510,1}};
    int i;
    int s = 0;
    for(i=0;i<=7;i++){
        s = s + a[i][0]*a[i][1];
        printf("%d,%d\n",a[i][0],a[i][1]);
    }
    s = s*1.08;
    s = s/3;
    printf("%d円です\n",s);
}