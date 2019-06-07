#include <stdio.h>

int main(int argc,char* argv[]){
    int i;
    for(i=0;i<3;i++){
        //縦
        if(argv[1][i] == argv[1][i+3] && argv[1][i] == argv[1][i+6]){
            if(argv[1][i] == 'o'){
                printf("oの勝利\n");
                return 0;
            }else if(argv[1][i] == 'x'){
                printf("xの勝利\n");
                return 0;
            }
        }
        //横
        if(argv[1][i*3] == argv[1][i*3+1] && argv[1][i*3] == argv[1][i*3+2]){
            if(argv[1][i*3] == 'o'){
                printf("oの勝利\n");
                return 0;
            }else if(argv[1][i*3] == 'x'){
                printf("xの勝利\n");
                return 0;
            }
        }
    }
    //斜め
    if(argv[1][0] == argv[1][4] && argv[1][0] == argv[1][8]){
        if(argv[1][0] == 'o'){
            printf("oの勝利\n");
            return 0;
        }else if(argv[1][0] == 'x'){
            printf("xの勝利\n");
            return 0;
        }
    }
    if(argv[1][2] == argv[1][4] && argv[1][2] == argv[1][6]){
        if(argv[1][2] == 'o'){
            printf("oの勝利\n");
            return 0;
        }else if(argv[1][2] == 'x'){
            printf("xの勝利\n");
            return 0;
        }
    }
    printf("勝敗が決していません\n");
    return 0;
}