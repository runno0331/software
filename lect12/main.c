#include <stdio.h>
void foo(void);
int x;

int main()
{
  x = 0;

  foo();

  printf("%d\n",x);
}