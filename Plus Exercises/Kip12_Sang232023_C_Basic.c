#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LENGTH 12

typedef struct BaiXe
{
      char BienSo[MAX_LENGTH];
      int day, month, year;
      int hour, minute, second;
      int status;
      struct BaiXe *next;
} BaiXe;

typedef struct BaiXeHienTai
{
      char BienSo_HT[MAX_LENGTH];
      int day_HT, month_HT, year_HT;
      int hour_HT, minute_HT, second_HT;
      int status_HT;
      struct BaiXeHienTai *left;
      struct BaiXeHienTai *right;
} BXHT;

BXHT *CreateTreeNode(int day, int month, int year, int hour, int minute, int second, int status, char *code)
{
      BXHT *NewVehicle = (BXHT *)malloc(sizeof(BXHT));
      if (NewVehicle == NULL)
      {
            printf("In function CreateTreeNode error allocate memory!\n");
            exit(1);
      }

      strcpy(NewVehicle->BienSo_HT, code);
      NewVehicle->day_HT = day;
      NewVehicle->month_HT = month;
      NewVehicle->year_HT = year;
      NewVehicle->hour_HT = hour;
      NewVehicle->minute_HT = minute;
      NewVehicle->second_HT = second;
      NewVehicle->status_HT = status;
      NewVehicle->left = NULL;
      NewVehicle->right = NULL;

      return NewVehicle;
}

BXHT *AddTreeNode(BXHT *root, int day, int month, int year, int hour, int minute, int second, int status, char *code)
{
      if (root == NULL)
      {
            return CreateTreeNode(day, month, year, hour, minute, second, status, code);
      }
      if (strcmp(root->BienSo_HT, code) > 0)
      {
            root->left = AddTreeNode(root->left, day, month, year, hour, minute, second, status, code);
      }
      else if (strcmp(root->BienSo_HT, code) < 0)
      {
            root->right = AddTreeNode(root->right, day, month, year, hour, minute, second, status, code);
      }
}

BXHT *FindMin(BXHT *root)
{
      BXHT *p = root;

      while (p && p->left != NULL)
      {
            p = p->left;
      }

      return p;
}

BXHT *DeleteNode(BXHT *root, char *code)
{
      if (root == NULL)
      {
            return root;
      }
      if (strcmp(root->BienSo_HT, code) > 0)
      {
            root->left = DeleteNode(root->left, code);
      }
      else if (strcmp(root->BienSo_HT, code) < 0)
      {
            root->right = DeleteNode(root->right, code);
      }
      else
      {
            if (root->left == NULL)
            {
                  BXHT *temp = root->right;
                  free(root);
                  return temp;
            }
            else if (root->right == NULL)
            {
                  BXHT *temp = root->left;
                  free(root);
                  return temp;
            }

            BXHT *temp = FindMin(root->right);
            strcpy(root->BienSo_HT, temp->BienSo_HT);
            root->right = DeleteNode(root->right, temp->BienSo_HT);
      }
      return root;
}

BXHT *SearchVehicle(BXHT *root, char *Code)
{
      if (root == NULL)
      {
            return root;
      }
      if (strcmp(root->BienSo_HT, Code) == 0)
      {
            return root;
      }
      if (strcmp(root->BienSo_HT, Code) > 0)
      {
            SearchVehicle(root->left, Code);
      }
      else if (strcmp(root->BienSo_HT, Code) < 0)
      {
            SearchVehicle(root->right, Code);
      }
}

BaiXe *CreateVehicle(int day, int month, int year, int hour, int minute, int second, int status, char *Code)
{
      BaiXe *NewVehicle = (BaiXe *)malloc(sizeof(BaiXe));
      if (NewVehicle == NULL)
      {
            printf("In function CreateVehicle error allocate memory!\n");
            exit(1);
      }

      strcpy(NewVehicle->BienSo, Code);
      NewVehicle->day = day;
      NewVehicle->month = month;
      NewVehicle->year = year;
      NewVehicle->hour = hour;
      NewVehicle->minute = minute;
      NewVehicle->second = second;
      NewVehicle->status = status;
      NewVehicle->next = NULL;

      return NewVehicle;
}

BaiXe *AddVehicle(BaiXe *head, int day, int month, int year, int hour, int minute, int second, int status, char *Code)
{
      if (head == NULL)
      {
            return CreateVehicle(day, month, year, hour, minute, second, status, Code);
      }

      BaiXe *NewVehicle = CreateVehicle(day, month, year, hour, minute, second, status, Code);
      BaiXe *p = head;
      while (p->next != NULL)
      {
            p = p->next;
      }
      p->next = NewVehicle;
      return head;
}

