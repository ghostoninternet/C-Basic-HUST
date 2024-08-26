#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main()
{
      char userWord[50];
      printf("Enter the word: \n");
      scanf("%s", userWord);

      // Transform all upper character into lower character
      for (int i = 0; i < strlen(userWord); i++)
      {
            if (isupper(userWord[i]))
            {
                  userWord[i] = tolower(userWord[i]);
            }
      }

      // Open file
      char filename[25] = "words_alpha.txt";
      FILE *fPtr;
      if ((fPtr = fopen(filename, "r")) == NULL)
      {
            printf("Can't open file %s.\n", filename);
            return 1;
      }

      // Searching for words.
      char word[50];
      int flag = 0;
      int count = 0;
      int i = 0;
      int c;

      while ((c = getc(fPtr)) != EOF)
      {
            if (c == 10)
            {
                  word[i] = '\0';
                  if (strlen(word) == strlen(userWord))
                  {
                        for (int j = 0; j < strlen(userWord); j++)
                        {
                              if (userWord[j] == word[j])
                              {
                                    count++;
                              }
                        }
                        if (count == strlen(userWord))
                        {
                              printf("Correct");
                              flag = 1;
                              i = 0;
                              count = 0;
                        }
                        else
                        {
                              i = 0;
                              count = 0;
                        }
                  }
                  else
                  {
                        i = 0;
                        count = 0;
                  }
            }
            else
            {
                  word[i] = c;
                  i++;
            }
      }
      if (flag == 0)
      {
            printf("Error");
      }

      fclose(fPtr);
      return 0;
}