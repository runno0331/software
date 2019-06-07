#include <assert.h>

int euclid(int m, int n)
{
 assert(n > 0 && m >= n);
 int remainder = m % n;
 if (remainder == 0)
 return n;
 else
 return euclid(n, remainder);
}

int main()
{
 euclid(-5, -1);
 return 0;
}