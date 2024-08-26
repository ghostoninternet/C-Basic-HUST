#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
      char *fileIn = argv[1];
      char *fileOut = argv[2];

      FILE *fIN;
      FILE *fOUT;

      if ((fIN = fopen(fileIn, "r")) == NULL)
      {
            printf("Can't open file %s.\n", fileIn);
            return 1;
      }
      if ((fOUT = fopen(fileOut, "w")) == NULL)
      {
            printf("Can't open file %s.\n", fileOut);
            return 1;
      }

      if (argc != 3)
      {
            printf("Please provide fileInput and fileOutput.\n");
            printf("PROGRAM <INPUT FILE> <OUTPUT FILE>.\n");
            return 1;
      }

      int c;
      while((c = getc(fIN)) != EOF)
      {
            putc(c, fOUT);
      }
      printf("Succesfully copy file %s to file %s.\n", fileIn, fileOut);
      fclose(fIN);
      fclose(fOUT);
      return 0;
}