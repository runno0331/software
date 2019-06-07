#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define SIZE 50
#define STEP 1000
#define DENSITY 50 //初期の密度

void check(char[SIZE][SIZE],char[SIZE][SIZE],int,int);
int count(char[SIZE][SIZE],int,int);

int main(){
    int n,i,j;
    char matrix[SIZE][SIZE],tem[SIZE][SIZE];//matrix及びcheck用の配列
    //matrixの初期化
    srand((unsigned)time(NULL));
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            if(rand()%100 < DENSITY){
                matrix[i][j] = '*';
            }else{
                matrix[i][j] = ' ';
            }
        }
    }

    //０段階目
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            printf("%c",matrix[i][j]);
        }
        printf("\n");
    }
    
    for(n=0;n<STEP;n++){
        for(i=0;i<SIZE;i++){
             for(j=0;j<SIZE;j++){
                 tem[i][j] = matrix[i][j];
             }
        }
        for(i=0;i<SIZE;i++){
            for(j=0;j<SIZE;j++){
                check(matrix,tem,i,j);
            }
        }
        system("clear");
        for(i=0;i<SIZE;i++){
             for(j=0;j<SIZE;j++){
                 printf("%c",matrix[i][j]);
             }
             printf("\n");
        }
        usleep(100000);
    }
    return 0;
}

//生死の判断
void check(char matrix[SIZE][SIZE],char tem[SIZE][SIZE],int i,int j){
    if(tem[i][j] == ' '){
        if(count(tem,i,j) == 3){
            matrix[i][j] = '*';
        }
    }else if(tem[i][j] == '*'){
        if(count(tem,i,j) <= 1 || count(tem,i,j) >= 4){
            matrix[i][j] = ' ';
        }
    }
}

//周囲の生きているセルのカウント
int count(char tem[SIZE][SIZE],int i,int j){
    int h,w,num = 0;
    for(h=i-1;h<i+2;h++){
        for(w=j-1;w<j+2;w++){
            if(h!=i || w!=j){
                if(h>=0 && w>=0 && h<SIZE && w<SIZE && tem[h][w]=='*'){
                    num++;
                }else if(h == -1 && w == -1 && tem[SIZE-1][SIZE-1] == '*'){
                    num++;
                }else if(h == -1 && w == SIZE && tem[SIZE-1][0] == '*'){
                    num++;
                }else if(h == SIZE && w == -1 && tem[0][SIZE-1] == '*'){
                    num++;
                }else if(h == SIZE && w == SIZE && tem[0][0] == '*'){
                    num++;
                }else if(h == -1 && tem[SIZE-1][w] == '*'){
                    num++;
                }else if(h == SIZE && tem[0][w] == '*'){
                    num++;
                }else if(w == -1 && tem[h][SIZE-1] == '*'){
                    num++;
                }else if(w == SIZE && tem[h][0] == '*'){
                    num++;
                }
                    
            }
        }
    }
    return num;
}