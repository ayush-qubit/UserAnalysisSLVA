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

//0:{(e,c),(f,d),(g,?)}
int main()
{
	//fun1();
	fun3(3);
	return *f;
}
//0:(e,b),(f,c),(f,b),(g,d)
