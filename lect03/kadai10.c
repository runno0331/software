#include <stdio.h>
#include <math.h>
#define NALPHA 26

int main(){
    int count[NALPHA][NALPHA];
    int c,i,j,sum;
    int first,second;
    double prob;
    double entropy[NALPHA];
    for(i=0;i<NALPHA;i++){
        for(j=0;j<NALPHA;j++){
            count[i][j] = 0;
        }
    }
    second = ' ';
    while((c=getchar())!=EOF){
        first = second;
        second = c;
        if(first >= 'a' && first <= 'z' && second >= 'a' && second <= 'z'){
            count[first-'a'][second-'a']++;
        }
    }
    for(i=0;i<NALPHA;i++){
        entropy[i] = 0;
    }
    for(i=0;i<NALPHA;i++){
        sum = 0;
        for(j=0;j<NALPHA;j++){
            sum += count[i][j];
        }
        for(j=0;j<NALPHA;j++){
            if(count[i][j]!=0){
            prob = (double)count[i][j]/(double)sum;
            entropy[i] += prob*(-log2(prob));
            }
        }
    }
    for(i=0;i<NALPHA;i++){
        printf("[%c]:ent = %e\n",'a'+i,entropy[i]);
    }
    return 0;
}