#include<stdio.h>


int **v,*x,*y,b,a,c,d;
int p()
{
	*v = y;
	return 0;
}

int main(){
    v = &x;
    x = &a;
    y = &b;

    p();
    return *x;
}
