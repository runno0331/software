#include <stdio.h>
#include <stdlib.h>
#define NAMELEN 20
#define MAXLEN 1000

int main(){
    char fn[NAMELEN],first,second='\0';
    int i = 0;
    FILE *fp1,*fp2;
    printf("圧縮するファイル名を入力してください\n");
    scanf("%s",fn);
    if((fp1 = fopen(fn,"r"))==NULL){
        perror("ファイルが開けません");
        return EXIT_FAILURE;
    }
    fp2 = fopen("copy.txt","w");
    while((first=getc(fp1)) != EOF){
        if(first != second && second != '\0'){
            fprintf(fp2,"%c",second);
            if(i != 1){
                fprintf(fp2,"%d",i);
            }
            i = 0;
        }
        second = first;
        i++;
    }
    fprintf(fp2,"%c",second);
    if(i != 1){
        fprintf(fp2,"%d",i);
    }
    fclose(fp1);
    fclose(fp2);
    printf("圧縮が完了しました\n");
    return 0;
}