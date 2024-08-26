#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 300

typedef struct DictionaryTree
{
      char English[MAX_LENGTH];
      char Vietnam[MAX_LENGTH];
      struct DictionaryTree *left;
      struct DictionaryTree *right;
} DT;

DT *CreateNode(char *eng, char *vn)
{
      DT *newNode = (DT *)malloc(sizeof(DT));
      if (newNode == NULL)
      {
            printf("Error allocate memory!\n");
            exit(1);
      }

      strcpy(newNode->English, eng);
      strcpy(newNode->Vietnam, vn);
      newNode->left = NULL;
      newNode->right = NULL;

      return newNode;
}

DT *InsertNode(DT *root, char *eng, char *vn)
{
      if (root == NULL)
      {
            return CreateNode(eng, vn);
      }

      if ((strcmp(root->English, eng)) > 0)
      {
            root->left = InsertNode(root->left, eng, vn);
      }
      else if (strcmp(root->English, eng) < 0)
      {
            root->right = InsertNode(root->right, eng, vn);
      }
}

DT *SearchDict(DT *root, char *eng)
{
      if (root == NULL)
      {
            printf("NULL\n\n");
            return NULL;
      }
      if (strcmp(root->English, eng) == 0)
      {
            printf("%s\n\n", root->English);
            return root;
      }
      else if (strcmp(root->English, eng) > 0)
      {
            printf("%s\n", root->left->English);
            SearchDict(root->left, eng);
      }
      else if (strcmp(root->English, eng) < 0)
      {     
            printf("%s\n", root->right->English);
            SearchDict(root->right, eng);
      }
}

DT *LoadDictionary(DT *root, char * filename)
{
      char engWord[MAX_LENGTH];
      char vietWord[MAX_LENGTH];

      FILE *Dict;
      if ((Dict = fopen(filename, "r")) == NULL)
      {
            printf("Error in LoadDictionary can't open file!\n");
            exit(1);
      }

      while (feof(Dict) == 0)
      {
            fscanf(Dict, "%s", engWord);
            fgetc(Dict);
            fscanf(Dict, "%s", vietWord);
            fgetc(Dict);

            if (feof(Dict) == 0)
            {
                  printf("%s %s\n", engWord, vietWord);
                  root = InsertNode(root, engWord, vietWord);
            }
      }

      fclose(Dict);
      return root;
}

void printDictionary(DT * root)
{
      if(root != NULL)
      {
            printf("%s %s\n", root->English, root->Vietnam);
            printDictionary(root->left);
            printDictionary(root->right);
      }
}

int check_for_space(char *word)
{
      for (int i = 0; i < strlen(word); i++)
      {
            if (word[i] == 32)
            {
                  return 1;
            }
      }
      return 0;
}

DT * UpdateDictionary(DT * root)
{
      char engWord[MAX_LENGTH];
      char vietWord[MAX_LENGTH];

      DT *search = NULL;

      do
      {
            printf("Hay nhap mot tu tieng Anh: ");
            gets(engWord);
            if (check_for_space(engWord))
            {
                  printf("Tu tieng Anh khong duoc co dau cach!\n");
            }
      } while (check_for_space(engWord));

      search = SearchDict(root, engWord);
      if (search == NULL)
      {
            do
            {
                  printf("Hay nhap nghia tieng Viet voi dinh dang <tu1_tu2>: ");
                  gets(vietWord);
                  if (check_for_space(vietWord))
                  {
                        printf("Vui long nhap dung dinh dang <tu1_tu2>\n");
                  }
            } while (check_for_space(vietWord));
            root = InsertNode(root, engWord, vietWord);
            return root;
      }
      else
      {
            printf("Tu %s da co trong tu dien!\n", engWord);
            return root;
      }
}

void TranslateWord(DT * root)
{
      char engWord[MAX_LENGTH];
      printf("Hay nhap vao tu tieng Anh: ");
      gets(engWord);

      DT * search = NULL;
      printf("%s\n", root->English);
      search = SearchDict(root, engWord);
      if(search == NULL)
      {
            printf("Khong tim thay tu can tra!\n");
      }
      else
      {
            printf("%s\n", search->Vietnam);
      }

}

int main(int argc, char *argv[])
{
      int control;
      DT *Dictionary = NULL;
      Dictionary = LoadDictionary(Dictionary, argv[1]);
      while (1)
      {
            printf("CHAO MUNG DEN VOI CHUONG TRINH BKTRANSLATE\n");
            printf("1. Duyet theo chieu sau\n");
            printf("2. Them tu moi\n");
            printf("3. Dich cau Anh-Viet\n");
            printf("Hay chon 1 trong 5 chuc nang tren: ");
            scanf("%d", &control);
            getchar();

            switch (control)
            {
            case 1:
                  printDictionary(Dictionary);
                  break;
            case 2:
                  Dictionary = UpdateDictionary(Dictionary);
                  break;
            case 3:
                  TranslateWord(Dictionary);
                  break;
            default:
                  printf("Vui long nhap dung dinh dang!\n");
                  break;
            }
      }
      return 0;
}