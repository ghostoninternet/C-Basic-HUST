#include <stdio.h>
enum
{
      SUCCESS,
      FAIL
};

void CharWriteToFile(FILE *fin, FILE *fout)
{
      int c;
      while ((c = fgetc(fin)) != EOF)
      {
            fputc(c, fout);
      }
}

int main()
{
      FILE *fptr1, *fptr2;
      char filename1[] = "lab1.txt";
      char filename2[] = "lab1a.txt";

      if ((fptr1 = fopen(filename1, "r")) == NULL)
      {
            printf("Can not open file %s.\n", filename1);
      }
      else if ((fptr2 = fopen(filename2, "w")) == NULL)
      {
            printf("Can not open file %s.\n", filename2);
      }
      else
      {
            CharWriteToFile(fptr1, fptr2);
            fclose(fptr1);
            fclose(fptr2);
      }
}