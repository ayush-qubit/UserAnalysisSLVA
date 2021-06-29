#include<stdio.h>
int x,y,z;
int *p,*q,*r,*s;

//global->global
*p=&x;
*q=&y;

//(p,x),(q,y),(r,?) 
void fun()
{
	int t;//local
	p=&y;
	r=&t;
	//(p,y),(q,y),(r,t) 
}
//(p,y),(q,y),(r,?)


//(p,x),(q,y)
//(r,?) should be here.
int main()
{
	int a,b;
	int *e,*f,*g;
	
	e=&a;//local->local
	f=&b;//local->local
	
	g=&z;//local->global
	
	r=&a;//global->local

	//(p,x),(q,y),(e,a),(f,b),(g,z),(r,a) 

	// Purely global: (p,x),(q,y) 
	// Purely Local: (e,a),(f,b) 
	// Mixed : (g,z),(r,a) 
	
	fun();//IN:

	//Obtained from callee:
	//(p,y), Changed/Updated
	//(q,y), No change
	//(r,?) undefined

	//Propagated from IN(line no 39)
	//(e,a),(f,b) , purely Local 

	//Propagated from IN(line no 39)
	//(g,z), Mixed Local

//(p,y),(q,y),(r,?),(e,a),(f,b),(g,z)
	e=&a;
//(p,y),(q,y),(r,?),(e,a),(f,b),(g,z)
	f=e;
//(p,y),(q,y),(r,?),(e,a),(f,a),(g,z)
	e=&x;
//(p,y),(q,y),(r,?),(e,x),(f,a),(g,z)
	f=e;
//(p,y),(q,y),(r,?),(e,x),(f,x),(g,z)
	r=f;
//(p,y),(q,y),(r,x),(e,x),(f,x),(g,z)
	s=&a;
	r=s;
}