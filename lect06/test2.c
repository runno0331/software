#include <stdio.h>

// func2: 自然数Nをn進法に変換して表示する関数
void func2(int N, int n)
{
    int i=0,m=0,num[40];
    while(N!=0){
        num[i] = N%n;
        N=N/n;
        m++;
        i++;
    }
    for(i=m-1;i>=0;i--){
        if(num[i] <= 9){
            printf("%d",num[i]);
        }else{
            printf("%c",'a'+num[i]-10);
        }
    }
    printf("\n");
}

/* ここから下を編集しないこと */
#define INPUT_NUM 7
int inputs[INPUT_NUM] = {91328, 35516, 619820, 317138, 981536, 568102, 1048575};
int bases[INPUT_NUM] = {3, 7, 9, 11, 12, 15, 16};

int main(void)
{
    int i;
    for (i = 0; i < INPUT_NUM; i++) {
        /* func2の中で答えの表示を行うこと */
        func2(inputs[i], bases[i]);
    }
    return 0;
}