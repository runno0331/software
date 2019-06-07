#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

int main(){
    int x,y;
    char c,matrix[SIZE][SIZE];
    for(x=0;x<SIZE;x++){
        for(y=0;y<SIZE;y++){
            matrix[x][y] = '-';
        }
    }
    while(scanf("%d %d %c",&x,&y,&c)!=EOF){
        if(0<=x && x<=SIZE-1 && 0<=y && y<=SIZE){
            matrix[x][y] = c;
            system("clear");
            for(x=0;x<SIZE;x++){
                for(y=0;y<SIZE;y++){
                    printf("%c ",matrix[x][y]);
                }
                printf("\n");
            }
        }else{
            printf("範囲外です\n");
        }
        while(getchar()!='\n'){
        }
    }
    return 0;
}