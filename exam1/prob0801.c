#include <stdio.h>
#include <math.h>

void circle_merge(float x1,float y1,float x2,float y2){
    float d;
    d = 2-sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    if(d>-0.00001){
        printf("o\n");
    }else{
        printf("x\n");
    }
}
int main(){
    circle_merge(3.14979,8.51743,1.79500,8.59211);
    circle_merge(2.84021,5.41511,4.70665,4.66125);
    return 0;
}