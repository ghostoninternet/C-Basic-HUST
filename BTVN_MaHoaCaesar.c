#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
      if (argc != 4)
      {
            printf("Invalid syntax\n");
            printf("<PROGRAM> <FILE START> <OFFSET> <FILE END>\n");
            return 1;
      }


      int step = (int)atof(argv[2]);
      if (step == 0)
      {
            printf("Step must be larger or smaller than 0.\n");
            return 1;
      }

      char *fileStart = argv[1];
      char *fileEnd = argv[3];

      FILE *fS;
      FILE *fE;

      if ((fS = fopen(fileStart, "r")) == NULL)
      {
            printf("Can't open file %s.\n", fileStart);
            return 1;
      }
      if ((fE = fopen(fileEnd, "w")) == NULL)
      {
            printf("Can't open and write to file %s.\n", fileEnd);
            return 1;
      }

      int c;
      if (step > 0)
      {
            printf("Encrypting file %s...", fileStart);
            while ((c = getc(fS)) != EOF)
            {
                  putc(c+step, fE);
            }
      }
      else if (step < 0)
      {
            printf("Decryting file %s...", fileStart);
            while((c = getc(fS)) != EOF)
            {
                  putc(c + step, fE);
            }
      }
      fclose(fS);
      fclose(fE);
      return 0;
}