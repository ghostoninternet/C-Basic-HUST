#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 256

int main()
{
      char a[MAX_LENGTH];
      gets(a);
      int num_space = 1;

      FILE * middleFile = fopen("middleFile.txt", "w");
      for(int i = 0; i < strlen(a); i++)
      {
            if(a[i] == 32)
            {
                  fputc(10, middleFile);
                  num_space++;
            }
            else
            {
                  fputc(a[i], middleFile);
            }
      }
      fclose(middleFile);

      middleFile = fopen("middleFile.txt", "r");
      char b[num_space][MAX_LENGTH];
      int index = 0;
      while(feof(middleFile) == 0)
      {
            fscanf(middleFile, "%s", b[index]);
            fgetc(middleFile);
            printf("%s\n", b[index]);
            index++;
      }
      fclose(middleFile);

      return 0;
}