#include <stdio.h>

#define IN 1
#define OUT 0
#define MAXLEN 25
#define MAXNWORD 23000

int get_max(int[],int);
double get_average(int[],int);
double get_variance(int[],int);

int main(){
    int c,nl,nw,nc,state;
    int i,j;
    int word_initial,word_final,len;
    int word_length[MAXLEN];
    int numbers[MAXNWORD];
    for(i=0;i<MAXLEN;++i){
        word_length[i] = 0;
    }
    for(j=0;j<MAXNWORD;++j){
        numbers[j] = 0;
    }

    state = OUT;
    nl = nw = nc = 0;
    while((c=getchar()) != EOF){
        ++nc;
        if(c==' ' || c=='\n' || c=='\t'){
            if(state == IN){
                word_final =nc;
                len = word_final - word_initial;
                ++word_length[len];
                numbers[nw] = (nl+1)*len;
                ++nw;
            }
            state = OUT;
        }
        else if(state == OUT){
            state = IN;
            word_initial = nc;
        }
        if(c=='\n'){
            ++nl;
        }
    }
    printf("#line = %d #word = %d #character = %d\n",nl,nw,nc);
    printf("max = %d, avg = %.3f, var = %.3f\n",get_max(numbers,nw),get_average(numbers,nw),get_variance(numbers,nw));
    return 0;
}

//配列内の最大値
int get_max(int array[],int N){
    int i,max;
    max = 0;
    for(i=0;i<N;++i){
        if(array[i] > max){
            max = array[i];
        }
    }
    return max;
}

//配列内の値の平均値
double get_average(int array[],int N){
    int i;
    double ave;
    ave = 0;
    for(i=0;i<N;++i){
        ave += array[i];
    }
    ave /= N;
    return ave;
}

//配列内の値の分散
double get_variance(int array[],int N){
    int i;
    double ave,var;
    ave = get_average(array,N);
    var = 0;
    for(i=0;i<N;++i){
        var += (array[i] - ave)*(array[i] - ave);
    }
    var /= N;
    return var;
}