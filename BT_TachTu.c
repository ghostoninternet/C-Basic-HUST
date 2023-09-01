#include <stdio.h>
#include <string.h>
void printWord(char *sentence)
{
      for (int i = 0; i < strlen(sentence); i++)
      {
            if (sentence[i] != ' ')
            {
                  printf("%c", sentence[i]);
            }
            else if (sentence[i] == ' ')
            {
                  printf("\n");
            }
      }
}
int main()
{
      char sentence[100];
      gets(sentence);
      printWord(sentence);
      return 0;
}