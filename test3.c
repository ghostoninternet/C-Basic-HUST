#include <stdio.h>
#include <stdlib.h>

void changeArray(int a[], int n)
{
      for(int i = 0; i < n; i++)
      {
            a[i] -= 1;
      }
}

int main()
{
      int a[10];
      for(int i = 0; i < 10; i++)
      {
            a[i] = i+1;
            printf("%d ", a[i]);
      }
      printf("\n");

      changeArray(a, 10);
      for(int i = 0; i < 10; i++)
      {
            printf("%d ", a[i]);
      }


}