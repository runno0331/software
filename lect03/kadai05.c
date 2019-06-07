#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define K 5
#define N 100000000

int bet(int k);

/*
初期段階を除いてコインを1工程100枚ごとにスロットに賭ける.どのスロットにどれくらいの割合でコインを賭けるかは
その工程開始時点における全当選金中のそのスロットから得られた当選金による．そのため、当選しやすいものほど多くの
掛け金がかけられることになる．実行結果はsum = 1.224628 でその他の実行結果も概ね1.22前後であった．
*/
int main(){
    srand((unsigned)time(NULL));
    int credit = N,reward = 0,sum = 0;
    int i,j,tem1,tem2;
    int slot[K][2];
    for(i=0;i<K;i++){
        slot[i][0] = 0; //スロットごとの当選金を記録
        slot[i][1] = 0; //スロットごとにそのスロットにかけた金額を記録
    }
//各スロットに100枚づつ賭ける
    for(i=0;i<K;i++){
        for(j=0;j<100;j++){
            if(credit-- > 0){
                reward = bet(i);
                sum += reward;
                slot[i][0] += reward;
                slot[i][1]++;
            }
        }
    }
//コインが0枚になるまで賭ける
    while(credit > 0){
        tem1 = sum; //開始段階における全当選金
        for(i=0;i<K;i++){
            tem2 = slot[i][0]; //開始段階におけるスロットの当選金
            for(j=0;j<round(100*(double)tem2/tem1);j++){
                if(credit-- > 0){
                    reward = bet(i);
                    sum += reward;
                    slot[i][0] += reward;
                    slot[i][1]++;
                }
            }
        }
    }
    printf("sum = %f\n",(double)sum/N);
    return 0;
}

int bet(int k){
    switch(k){
        case 0:
            if(rand() % 2 == 0){ // 2/2
                return 2;
            }else{
                return 0;
            }
            break;
        case 1:
            if(rand() % 7 == 0){ // 5/7
                return 5;
            }else{
                return 0;
            }
            break;
        case 2:
            if(rand() % 8 == 0){ // 10/8
                return 10;
            }else{
                return 0;
            }
            break;
        case 3:
            if(rand() % 40 == 0){ // 50/40
                return 50;
            }else{
                return 0;
            }
            break;
        case 4:
            if(rand() % 200 == 0){  // 100/200
                return 100;
            }else{
                return 0;
            }
            break;
        default:
            return 0;
    }
}