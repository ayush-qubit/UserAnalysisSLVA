#include "stdio.h"
int *x,*y;
int a,b;
int c=6,d=6;
int *z=&c;
int *w=&d;

int main() {
    b=*w;
    while(c>0)
    {
    	if(c==4)
    	{
    		a=*z+c;
    	}
    	else
    	{
    		a=*x-*z;
    	}  
    }        
    x=&a;
    y=&b;
    return *x+*y;
}
