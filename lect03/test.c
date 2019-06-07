#include <stdlib.h>
#include <stdio.h>
int main(void)
{
  int i, seed;
  for (seed = 0; seed < 5; seed++) {
    srand(seed);
    printf("seed = %d\n", seed);
    /* 1～100の乱数を10個生成 */
    for (i=0; i<10; i++) {
      printf("%3d ",rand() % 100 + 1);
    }
    printf("\n");
  }
  for(i=0;i<10;i++){
      printf("%d\n",rand());
  }
  return 0;
}