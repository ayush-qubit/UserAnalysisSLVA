#include<stdio.h>

int *x, *y, *z, c;

void fun()
{
int *a, b;
a = &b;
a = x;
y = a;
}
int main()
{
	fun();
	return *y;
}


/*int *x, *y, *z, u, v;

void func(int *a, int * b)
{
int *c, *d, e, f;
c = &e;
d = &f;

if ( e == 1)
	a = c;
else
	a = d;

z = a;

}

int main()
{
u = 50; v = 30;

x = &u;
y = &v;

func(x, y);
}

*/

//int **v,*x,*y,*w,*z, a,b,c,d;

/*int fun()
{
x = *v;

return 0;
}
int main(){
    v = &y;
    x = &b;
    y = &c;
  //  w = &d;

   fun();
    return *x;
}*/

/*int fun()
{
*v = y;
return 0;
}

int main(){
v = &x;
    y = &c; 

    fun();
    return *x;
}



*/












/*int **x,*v, *u,*y,*z,b,a,c,d;
int p()
{

	if (a < b)
		x = &z;
	else
	{ }	
	return 0;
}

int main(){
   x = &y;
    p();

   *x = &b;   
return 0;
}
*/
