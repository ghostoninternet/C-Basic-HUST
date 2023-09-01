#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
      if (argc != 3)
      {
            printf("Invalid command!\n");
            printf("Correct Syntax: PROGRAM <FILE 1> <FILE 2>.\n");
            return 1;
      }

      char *fileBegin = argv[1];
      char *fileEnd = argv[2];

      FILE *fB;
      FILE *fE;

      if ((fB = fopen(fileBegin, "a")) == NULL)
      {
            printf("Can't open and write to file %s\n", fileBegin);
            return 1;
      }
      if ((fE = fopen(fileEnd, "r")) == NULL)
      {
            printf("Can't open file %s\n", fileEnd);
            return 1;
      }

      int c;
      putc(10, fB);
      while ((c = getc(fE)) != EOF)
      {
            putc(c, fB);
      }

      fclose(fB);
      fclose(fE);
      return 0;
}