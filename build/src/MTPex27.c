#include<stdio.h>

int *x,*v, *u,*y,*z,b,a,c,d;
int p()
{
	v =x;
	u = v;
	x = u; //PointsTo Map -- Alias * --- Alais *
	return 0;
}
// Wrapper function ---> Compatible Data Structures. //UID--- Comparation
int main(){
   u = &d;
   v = &c;
    p();

   return *x;
}
/*
int p()
{

	if (a < b)
	{	
		y = x;
		x = &a;
	}
	else
	{
	}		
	return 0;
}

int main(){
   u = &d;
   v = &c;
    p();

   return *x;
}

*/
