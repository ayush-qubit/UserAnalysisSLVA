#include<stdio.h>

int *x,*v, *u,*y,*z,b,a,c,d;
int p()
{

	if (a < b)
	{	
		x = &a;
		y = x;
	}
	else
	{
	}		
	return 0;
}

int main(){
   x = &d;
   y = &c;
    p();

   return *x;
}

