#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define HINT 1

void find(char* hint,char* word,int* n,int *m){
    int i,j,l;
    int a[12] = {1,3,5,7,11,13,15,17,19,21,23,25};
    for(i=0;i<12;i++){
        for(j=0;j<26;j++){
            for(l=0;l<strlen(hint);l++){
                if(hint[i] != 'a'+((a[i]*word[i]-'a')+j)%26){
                    break;
                }
                if(l == strlen(hint)){
                    *n = i;
                    *m = j;
                }
            }
        }
    }
}

int main(int argc,char* argv[]){
    int i,j,*n,*m;
    n = (int*)malloc(sizeof(int));
    m = (int*)malloc(sizeof(int));
    int a[12] = {1,3,5,7,11,13,15,17,19,21,23,25};
    char* hint = "google";
    find(hint,argv[HINT],n,m);
    
    for(i=1;argc<=i;i++){
        for(j=0;j<strlen(argv[i]);j++){
            printf("%c",'a'+(a[*n]*(argv[i][j]-'a')+*m)%26);
        }
        printf("\n");
    }
    return 0;
}

