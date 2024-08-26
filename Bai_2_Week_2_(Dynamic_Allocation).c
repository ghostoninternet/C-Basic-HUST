#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int TOTAL_WORDS = 370100;
const int WORD_LEN = 30;

void standalizeWord(char *Word)
{
      int i = 0;
      while (i < strlen(Word))
      {
            if (Word[i] == '\r' || Word[i] == '\n')
            {
                  Word[i] = '\0';
                  break;
            }
            else
            {
                  i++;
            }
      }

}

char **loadDict (char *filename, int *dict_size)
{
      char **Words;
      int i, total_size = 0;
      char buff[50];
      FILE *fPtr;
      if((fPtr = fopen(filename, "r")) == NULL)
      {
            perror("Error in opening file");
            return NULL;
      }

      //Cap phat mang con tro
      Words = (char **)malloc(sizeof(char *) * TOTAL_WORDS);
      i = 0;

      while(fgets(buff, WORD_LEN, fPtr) != NULL)
      {
            standalizeWord(buff);
            Words[i] = (char *)malloc(sizeof(char) * (strlen(buff) + 1));
            strcpy(Words[i], buff);
            puts(Words[i]);
            total_size = total_size + strlen(buff) + 1;
            i++;
      }
      fclose(fPtr);
      printf("Total Read: %d\n", i);
      printf("Total size: %d\n", total_size);
      *dict_size = i;
      return Words;
}

void freeMem(char **pointer)
{
      //Giai phong bo nho
      for (int i = 0; i < TOTAL_WORDS; i++)
      {
            free(pointer[i]);
      }
      free(pointer);
      
}

int checkWord(char *word, char **Dict, int dict_size)
{
      for(int i = 0; i < dict_size; i++)
      {
            if(strcmp(word, Dict[i]) == 0)
            {
                  return 1;
            }
      }
      return 0;
}

int main()
{
      char **Dict;
      char lookupW[30];
      int dict_size;
      char filename[] = "words_alpha.txt";
      Dict = loadDict(filename, &dict_size);

      printf("Tra cuu tu dien:\n");
      while(1)
      {
            printf("Tu can tra: ");
            fflush(stdin);
            gets(lookupW);
            if(strcmp(lookupW, "@") == 0)
            {
                  break;
            }
            if(checkWord(lookupW, Dict, dict_size))
            {
                  printf("Tu nay dung!\n");
            }
            else
            {
                  printf("Tu nay KHONG co trong tu dien!\n");
            }
      }
      freeMem(Dict);
      return 0;
}