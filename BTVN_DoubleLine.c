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

      if ((fB = fopen(fileBegin, "r")) == NULL)
      {
            printf("Can't open file %s\n", fileBegin);
            return 1;
      }
      if ((fE = fopen(fileEnd, "w")) == NULL)
      {
            printf("Can't open and write to file %s\n", fileEnd);
            return 1;
      }

      int c;
      while ((c = getc(fB)) != EOF)
      {
            if (c == 10)
            {
                  putc(10, fE);
                  
            }
            else
            {
                  putc(c, fE);
            }
      }

      fclose(fB);
      fclose(fE);
      return 0;
}