#include "stdio.h"
int *x,*y;
int a,b;
int c=6,d=6;
int *z=&c;
int *w=&d;

void func()
{
  z=&a;
  return;
}

int main() {
    a=c+d;
    b=c-d;
    func();
    a=*z+1;
    b=*w+1;
    x=&a;
    y=&b;
    return *x+*y;
}
