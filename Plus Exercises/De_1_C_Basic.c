#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DoiBongDa
{
      int final_score;
      char team_code[11];
      struct DoiBongDa *left;
      struct DoiBongDa *right;
      struct DoiBongDa *parents;
} DBD;

///////////////////////////////////////////////////////////////////////////////////////////////////
DBD *makeNode(char *code, int score)
{
      DBD *newNode = (DBD *)malloc(sizeof(DBD));
      if (newNode == NULL)
      {
            printf("In function makeNode can't allocate memory!\n");
            exit(1);
      }

      newNode->final_score = score;
      strcpy(newNode->team_code, code);
      newNode->parents = NULL;
      newNode->right = NULL;
      newNode->left = NULL;

      return newNode;
}

DBD *insert(DBD *root, char *code, int score, int *n)
{
      if (root == NULL)
      {
            root = makeNode(code, score);
            printf("Thanh cong tao nut moi thu %d \t dia chi: %s\n", *n, root->team_code);
            *n += 1;
            return root;
      }

      if (strcmp(root->team_code, code) > 0)
      {
            root->left = insert(root->left, code, score, n);
            root->left->parents = root;
      }
      if (strcmp(root->team_code, code) < 0)
      {
            root->right = insert(root->right, code, score, n);
            root->right->parents = root;
      }
      if (strcmp(root->team_code, code) == 0)
      {
            root->final_score += score;
      }
      return root;
}

DBD *Tao_Cay(DBD *root)
{
      FILE *KetQua;
      if ((KetQua = fopen("Quan Ly Ket Qua Bong Da.txt", "r")) == NULL)
      {
            printf("Can't read file!\n");
            return root;
      }

      int numNode = 1;
      int c;
      int ti_so[2];
      int score[2];
      char **team = (char **)malloc(sizeof(char *) * 2);
      for (int i = 0; i < 2; i++)
      {
            team[i] = (char *)malloc(sizeof(char) * 11);
      }
      do
      {
            for (int i = 0; i < 2; i++)
            {
                  fscanf(KetQua, "%s", team[i]);
                  team[i][strlen(team[i])] = '\0';
                  fgetc(KetQua);
            }
            for (int j = 0; j < 2; j++)
            {
                  printf("%s\t", team[j]);
            }
            for (int i = 0; i < 2; i++)
            {
                  fscanf(KetQua, "%d", &ti_so[i]);
                  fgetc(KetQua);
            }
            for (int j = 0; j < 2; j++)
            {
                  printf("%d\t", ti_so[j]);
            }
            printf("\n");

            if (ti_so[0] > ti_so[1])
            {
                  score[0] = 3;
                  score[1] = 0;
                  for (int i = 0; i < 2; i++)
                  {
                        root = insert(root, team[i], score[i], &numNode);
                  }
            }
            else if (ti_so[0] < ti_so[1])
            {
                  score[0] = 0;
                  score[1] = 3;
                  for (int i = 0; i < 2; i++)
                  {
                        root = insert(root, team[i], score[i], &numNode);
                  }
            }
            else if (ti_so[0] == ti_so[1])
            {
                  score[0] = score[1] = 1;
                  for (int i = 0; i < 2; i++)
                  {
                        root = insert(root, team[i], score[i], &numNode);
                  }
            }
      } while (feof(KetQua) == 0);

      return root;
}
///////////////////////////////////////////////////////////////////////////////////////////////////

void In_Ket_Qua(DBD *root)
{
      if (root != NULL)
      {
            In_Ket_Qua(root->left);
            printf("Thong tin Doi Bong: %-20s Diem So: %d\n", root->team_code, root->final_score);
            In_Ket_Qua(root->right);
      }
}

void Tim_Doi_Bong(DBD *root, char *search_key)
{
      if (root != NULL)
      {
            if (strcmp(root->team_code, search_key) > 0)
            {
                  Tim_Doi_Bong(root->left, search_key);
            }
            if (strcmp(root->team_code, search_key) == 0)
            {
                  printf("Da tim thay doi bong.\n");
                  printf("Thong tin Doi Bong: %-20s Diem So: %d\n", root->team_code, root->final_score);
            }
            if (strcmp(root->team_code, search_key) < 0)
            {
                  Tim_Doi_Bong(root->right, search_key);
            }
      }
      else
      {
            printf("Khong tim thay thong tin doi bong ma %s\n", search_key);
            return;
      }
}

