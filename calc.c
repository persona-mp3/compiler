#include <stdio.h>
#include <stdlib.h>

int calculator() {
  double n1, n2;
  double total;
  printf("first number -> ");
  scanf("%lf", &n1);
  printf("second number -> ");
  scanf("%lf", &n2);

  total = n1 + n2;
  printf("total is -> %f\n", total);

  return 0;
}

int main() 
{ 
  calculator();
  return 0;
}

