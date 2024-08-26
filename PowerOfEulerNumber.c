#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define E 2.71828

int main(int argc, char * argv[])
{
      double power = atof(argv[1]);
      printf("Exponent of e to the power of %f is: %.5f", atof(argv[1]), pow(E, power));
      return 0;
}