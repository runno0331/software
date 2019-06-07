#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define SIZE 10
#define STEP 10

int count(char copy[SIZE][SIZE],int i,int j){
    int h,w;
    int num = 0;
    for(h=i-1;h<=i+1;h++){
        for(w=j-1;w<=j+1;w++){
            if(h == -1){
                h = SIZE - 1;
            }else if(h == SIZE){
                h = 0;
            }
            if(w == -1){
                w = SIZE - 1;
            }else if(w == SIZE){
                w = 0;
            }
            if(h!=i && w!=j && copy[h][w]=='*'){
                num++;
            }
        }
    }
    return num;
}

void check(char matrix[SIZE][SIZE],char copy[SIZE][SIZE],int i,int j){
    if(count(copy,i,j) <= 1){
        matrix[i][j] = ' ';
    }else if(count(copy,i,j) == 3){
        matrix[i][j] = '*';
    }else if(count(copy,i,j) >= 4){
        matrix[i][j] = ' ';
    }
}

int main(){
    char matrix[SIZE][SIZE],copy[SIZE][SIZE];
    int i,j,steps = 0;
    srand((unsigned)time(NULL));

    //matrixの初期化
    for(i=0;i<SIZE;i++){
        for(j=0;j<SIZE;j++){
            if(rand()%100 < 14){
                matrix[i][j] = '*';
            }else{
                matrix[i][j] = ' ';
            }
        }
    }

    while(steps<STEP){
        for(i=0;i<SIZE;i++){
            for(j=0;j<SIZE;j++){
                copy[i][j] = matrix[i][j];
            }
        }
        for(i=0;i<SIZE;i++){
            for(j=0;j<SIZE;j++){
                check(matrix,copy,i,j);
            }
        }
        system("clear");
        for(i=0;i<SIZE;i++){
            for(j=0;j<SIZE;j++){
                printf("%c",matrix[i][j]);
            }
            printf("\n");
        }
        steps++;
        usleep(3*100000);
    }
    return 0;
}

