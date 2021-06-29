#include<stdio.h>

int *x,*v, *u,*y,*z,b,a,c,d;
int p()
{

	if (a < b)
		y = x;
	else
		x = &a;	
	return 0;
}

int main(){
   x = &d;
   y = &c;
    p();

   return *x;
}

