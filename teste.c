#include <stdio.h>



int main(void){

int a = 1;
int *b;
b = &a;

printf("%d e %p\n", a, b);

*b = 3;

printf("%d e %p", a, b);


  return 0;
}