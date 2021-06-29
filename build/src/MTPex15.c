#include "stdio.h"
int *x,*y;
int a,b;
int c=6,d=6;
int *z=&c;
int *w=&d;

int func(int p)
{
    z=&d;
    w=&c;
    return b;   
}

int main() {
    a=1;
    b=2;
    b=func(6);
    x=&a;
    y=&b;
    return *x+*y;
}
