#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
      if (argc != 2)
      {
            printf("Please provide a filename.\n");
            printf("PROGRAM <FILENAME>\n");
            return 1;
      }

      char *filename = argv[1];
      FILE *fIN;
      if ((fIN = fopen(filename, "r")) == NULL)
      {
            printf("Can't open file %s.\n", filename);
            return 1;
      }

      char tempFilename[50] = "Copy of Current File.txt";
      FILE *fTEMP;
      if ((fTEMP = fopen(tempFilename, "w")) == NULL)
      {
            printf("Can't open or write file %s.\n", tempFilename);
            return 1;
      }

      int c;
      while ((c = getc(fIN)) != EOF)
      {
            if (islower(c))
            {
                  c = toupper(c);
                  putc(c, fTEMP);
            }
            else
            {
                  putc(c, fTEMP);
            }
      }
      fclose(fIN);
      fclose(fTEMP);

      if ((fIN = fopen(filename, "w")) == NULL)
      {
            printf("Can't open or write file %s.\n", filename);
            return 1;
      }
      if ((fTEMP = fopen(tempFilename, "r")) == NULL)
      {
            printf("Can't open file %s.\n", tempFilename);
            return 1;
      }

      while ((c = getc(fTEMP)) != EOF)
      {
            putc(c, fIN);
      }
      fclose(fIN);
      fclose(fTEMP);

      return 0;
}