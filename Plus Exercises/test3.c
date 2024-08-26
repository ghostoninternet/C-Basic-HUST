#include <stdio.h>

void f(int n)
{
      if(n > 0) f(--n);
      printf("%d ", n);
}

int main()
{
      f(4);
      return 0;
}