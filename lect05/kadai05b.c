#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define SIZE 50
#define STEP 50

void check(char[SIZE][SIZE],int,int);
int count(char[SIZE][SIZE],int,int);

int main(){
    int n,i,j;
    char matrix[SIZE][SIZE];
    srand((unsigned)time(NULL));
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            if(rand()%100 < 50){
                matrix[i][j] = '*';
            }else{
                matrix[i][j] = ' ';
            }
        }
    }
    for(n=0;n<STEP;n++){
        for(i=0;i<SIZE;i++){
            for(j=0;j<SIZE;j++){
                check(matrix,i,j);
            }
        }
        system("clear");
        for(i=0;i<SIZE;i++){
             for(j=0;j<SIZE;j++){
                 printf("%c",matrix[i][j]);
             }
             printf("\n");
        }
        usleep(2*100000);
    }
    return 0;
}

//生死の判断
void check(char matrix[SIZE][SIZE],int i,int j){
    if(count(matrix,i,j) <= 1){
        matrix[i][j] = ' ';
    }else if(count(matrix,i,j) == 3){
        matrix[i][j] = '*';
    }else if(count(matrix,i,j) >= 4){
        matrix[i][j] = ' ';
    }
    printf("%d",count(matrix,i,j));
}

//周囲の生きているセルのカウント
int count(char matrix[SIZE][SIZE],int i,int j){
    int h,w,num = 0;
    for(h=i-1;h<=i+1;h++){
        for(w=j-1;w<=j+1;w++){
            if(h!=i && w!=j){
                if(h>=0 && w>=0 && h<SIZE && w<SIZE && matrix[h][w]=='*'){
                    num++;
                }else if(h == -1 && matrix[SIZE-1][w]=='*'){
                    num++;
                }else if(w == -1 && matrix[h][SIZE-1]=='*'){
                    num++;
                }else if(h == SIZE && matrix[0][w]=='*'){
                    num++;
                }else if(w == SIZE && matrix[h][0]=='*'){
                    num++;
                }
            }
        }
    }
    return num;
}