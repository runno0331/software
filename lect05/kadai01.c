#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define SIZE 10

int main(){
    int i=0,x,y;
    char matrix[SIZE][SIZE];
    for(x=0;x<SIZE;x++){
            for(y=0;y<SIZE;y++){
                matrix[x][y] = ' ';
            }
    }
    while(i<SIZE){
        system("clear");
        matrix[i][i] = '*';
        for(x=0;x<SIZE;x++){
            for(y=0;y<SIZE;y++){
                printf("%c ",matrix[x][y]);
            }
            printf("\n");
        }
        i++;
        sleep(1);
    }
}