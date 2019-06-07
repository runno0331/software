#include <stdio.h>
#include <stdlib.h>

int main(){
    int c,i,r;
    int strength =80;
    while(1){
        c = getchar();
        if(c >= 'A' && c <= 'Z'){
            c = c - 'A' + 'a';
        }
        if(c=='q'){
            printf("終了します\n");
            break;
        }
        r = rand()%100;
        if(c=='g'){
            if(r < strength){
                printf("あなたはグーを出しました。私はチョキを出しました。あなたの勝ち！\n");
            }else{
                printf("あなたはグーを出しました。私はパーを出しました。あなたの負け！\n");
            }
        }else if(c=='c'){
            if(r < strength){
                printf("あなたはチョキを出しました。私はパーを出しました。あなたの勝ち！\n");
            }else{
                printf("あなたはチョキを出しました。私はグーを出しました。あなたの負け！\n");
            }
        }else if(c=='p'){
            if(r < strength){
                printf("あなたはパーを出しました。私はグーを出しました。あなたの勝ち！\n");
            }else{
                printf("あなたはパーを出しました。私はチョキを出しました。あなたの負け！\n");
            }
        }
    }
    return 0;
}