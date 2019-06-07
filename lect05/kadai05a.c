#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define SIZE 50
#define STEP 1

void check(char[SIZE][SIZE],char[SIZE][SIZE],int,int);
int count(char[SIZE][SIZE],int,int);

int main(){
    int n,i,j;
    char matrix1[SIZE][SIZE],matrix2[SIZE][SIZE];
    srand((unsigned)time(NULL));
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            if(rand()%100 < 13){
                matrix1[i][j] = '*';
            }else{
                matrix1[i][j] = ' ';
            }
        }
    }
    for(n=0;n<STEP;n++){
        for(i=0;i<SIZE;i++){
            for(j=0;j<SIZE;j++){
                check(matrix1,matrix2,i,j);
            }
        }
        system("clear");
        for(i=0;i<SIZE;i++){
             for(j=0;j<SIZE;j++){
                 printf("%c",matrix2[i][j]);
             }
             printf("\n");
        }
        usleep(2*100000);
        for(i=0;i<SIZE;i++){
            for(j=0;j<SIZE;j++){
                check(matrix2,matrix1,i,j);
            }
        }
        system("clear");
        for(i=0;i<SIZE;i++){
             for(j=0;j<SIZE;j++){
                 printf("%c",matrix1[i][j]);
             }
             printf("\n");
        }
        usleep(2*100000);
    }
    return 0;
}

//生死の判断
void check(char matrix1[SIZE][SIZE],char matrix2[SIZE][SIZE],int i,int j){
    if(matrix1[i][j] == ' '){
        if(count(matrix1,i,j) == 3 || count(matrix1,i,j) == 2){
            matrix2[i][j] = '*';
        }
    }else if(matrix1[i][j] == '*'){
        if(count(matrix1,i,j) <= 1 || count(matrix1,i,j) >= 4){
            matrix2[i][j] = ' ';
        }
    }
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