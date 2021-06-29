#include<stdio.h>
int a,b,c,d;
int *p1=&a;
int *p2=&b;
int *p3=&c;
int *p4=&d;
int **p5=&p1;

int main()
{
	p1=&b;
	p2=p3;
	p4=*p5;
	*p5=p3; //p5 Union A{p5}
	return **p5;
}
