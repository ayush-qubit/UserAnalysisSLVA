#include "stdio.h"
int *x,*y;
int a,b;
int c=6,d=6;
int *z=&c;
int *w=&d;

int main() 
{
    a=c+d;
	b=c-d;
    a=*z+1;
    b=b+1;
    return *x+*y;
}