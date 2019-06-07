#include <stdio.h>

// func3: S(N, m)を最大にするようなmを返す関数
// func3は返り値がintであることに注意せよ。
int func3(int N)
{
    int sum = 0,max = 0,n = N,m,d;
    for(d=2;d<=10;d++){
        while(n!=0){
            sum += n%d;
            n = n/d;
        }
        if(sum>max){
            max = sum;
            m = d;
        }
        sum = 0;
        n = N;
    }
    return m;
}

/* ここから下を編集しないこと */
#define INPUT_NUM 3
int inputs[INPUT_NUM] = {35, 732043, 991326};

int main(void)
{
    int i;
    for (i = 0; i < INPUT_NUM; i++) {
        /* func3はS(N, m)を最大にするようなmを返すこと。 */
        printf("%d\n", func3(inputs[i]));
    }
    return 0;
}