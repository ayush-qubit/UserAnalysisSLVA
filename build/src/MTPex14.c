#include<stdio.h>
int c=6,d=6,a,b;
int *z=&c;
int *w=&d;
int *e=&a;
int *f=&b;


//(z,c),(w,d),(e,a),(f,b) 
void func1()
{
    z=&d;
    w=&c;  
}
//(z,d),(w,c),(e,a),(f,b) 

//(z,d),(w,c),(e,a),(f,b)
void func2()
{
    e=z;
    f=w;
}
//(z,d),(w,c),(e,d),(f,c)


//(z,c),(w,d),(e,a),(f,b)
int main() 
{
    func1();
    func2();
    return 0;
}
//(z,d),(w,c),(e,d),(f,c)