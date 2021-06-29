#include<stdio.h>
int c,d,g1,g2;
int *e=&c;
int *f=&d;
//(e,c),(f,d)
void func()
{
	e=&g1;
	f=&g2;
}
//(e,g1),(f,g2)

//(e,c),(f,d)
int main()
{
	func();
	int a,b;
	int *x,*y;
	x=e;
	y=&b;
	return 0;
}
//(e,g1),(f,g2),(x,g1)

