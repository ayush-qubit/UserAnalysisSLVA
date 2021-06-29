#include<stdio.h>

int c,d,g1,g2,a,b;
int *e=&c;
int *f=&d;
int *g;
int **q;


void fun3(int k)
{
	f=e;
	e=&b;
}

void fun1()
{
	int *y;
	int **z;
	z=&y;
	int **x;
	int k,l;
	y=&c;
	g=&d;
	x=z;
    //z=f;
	if(*g>1)
	{
		//z=y;
		f=e; 
		fun3(c);

	}
	else
	{
		*x=&a;
		f=g;
        printf("%d",**z);
	}
}

int main()
{
	int *l,*m;
	l=&c;
	m=&d;
	q=&e;
	fun1();
	fun3(3);
	return 0;
}

/*
Mem2reg : Removes all local-local interactions, and takes care of transitive dependencies betweem locals and globals. Confirmed with Rasesh.
Ex : Variable x in our code. Also variable z.
*/