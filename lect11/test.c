#include <stdio.h>
int add_one(int x)
{
 return x + 1;
}
int add_two(int x)
{
 return x + 2;
}
void apply(int v[], int n, int (*fp)(int))
{
 for (int i = 0; i < n; i++) {
 v[i] = (*fp)(v[i]);
 }
}

int main()
{
 int v[10];
 const int n = sizeof(v)/sizeof(int);
 for (int i = 0; i < n; i++) {
 v[i] = i;
 }
 apply(v, n, add_one);
 apply(v, n, add_two);
 for (int i = 0; i < n; i++) {
 printf("v[%d] = %d", i, v[i]);
 }
}