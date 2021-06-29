#include<stdio.h>

int c,d,g1,g2,a,b;
int *e=&c;
int *f=&d;
int *g;


//2:{(e,c),(f,c),(g,d)}
//3:{(e,c),(f,d),(g,d),(e,b),(f,c)}
void fun3(int k)
{
	f=e;
	e=&b;
}
//2:{(e,b),(f,c),(g,d)}
//3:{(e,b),(f,c),(g,d),(f,b)}


//1:{(e,c),(f,d),(g,?)}
void fun1()
{
	int *y;
	y=&c;
	g=&d;
	if(*g>1)
	{
		f=e; //a->b....a->x....
//(e,c),(f,c),(g,d)
		fun3(c);
//{(e,b),(f,c),(g,d)}	
	}
	else
	{
//{(e,c),(f,d),(g,d)}
		f=g;
//{(e,c),(f,d),(g,d)}
	}
}
//1:{(e,c),(f,d),(g,d),(e,b),(f,c)}

//0:{(e,c),(f,d),(g,?)}
int main()
{
	int *l,*m;
	l=&c;
	m=&d;
	fun1();
	fun3(3);
	return 0;
}
//0:(e,b),(f,c),(f,b),(g,d)
