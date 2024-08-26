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

///////////////////////////////////////////////////////////////////////////////////////////////////
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
            return NULL;
      }
      if (strcmp(root->English, eng) == 0)
      {
            return root;
      }
      else if (strcmp(root->English, eng) > 0)
      {
            root = SearchDict(root->left, eng);
      }
      else if (strcmp(root->English, eng) < 0)
      {
            root = SearchDict(root->right, eng);
      }
}
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
DT *LoadDictionary(DT *root)
{
      char engWord[MAX_LENGTH];
      char vietWord[MAX_LENGTH];

      FILE *Dict;
      if ((Dict = fopen("dict.txt", "r")) == NULL)
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
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
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

void UpdateFileDict(DT * root, FILE * Update)
{
      if(root != NULL)
      {
            UpdateFileDict(root->left, Update);
            fprintf(Update, "%s %s\n", root->English, root->Vietnam);
            UpdateFileDict(root->right, Update);
      }
}

DT *Add_UpdateDictionary(DT *root)
{
      char engWord[MAX_LENGTH];
      char vietWord[MAX_LENGTH];
      char answer;
      DT *search = NULL;

      FILE *Dict;
      if ((Dict = fopen("dict.txt", "w")) == NULL)
      {
            printf("Error in Add_UpdateDictionary can't open file!\n");
            exit(1);
      }

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
            printf("Khong co tu %s trong tu dien! Hay cap nhat tieng Viet!\n", engWord);
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
            UpdateFileDict(root, Dict);
      }
      else
      {
            do
            {
                  printf("Ban co muon cap nhat nghia tieng Viet ? Hay nhap 'y'/n': ");
                  scanf("%c", &answer);
                  getchar();
                  if ((answer != 'y') && (answer != 'n'))
                  {
                        printf("Vui long nhap dung dinh dang!\n");
                  }
            } while ((answer != 'y') && (answer != 'n'));

            if (answer == 'y')
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
                  strcpy(search->Vietnam, vietWord);
                  UpdateFileDict(root, Dict);
            }
            else
            {
                  UpdateFileDict(root, Dict);
            }
      }
      fclose(Dict);
      return root;
}
////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
void Translate(DT * root)
{
      char sentence[MAX_LENGTH];
      int space = 1;
      gets(sentence);
      for(int i = 0; i < strlen(sentence); i++)
      {
            if(sentence[i] == 32)
            {
                  space++;
            }
      }

      char seperate[space][MAX_LENGTH];
      int j = 0, k = 0;
      for(int i = 0; i < strlen(sentence) + 1; i++)
      {
            if(sentence[i] != 32 && sentence[i] != '\0')
            {
                  seperate[j][k] = sentence[i];
                  k++;
            }
            else 
            {
                  seperate[j][k] = '\0';
                  k = 0;
                  j++;
            }
      }

      for(int i = 0; i < space; i++)
      {
            printf("%s\n", seperate[i]);
      }

      DT * search = NULL;
      for(int i = 0; i < space; i++)
      {
            search = SearchDict(root, seperate[i]);
            if(search == NULL)
            {
                  printf("<thieu tu> ");
            }
            else
            {
                  printf("%s ", search->Vietnam);
            }
      }
      printf("\n");
}
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
void printDictionary(DT *root)
{
      if (root != NULL)
      {
            printDictionary(root->left);
            printf("%s %s\n", root->English, root->Vietnam);
            printDictionary(root->right);
      }
}
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
void freeTree(DT *root)
{
      if (root != NULL)
      {
            freeTree(root->left);
            freeTree(root->right);
            free(root);
      }
}
///////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
      int control;
      DT *Dictionary = NULL;
      while (1)
      {
            printf("CHAO MUNG DEN VOI CHUONG TRINH BKTRANSLATE\n");
            printf("1. Nap tu dien\n");
            printf("2. Noi dung tu dien\n");
            printf("3. Them/Sua tu\n");
            printf("4. Dich cau Anh-Viet\n");
            printf("5. Thoat\n");
            printf("Hay chon 1 trong 5 chuc nang tren: ");
            scanf("%d", &control);
            getchar();

            switch (control)
            {
            case 1:
                  Dictionary = LoadDictionary(Dictionary);
                  break;
            case 2:
                  printDictionary(Dictionary);
                  break;
            case 3:
                  Dictionary = Add_UpdateDictionary(Dictionary);
                  break;
            case 4:
                  Translate(Dictionary);
                  break;
            case 5:
                  freeTree(Dictionary);
                  printf("Cam on ban da su dung chuong trinh\n");
                  return 0;
            default:
                  printf("Vui long nhap dung dinh dang!\n");
                  break;
            }
      }
}