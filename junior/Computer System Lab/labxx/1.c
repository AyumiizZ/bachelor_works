#include<stdio.h>

int func(int x){
    int mask = x >> 31 | 1;
    return x + (x >> 31 | 1);
}

int main()
{
    for(int i = -10; i <= 10; i++)
     printf("%d ",func(i));
}