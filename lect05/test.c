#include <stdio.h>
#include <stdlib.h>
void func1(int *input);
void func2(int input);
int main(void)
{
  int a=100;

  int *b;
  b = (int *) malloc(sizeof(int));
  *b = 200;
  
  func1(&a); // a? *a? &a? どう書くべき？
  func1(b); // b? *b? &b? どう書くべき？
  func2(a); // a? *a? &a? どう書くべき？
  func2(*b); // b? *b? &b? どう書くべき？
  
  return 0;
}

void func1(int *input)
{
  printf("%d\n", *input);
}

void func2(int input)
{
  printf("%d\n", input);
}

