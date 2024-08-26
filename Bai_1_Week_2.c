#include <stdio.h>
#include <string.h>
#define MAX 50

int compareString(char *str1, char *str2)
{
      char ten1[10], ten2[10];
      int startPost;
      int endPost;
      for (int i = strlen(str1) - 1; i >= 0; i--)
      {
            if (str1[i] == ' ')
            {
                  startPost = i;
                  break;
            }
      }
      for (int i = startPost + 1; i < strlen(str1); i++)
      {
            ten1[i - startPost - 1] = str1[i];
            endPost = (i - startPost - 1) + 1;
      }
      ten1[endPost] = '\0';

      for (int i = strlen(str2) - 1; i >= 0; i--)
      {
            if (str2[i] == ' ')
            {
                  startPost = i;
                  break;
            }
      }
      for (int i = startPost + 1; i < strlen(str2); i++)
      {
            ten2[i - startPost - 1] = str2[i];
            endPost = (i - startPost - 1) + 1;
      }
      ten2[endPost] = '\0';
      

      return strcmp(ten1, ten2);
}

int main()
{
      char tempName[50];
      char DS[MAX][50];
      for (int i = 0; i < MAX; i++)
      {
            gets(DS[i]);
            fflush(stdin);
      }
      printf("\n");
      for (int i = 0; i < MAX - 1; i++)
      {
            for (int j = i; j < MAX; j++)
            {
                  if (compareString(DS[i], DS[j]) > 0)
                  {
                        strcpy(tempName, DS[i]);
                        strcpy(DS[i], DS[j]);
                        strcpy(DS[j], tempName);
                  }
            }
      }
      for (int i = 0; i < MAX; i++)
      {
            printf("%s\n", DS[i]);
      }
      return 0;
}
