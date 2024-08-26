#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 256
#define SENTENCE_LENGTH 1024

typedef struct EnglishDictionary
{
      char english[MAX_LENGTH];
      char vietnamese[MAX_LENGTH];
      struct EnglishDictionary *left;
      struct EnglishDictionary *right;
} ED;

ED *makeNode(char *eng, char *viet)
{
      ED *newNode = (ED *)malloc(sizeof(ED));
      if (newNode == NULL)
      {
            printf("Error allocate memory for new node\n");
            exit(1);
      }

      strcpy(newNode->english, eng);
      strcpy(newNode->vietnamese, viet);
      newNode->left = NULL;
      newNode->right = NULL;

      return newNode;
}

ED *InsertNode(ED *ROOT, char *eng, char *viet)
{
      if (ROOT == NULL)
      {
            return makeNode(eng, viet);
      }
      if (ROOT != NULL)
      {
            if (strcmp(ROOT->english, eng) > 0)
            {
                  ROOT->left = InsertNode(ROOT->left, eng, viet);
            }
            else if (strcmp(ROOT->english, eng) < 0)
            {
                  ROOT->right = InsertNode(ROOT->right, eng, viet);
            }
      }
      return ROOT;
}

void printDictionary(ED *ROOT)
{
      if (ROOT != NULL)
      {
            printDictionary(ROOT->left);
            printf("%s \t %s\n", ROOT->english, ROOT->vietnamese);
            printDictionary(ROOT->right);
      }
}

ED *Read_Data(ED *ROOT)
{
      FILE *Dictionary;
      if ((Dictionary = fopen("data.txt", "r")) == NULL)
      {
            printf("Error opening file\n");
            exit(1);
      }

      char a[MAX_LENGTH];
      char b[MAX_LENGTH];
      while (feof(Dictionary) == 0)
      {
            fscanf(Dictionary, "%s", a);

            fgetc(Dictionary);

            fgets(b, MAX_LENGTH, Dictionary);

            if (b[strlen(b) - 1] == 10)
            {
                  b[strlen(b) - 1] = '\0';
            }
            ROOT = InsertNode(ROOT, a, b);
      }
      fclose(Dictionary);
      return ROOT;
}

ED *SearchDictionary(ED *root, char *eng)
{
      if (root == NULL || (strcmp(root->english, eng) == 0))
      {
            return root;
      }
      if (root != NULL)
      {
            if (strcmp(root->english, eng) > 0)
            {
                  SearchDictionary(root->left, eng);
            }
            else if (strcmp(root->english, eng) < 0)
            {
                  SearchDictionary(root->right, eng);
            }
      }
}

ED *Translate(ED *ROOT)
{
      char sentence[SENTENCE_LENGTH];
      gets(sentence);
      int num_space = 1;

      FILE *middleFile;
      if ((middleFile = fopen("middleFile.txt", "w")) == NULL)
      {
            printf("Error creating file\n");
            exit(1);
      }
      for (int i = 0; i < strlen(sentence); i++)
      {
            if (sentence[i] == 32)
            {
                  fputc(10, middleFile);
                  num_space++;
            }
            else
            {
                  fputc(sentence[i], middleFile);
            }
      }
      fclose(middleFile);

      if ((middleFile = fopen("middleFile.txt", "r")) == NULL)
      {
            printf("Error reading file\n");
            exit(1);
      }
      char b[num_space][MAX_LENGTH];
      int index = 0;
      while (feof(middleFile) == 0)
      {
            fscanf(middleFile, "%s", b[index]);
            fgetc(middleFile);
            index++;
      }
      fclose(middleFile);

      for (int i = 0; i < num_space; i++)
      {
            for (int j = 0; j < strlen(b[i]); j++)
            {
                  if (isupper(b[i][j]))
                  {
                        b[i][j] += 32;
                  }
            }
      }

      for (int i = 0; i < num_space; i++)
      {
            printf("%s\n", b[i]);
      }

      ED *found = ROOT;
      char translate[MAX_LENGTH];
      for (int i = 0; i < num_space; i++)
      {
            found = SearchDictionary(ROOT, b[i]);
            if (found == NULL)
            {
                  printf("%s khong co trong tu dien\n", b[i]);
                  printf("Hay them nghia tieng Viet cua tu %s vao trong tu dien: ", b[i]);
                  gets(translate);
                  ROOT = InsertNode(ROOT, b[i], translate);
            }
            else
            {
                  printf("%s ", found->vietnamese);
            }
      }

      printf("\n");

      return ROOT;
}

void UpdateDictionary(ED *ROOT, FILE *Dict)
{
      if (ROOT != NULL)
      {
            UpdateDictionary(ROOT->left, Dict);
            fprintf(Dict, "%s\t%s\n", ROOT->english, ROOT->vietnamese);
            UpdateDictionary(ROOT->right, Dict);
      }
}

int main()
{
      ED *Dictionary = NULL;
      FILE *Updated;
      int control;
      while (1)
      {
            printf("Tu dien dich Anh-Viet\n");
            printf("1. Doc file\n");
            printf("2. Hien thi du lieu\n");
            printf("3. Dich Anh-Viet\n");
            printf("4. Cap nhat tu dien\n");
            printf("Hay chon 1 trong 4 chuc nang: ");
            scanf("%d", &control);
            getchar();

            switch (control)
            {
            case 1:
                  Dictionary = Read_Data(Dictionary);
                  break;
            case 2:
                  printDictionary(Dictionary);
                  break;
            case 3:
                  Dictionary = Translate(Dictionary);
                  break;
            case 4:
                  if ((Updated = fopen("data.txt", "w")) == NULL)
                  {
                        printf("Error opening file!\n");
                        exit(1);
                  }
                  UpdateDictionary(Dictionary, Updated);
                  fclose(Updated);
                  break;
            default:
                  printf("Vui long nhap dung dinh dang!\n");
                  break;
            }
      }
}