char *Tim_Doi_Xuong_Hang(DBD *root, int X)
{
      if (root != NULL)
      {
            Tim_Doi_Xuong_Hang(root->left, X);
            if (root->final_score < X)
            {
                  return root->team_code;
            }
            Tim_Doi_Xuong_Hang(root->right, X);
      }
}

void So_Doi_Xuong_Hang(DBD * root, int *Num, int X)
{
      if(root != NULL)
      {
            So_Doi_Xuong_Hang(root->left, Num, X);
            if(root->final_score < X)
            {
                  *Num += 1;
            }
            So_Doi_Xuong_Hang(root->right, Num, X);
      }
}

DBD * FindMin(DBD * root)
{
      DBD * p = root;

      while(p && p->left != NULL)
      {
            p = p->left;
      }

      return p;
}

DBD * DeleteNode(DBD * root, char * name)
{
      if(root == NULL)
      {
            return root;
      }
      if(strcmp(root->team_code, name) > 0)
      {
            root->left = DeleteNode(root->left, name);
      }
      else if(strcmp(root->team_code, name) < 0)
      {
            root->right = DeleteNode(root->right, name);
      }
      else
      {
            if(root->left == NULL)
            {
                  DBD * temp = root->right;
                  free(root);
                  return temp;
            }
            else if(root->right == NULL)
            {
                  DBD * temp = root->left;
                  free(root);
                  return temp;
            }

            DBD * temp = FindMin(root->right);
            strcpy(root->team_code, temp->team_code);
            root->final_score = temp->final_score;
            root->right = DeleteNode(root->right, temp->team_code);
      }
      return root;
}

DBD *Xuong_Hang(DBD *root)
{
      int X;
      int n = 0;
      char *terminate = NULL;
      printf("Hay nhap vao so diem X: ");
      scanf("%d", &X);
      getchar();
      So_Doi_Xuong_Hang(root, &n, X);
      printf("%d\n", n);

      while(n > 0)
      {
            terminate = Tim_Doi_Xuong_Hang(root, X);
            n--;
            printf("%s\n", terminate);
            root = DeleteNode(root, terminate);
            In_Ket_Qua(root);
      }
      return root;
}

void Xuat_File(DBD *root, FILE *Football)
{
      if (root != NULL)
      {
            Xuat_File(root->left, Football);
            fprintf(Football, "%s\t%d\n", root->team_code, root->final_score);
            Xuat_File(root->right, Football);
      }
}

int main()
{
      int control;
      int min;
      DBD *DoiBong = NULL;
      while (1)
      {
            for (int i = 1; i <= 10; i++)
            {
                  printf("%c", '=');
            }
            printf("Chao Mung Den Voi Chuong Trinh Quan Ly Ket Qua Bong Da");
            for (int i = 1; i <= 10; i++)
            {
                  printf("%c", '=');
            }
            printf("\n");
            printf("1. Tao Cay\n");
            printf("2. Ket Qua\n");
            printf("3. Tim Kiem\n");
            printf("4. Xuong Hang\n");
            printf("5. Xuat file\n");
            printf("Hay chon 1 trong 5 chuc nang tren: ");
            do
            {
                  scanf("%d", &control);
                  if (control < 1 || control > 5)
                  {
                        printf("\nGia tri nhap khong hop le. Vui long nhap lai: ");
                  }
            } while (control < 1 || control > 5);

            fflush(stdin);
            if (control == 1)
            {

                  DoiBong = Tao_Cay(DoiBong);
            }
            if (control == 2)
            {
                  In_Ket_Qua(DoiBong);
            }
            if (control == 3)
            {
                  char search_key[11];
                  printf("Hay nhap ten doi bong can tim: ");
                  gets(search_key);
                  Tim_Doi_Bong(DoiBong, search_key);
                  fflush(stdin);
            }
            if (control == 4)
            {
                  DoiBong = Xuong_Hang(DoiBong);
            }
            if (control == 5)
            {
                  FILE *Football;
                  if ((Football = fopen("KetQua.txt", "w")) == NULL)
                  {
                        printf("Can't create file\n");
                        exit(1);
                  }
                  Xuat_File(DoiBong, Football);
                  fclose(Football);
            }
      }
}