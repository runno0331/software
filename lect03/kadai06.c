#include <stdio.h> 
#define NALPHA 26

int main() { 
  int count[NALPHA]; 
  int c,i; 
  for(i=0;i<NALPHA;i++){
    count[i] = 0; 
  } 
  while((c=getchar())!=EOF){ 
    if('a'<=c && 'z'>= c) {
      count[c-'a']++;
    } 
  } 
  for(i=0;i<NALPHA;i++){ 
    printf("%c : %d\n",'a'+i,count[i]);  
  }
  return 0;
}