BaiXe *ReadFile(BaiXe *head)
{
      char Code[MAX_LENGTH];
      int day, month, year;
      int hour, minute, second;
      int status;

      FILE *Log;
      if ((Log = fopen("log_input.txt", "r")) == NULL)
      {
            printf("In function ReadFile error can't read file\n");
            exit(1);
      }
      while (feof(Log) == 0)
      {
            fscanf(Log, "%d-%d-%d", &year, &month, &day);
            fgetc(Log);
            fscanf(Log, "%d:%d:%d", &hour, &minute, &second);
            fgetc(Log);
            fscanf(Log, "%s", Code);
            fgetc(Log);
            fscanf(Log, "%d", &status);
            if (feof(Log) == 0)
            {
                  head = AddVehicle(head, day, month, year, hour, minute, second, status, Code);
            }
            fgetc(Log);
      }
      printf("Doc file thanh cong!\n");
      fclose(Log);
      return head;
}

int checkDate(int day, int month, int year)
{
      if (day < 1 || day > 31)
      {
            return 1;
      }
      if (month < 1 || month > 12)
      {
            return 1;
      }
      if (year < 1000)
      {
            return 1;
      }
      return 0;
}

void Print_Day_Info(BaiXe *head)
{
      int day, month, year;
      do
      {
            printf("Hay nhap vao ngay can kiem tra voi dinh dang DD-MM-YYYY: ");
            scanf("%d %d %d", &day, &month, &year);
            getchar();
            if (checkDate(day, month, year))
            {
                  printf("Yeu cau nhap dung dinh dang!\n");
            }
      } while (checkDate(day, month, year));

      int GuiXe = 0;
      int LayXe = 0;
      int Total = 0;
      while (head != NULL)
      {
            if ((head->day == day) && (head->month == month) && (head->year == year))
            {
                  Total++;
                  if (head->status == 0)
                  {
                        LayXe++;
                  }
                  else if (head->status == 1)
                  {
                        GuiXe++;
                  }
            }
            head = head->next;
      }
      printf("Date %d-%d-%d Total %d, In %d, Out %d\n", year, month, day, Total, GuiXe, LayXe);
}

BXHT *Lay_Thong_Tin_HT(BXHT *root, BaiXe *head)
{
      while (head != NULL)
      {
            if (head->status == 1)
            {
                  root = AddTreeNode(root, head->day, head->month, head->year, head->hour, head->minute, head->second, head->status, head->BienSo);
            }
            else if (head->status == 0)
            {
                  root = DeleteNode(root, head->BienSo);
            }
            head = head->next;
      }
      return root;
}

void subprint(BaiXe *head)
{
      while (head != NULL)
      {
            printf("%d-%d-%d %d:%d:%d %s %d\n", head->year, head->month, head->day, head->hour, head->minute, head->second, head->BienSo, head->status);
            head = head->next;
      }
}

void count(BXHT *root, int *num)
{
      if (root != NULL)
      {
            *num += 1;
            count(root->left, num);
            count(root->right, num);
      }
}

void printTree(BXHT *root)
{
      if (root != NULL)
      {
            printTree(root->left);
            printf("%-20s %4d-%02d-%02d %02d:%02d:%02d\n", root->BienSo_HT, root->year_HT, root->month_HT, root->day_HT, root->hour_HT, root->minute_HT, root->second_HT);
            printTree(root->right);
      }
}

void Print_BaiXe_HT(BXHT *root)
{
      int num_node = 0;
      count(root, &num_node);
      printf("Tong so xe hien co: %d\n", num_node);
      printf("%-20s %-20s\n", "Bien So", "Thoi Gian Gui");
      printTree(root);
}

void Update_Log_File(BaiXe *head, FILE *Update)
{
      while (head != NULL)
      {
            fprintf(Update, "%04d-%02d-%02d %02d:%02d:%02d %-12s %d\n", head->year, head->month, head->day, head->hour, head->minute, head->second, head->BienSo, head->status);
            head = head->next;
      }
}

void Present_Log_File(BXHT *root, FILE *Present)
{
      if (root != NULL)
      {
            fprintf(Present, "%04d-%02d-%02d %02d:%02d:%02d %-12s %d\n", root->year_HT, root->month_HT, root->day_HT, root->hour_HT, root->minute_HT, root->second_HT, root->BienSo_HT, root->status_HT);
            Present_Log_File(root->left, Present);
            Present_Log_File(root->right, Present);
      }
}

void Parking(BaiXe **head, BXHT **root)
{
      time_t t = time(NULL);
      struct tm tm = *localtime(&t);
      int year = tm.tm_year + 1900;
      int month = tm.tm_mon + 1;
      int day = tm.tm_mday;
      int hour = tm.tm_hour;
      int minute = tm.tm_min;
      int second = tm.tm_sec;
      int status = 1;

      char BienSo[MAX_LENGTH];
      printf("Hay dien bien so xe: ");
      gets(BienSo);

      BXHT *Found = SearchVehicle(*root, BienSo);
      if (Found == NULL)
      {
            *head = AddVehicle(*head, day, month, year, hour, minute, second, status, BienSo);
            *root = AddTreeNode(*root, day, month, year, hour, minute, second, status, BienSo);
            printf("%-20s: Gui xe thanh cong %04d-%02d-%02d %02d:%02d:%02d\n", BienSo, year, month, day, hour, minute, second);
      }
      else if (Found != NULL)
      {
            printf("Loi bien so xe %s da ton tai\n", BienSo);
      }
}

