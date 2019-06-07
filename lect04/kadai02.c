#include <stdio.h>
#include <stdlib.h>

int main(){
    int *p;
    p = (int*)malloc(sizeof(int)*1);
    *p = 100;
    printf("*p = %d\n",*p);//ポインタ変数pが指すアドレスに格納されている値（100）を出力
    printf("p = %p\n",p);//ポインタ変数pの値、すなわち値100のアドレスを出力
    printf("&p = %p\n",&p);//ポインタ変数pのアドレスを出力
    free(p);
    return 0;
}