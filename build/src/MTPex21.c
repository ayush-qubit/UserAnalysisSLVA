#include<stdio.h>

int c,d,g1,g2,a,b;
int *e=&c;
int *f=&d;
int *g;

//1:{e}, 2:{phi}
void fun3(int k)
{
	f=e;
	e=&b;
}
//1:{f}, 2:{e}

int main()
{
	//fun1();
    // 0 : {phi}	
    fun3(3);
	// 0 : {e}	------> e --> b
    fun3(3);
	// 0 : {f} --------> f --> b
    return *f;
}
