#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

int main(){
    int x=0,y=0;
    char c,matrix[SIZE][SIZE];
    FILE *fp;
    if((fp = fopen("data.txt","r"))==NULL){
        for(x=0;x<SIZE;x++){
            for(y=0;y<SIZE;y++){
                matrix[x][y] = '-';
            }
        }
    }else{
        while((c=fgetc(fp))!=EOF){
            if(c != ' ' && c != '\n'){
                matrix[x][y] = c;
                y++;
            }else if(c == '\n'){
                y = 0;
                x++;
            }
        }
    }
    fclose(fp);
    while(scanf("%d %d %c",&x,&y,&c)!=EOF){
        matrix[x][y] = c;
        fp = fopen("data.txt","w");
        system("clear");
        for(x=0;x<SIZE;x++){
            for(y=0;y<SIZE;y++){
                printf("%c ",matrix[x][y]);
                fprintf(fp,"%C ",matrix[x][y]);
            }
            printf("\n");
            fprintf(fp,"\n");
        }
        fclose(fp);
        while(getchar()!='\n'){
        }
    }
    return 0;
}