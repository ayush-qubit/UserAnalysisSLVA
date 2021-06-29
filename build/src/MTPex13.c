#include<stdio.h>
int *b,*c;
int x;
int *a=&x;

int main() {
    int *x,*y,*z;
    return 0;
}
/*
Killn(I),Refn(I),Pointeen(I) ------> 
Multiple IR instructions are required to figure out type of statements in Source language(C).
So cannot model them using single IR statement, requires a sequence of IR statements. 

Also we initailise the pointers with ? now.
*/
 