void Removing(BaiXe **head, BXHT **root)
{
      time_t t = time(NULL);
      struct tm tm = *localtime(&t);
      int year = tm.tm_year + 1900;
      int month = tm.tm_mon + 1;
      int day = tm.tm_mday;
      int hour = tm.tm_hour;
      int minute = tm.tm_min;
      int second = tm.tm_sec;
      int status = 0;

      char BienSo[MAX_LENGTH];
      printf("Hay dien bien so xe: ");
      gets(BienSo);

      BXHT *Found = SearchVehicle(*root, BienSo);
      if (Found != NULL)
      {
            *head = AddVehicle(*head, day, month, year, hour, minute, second, status, BienSo);
            *root = DeleteNode(*root, BienSo);
            printf("%-20s Lay xe thanh cong\n", BienSo);
      }
      else if (Found == NULL)
      {
            printf("%-20s Lay xe KHONG thanh cong do xe khong gui trong bai\n", BienSo);
      }
}

void History(BaiXe *head)
{
      char BienSo[MAX_LENGTH];
      printf("Hay nhap vao 1 bien so xe: ");
      gets(BienSo);
      int flag = 0;
      while (head != NULL)
      {
            if (strcmp(head->BienSo, BienSo) == 0)
            {
                  flag = 1;
                  if (head->status == 0)
                  {
                        printf("Xe %s duoc lay ra vao %04d-%02d-%02d %02d:%02d:%02d\n", BienSo, head->year, head->month, head->day, head->hour, head->minute, head->second);
                  }
                  else
                  {
                        printf("Xe %s duoc gui vao %04d-%02d-%02d %02d:%02d:%02d\n", BienSo, head->year, head->month, head->day, head->hour, head->minute, head->second);
                  }
            }
            head = head->next;
      }
      if (flag == 0)
      {
            printf("Khong co lich su gui/lay cua xe %s\n", BienSo);
      }
}

void freeList(BaiXe *head)
{
      BaiXe *p;
      while (head != NULL)
      {
            p = head;
            head = head->next;
            free(p);
      }
}

void freeTree(BXHT *Tree)
{
      if (Tree != NULL)
      {
            freeTree(Tree->left);
            freeTree(Tree->right);
            free(Tree);
      }
}

int main()
{
      int control;
      FILE *LogUpdate;
      FILE *LogPresent;
      BaiXe *InfoBaiXe = NULL;
      BXHT *InfoBaiXe_HT = NULL;
      while (1)
      {
            printf("Chuong trinh quan ly bai xe\n");
            printf("Vui long chon mot trong cac chuc nang sau\n");
            printf("[1] Doc du lieu tu file\n");
            printf("[2] Tra cuu so luong xe gui/lay theo ngay trong qua khu\n");
            printf("[3] Thong tin cac xe trong bai hien tai\n");
            printf("[4] Gui them xe moi\n");
            printf("[5] Tra xe\n");
            printf("[6] Cap nhat file log\n");
            printf("[7] Luu danh sach xe dang co trong bai ra file\n");
            printf("[8] Tra cuu lich su gui/lay xe\n");
            printf("Lua chon cua ban la: ");
            scanf("%d", &control);
            getchar();

            switch (control)
            {
            case 1:
                  InfoBaiXe = ReadFile(InfoBaiXe);
                  InfoBaiXe_HT = Lay_Thong_Tin_HT(InfoBaiXe_HT, InfoBaiXe);
                  subprint(InfoBaiXe);
                  break;
            case 2:
                  Print_Day_Info(InfoBaiXe);
                  break;
            case 3:
                  Print_BaiXe_HT(InfoBaiXe_HT);
                  printf("\n\n");
                  subprint(InfoBaiXe);
                  break;
            case 4:
                  Parking(&InfoBaiXe, &InfoBaiXe_HT);
                  break;
            case 5:
                  Removing(&InfoBaiXe, &InfoBaiXe_HT);
                  break;
            case 6:
                  if ((LogUpdate = fopen("change_log.txt", "w")) == 0)
                  {
                        printf("Error create change_log.txt file\n");
                        exit(1);
                  }
                  Update_Log_File(InfoBaiXe, LogUpdate);
                  fclose(LogUpdate);
                  break;
            case 7:
                  if ((LogPresent = fopen("log_present.txt", "w")) == 0)
                  {
                        printf("Error create log_present.txt file\n");
                        exit(1);
                  }
                  Present_Log_File(InfoBaiXe_HT, LogPresent);
                  fclose(LogPresent);
                  break;
            case 8:
                  History(InfoBaiXe);
                  break;
            default:
                  freeList(InfoBaiXe);
                  freeTree(InfoBaiXe_HT);
                  printf("Thoat chuong trinh...\n");
                  return 0;
            }
      }
}