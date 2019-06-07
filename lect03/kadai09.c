#include <stdio.h> 
#include <math.h>
#define NALPHA 26

int main() { 
  int count[NALPHA];
  int c,i; 
  int sum = 0;
  double prob,entropy;
  for(i=0;i<NALPHA;i++){
    count[i] = 0; 
  } 
  while((c=getchar())!=EOF){ 
    if('a'<=c && 'z'>= c) {
      count[c-'a']++;
      sum++;
    } 
  } 
  entropy = 0;
  for(i=0;i<NALPHA;i++){
      prob = (double)count[i]/(double)sum;
      entropy += prob*(-log2(prob));
  }
  printf("entropy = %e\n",entropy);
  return 0;
}