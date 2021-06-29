#include<stdio.h>
int a,b,c,d;
int *p1=&a;
int *p2=&b;
int *p3=&c;
int *p4=&d;
int **p5=&p1;

int main()
{
	int x,y;
	int *l1=&x;
	int *l2=&y;
	l2=p2;
	l1=l2;
	l1=p1;
}
/*
We cannot code flow-functions in form of Refn, Defn, Killn because consider the statement *x=&a, this statement is decomposed into a number of load and store statements in LLVM IR. In our computeOutFromIn(), we only check single IR instruction, so its not possible to differentiate whether the IR instruction is a part of 
*x=y or x=y. So its not possible to identify the corresponding pointer statement and cannot code computeOutFromIn() in form of Refn, Defn.*/  