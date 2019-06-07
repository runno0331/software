#include <stdio.h>
#include <stdlib.h>

int check(char*);

int main(){
    char *board;
    int line,row,i;
    board = (char*)malloc(sizeof(char)*9);
    for(i=0;i<9;i++){
        board[i] = '-';
    }
    for(i=0;i<9;i++){
        printf("%c ",board[i]);
        if(i%3 == 2){
            printf("\n");
        }
    }
    printf("あなたはoです\n");
    printf("先手なら0,後手なら1を入力してください\n");
    scanf("%d",&i);
    if(i){
        printf("コンピュータの手番です\n");
        line = rand()%3;
        row = rand()%3;
        board[row+line*3] = 'x';
        for(i=0;i<9;i++){
            printf("%c ",board[i]);
            if(i%3 == 2){
                printf("\n");
            }
        }
    }
    printf("あなたの手番です.行番号と列番号を入力してください\n");
    while(scanf("%d %d",&line,&row) != EOF){
        if(line<0 || line>2 || row<0 || row>2){
            printf("範囲外\n");
        }else if(board[row+line*3] != '-'){
            printf("すでに置かれています\n");
        }else{
            board[row+line*3] = 'o';
            for(i=0;i<9;i++){
                printf("%c ",board[i]);
                if(i%3 == 2){
                    printf("\n");
                }
            }
            printf("\n");
            if(check(board) == 0){
                return 0;
            }
            printf("コンピュータの手番です\n");
            while(board[row+line*3] != '-'){
                line = rand()%3;
                row = rand()%3;
            }
            board[row+line*3] = 'x';
            for(i=0;i<9;i++){
                printf("%c ",board[i]);
                if(i%3 == 2){
                    printf("\n");
                }
            }
            if(check(board) == 0){
                return 0;
            }
            printf("\n");
            printf("あなたの手番です.行番号と列番号を入力してください\n");
        }
    }
}

int check(char* board){
    int i;
    for(i=0;i<3;i++){
        //縦
        if(board[i] == board[i+3] && board[i] == board[i+6]){
            if(board[i] == 'o'){
                printf("oの勝利\n");
                return 0;
            }else if(board[i] == 'x'){
                printf("xの勝利\n");
                return 0;
            }
        }
        //横
        if(board[i*3] == board[i*3+1] && board[i*3] == board[i*3+2]){
            if(board[i*3] == 'o'){
                printf("oの勝利\n");
                return 0;
            }else if(board[i*3] == 'x'){
                printf("xの勝利\n");
                return 0;
            }
        }
    }
    //斜め
    if(board[0] == board[4] && board[0] == board[8]){
        if(board[0] == 'o'){
            printf("oの勝利\n");
            return 0;
        }else if(board[0] == 'x'){
            printf("xの勝利\n");
            return 0;
        }
    }
    if(board[2] == board[4] && board[2] == board[6]){
        if(board[2] == 'o'){
            printf("oの勝利\n");
            return 0;
        }else if(board[2] == 'x'){
            printf("xの勝利\n");
            return 0;
        }
    }
    for(i=0;i<9;i++){
        if(board[i] == '-'){
            return 1;
        }
    }
    printf("引き分け\n");
    return 0;
}