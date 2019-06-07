#include <stdio.h>
#include <math.h>

int main()
{   
    int numbers[3];
    scanf("%d %d %d",numbers,numbers+1, numbers+2);
    printf("%d %d %d",*numbers,*numbers+1,*numbers+2);
}