#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define K 5
#define N 10000000

int bet(int k);

int main(){
    srand((unsigned)time(NULL));
    int credit = N,reward = 0,sum = 0,play = 1,loop_n = 1;
    int i,j,check;
    int in = 100;
    int slot_reward[K];
    double rate;
    for(i=0;i<K;i++){
        slot_reward[i] = 0;
    }
    while(credit > 0){
        check = loop_n;
        for(i=0;i<K;i++){
            if(play==1 || ((double)slot_reward[i]/(double)play)>((double)sum/(double)loop_n)){
                for(j=0;j<in;j++){
                    if(credit-- > 0){
                        reward = bet(i);
                        slot_reward[i] += reward;
                        sum += reward;
                        loop_n++;
                    }
                }
            }
            //printf("%f %f\n",(double)slot_reward[i]/(double)play*100),((double)sum/(double)loop_n*100)));
        }
        play++;
        if(loop_n == check){
            break;
        }
    }
    printf("sum = %f\n",(double)sum/N);
    printf("sum = %d\n",loop_n);
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
            if(rand() % 40 == 0){ // 50/4０
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