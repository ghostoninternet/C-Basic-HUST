#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 40

typedef struct Destination
{
      char place[MAX_LENGTH];
      int hour;
      int minute;
      struct Destination *next;
} Destination;

void freeMemory(Destination *head)
{
      Destination *p;
      while (head != NULL)
      {
            p = head;
            head = head->next;
            free(p);
      }
}

Destination *MakeDestination(char *pname, int h, int m)
{
      Destination *newNode = (Destination *)malloc(sizeof(Destination));
      if (newNode == NULL)
      {
            printf("In function MakeDestination error allocate memory!\n");
            exit(1);
      }

      strcpy(newNode->place, pname);
      newNode->hour = h;
      newNode->minute = m;
      newNode->next = NULL;

      return newNode;
}

Destination *AddDestination(Destination *head, char *pname, int h, int m)
{
      if (head == NULL)
      {
            return MakeDestination(pname, h, m);
      }

      Destination *newDestination = MakeDestination(pname, h, m);
      Destination *p = head;
      while (p->next != NULL)
      {
            p = p->next;
      }
      p->next = newDestination;
      return head;
}

Destination *ReadFile(Destination *head)
{
      FILE *Log;
      if ((Log = fopen("log.txt", "r")) == NULL)
      {
            printf("In function ReadFile error reading file!\n");
            exit(1);
      }

      char pname[MAX_LENGTH];
      int h;
      int m;

      while (feof(Log) == 0)
      {
            fscanf(Log, "%s", pname);
            fgetc(Log);
            fscanf(Log, "%d %d", &h, &m);
            if (feof(Log) == 0)
            {
                  head = AddDestination(head, pname, h, m);
            }
            fgetc(Log);
      }
      printf("Doc du lieu thanh cong\n");
      fclose(Log);
      return head;
}

void PrintHistory(Destination *head)
{
      printf("%-50s%-10s%-10s\n", "Dia diem", "Gio", "Phut");
      while (head != NULL)
      {
            printf("%-50s%-10d%-10d\n", head->place, head->hour, head->minute);
            head = head->next;
      }
}

int check_space(char *pname)
{
      for (int i = 0; i < strlen(pname); i++)
      {
            if (pname[i] == 32)
            {
                  return 1;
            }
      }
      return 0;
}

void SearchDestination(Destination *head)
{
      char pname[MAX_LENGTH];
      do
      {
            printf("Hay nhap mot dia diem (su dung dau '_' thay cho dau cach): ");
            gets(pname);
            if (check_space(pname))
            {
                  printf("Yeu cau nhap dung dinh dang!\n");
            }
      } while (check_space(pname));

      Destination *p = head;
      int i = 0;
      int found = 0;
      while (p != NULL)
      {
            if (strcmp(pname, p->place) == 0)
            {
                  found = 1;
                  if (i == 0)
                  {
                        i++;
                        if (p->minute == 0)
                        {
                              printf("%d:%d0", p->hour, p->minute);
                        }
                        else
                        {
                              printf("%d:%d", p->hour, p->minute);
                        }
                  }
                  else
                  {
                        if (p->minute == 0)
                        {
                              printf(", %d:%d0", p->hour, p->minute);
                        }
                        else
                        {
                              printf(", %d:%d", p->hour, p->minute);
                        }
                  }
            }
            p = p->next;
      }
      if (found == 0)
      {
            printf("Ban chua di toi dia diem do\n");
      }
}

int check_value(int h, int m)
{
      if (h < 0 && h >= 24)
      {
            return 1;
      }
      if (m < 0 && m >= 60)
      {
            return 1;
      }
      return 0;
}

void TimeSearchDestination(Destination *head)
{
      int h, m;
      do
      {
            printf("Hay nhap vao thoi gian voi dinh dang <gio phut>: ");
            scanf("%d %d", &h, &m);
            getchar();
            if (check_value(h, m))
            {
                  printf("Yeu cau 0<=gio<24 va 0<=phut<60!\n");
            }
      } while (check_value(h, m));

      Destination *new = NULL;
      while (head != NULL)
      {
            if (head->hour == h)
            {
                  new = AddDestination(new, head->place, head->hour, head->minute);
            }
            head = head->next;
      }

      if (new == NULL)
      {
            printf("KHONG tim thay lich su di chuyen\n");
      }

      while (new != NULL)
      {
            if (new->next != NULL)
            {
                  if (new->minute > m)
                  {
                        printf("KHONG tim thay lich su di chuyen!\n");
                        break;
                  }
                  if (new->minute <= m &&new->next->minute > m)
                  {
                        printf("%s\n", new->place);
                        break;
                  }
                  if (new->minute <= m &&new->next->minute <= m)
                  {
                        new = new->next;
                  }
            }
            else
            {
                  printf("%s\n", new->place);
                  break;
            }
      }
      freeMemory(new);
}

void COVID19_Trace(Destination *head)
{
      char pname[MAX_LENGTH];
      int h, m;
      do
      {
            printf("Hay nhap vao dia diem va thoi gian voi dinh dang <dia_diem gio phut>: ");
            scanf("%s %d %d", pname, &h, &m);
            getchar();
            if (check_value(h, m))
            {
                  printf("Yeu cau 0<=gio<24 va 0<=phut<60!\n");
            }
            if (check_space(pname))
            {
                  printf("Yeu cau nhap dia diem su dung '_' thay cho dau cach!\n");
            }
      } while (check_value(h, m) + check_space(pname) != 0);

      int flag = 0;
      while (head != NULL)
      {
            if (strcmp(head->place, pname) == 0)
            {
                  if (head->hour == h)
                  {
                        if (head->minute >= m)
                        {
                              printf("Ban co kha nang bi lay Covid, can phai khai bao y te ngay lap tuc!\n");
                              flag = 1;
                              break;
                        }
                  }
                  if (head->hour > h)
                  {
                        printf("Ban co kha nang bi lay Covid, can phai khai bao y te ngay lap tuc!\n");
                        flag = 1;
                        break;
                  }
            }

            head = head->next;
      }
      
      if(flag == 0)
      {
            printf("Lich su di chuyen cua ban OK\n");
      }
}

int main()
{
      int control;
      Destination *HistoryDestination = NULL;
      while (1)
      {
            printf("\nTRUY VET COVID-19\n");
            printf("1. Nap du lieu\n");
            printf("2. In lich su di chuyen\n");
            printf("3. Tim kiem lich su di chuyen theo dia diem\n");
            printf("4. Tim kiem thong tin di chuyen theo thoi gian\n");
            printf("5. Kiem tra truy ve moi nhat\n");
            printf("6. Thoat\n");
            printf("Hay chon 1 trong 6 chuc nang tren: ");
            scanf("%d", &control);
            getchar();

            switch (control)
            {
            case 1:
                  HistoryDestination = ReadFile(HistoryDestination);
                  break;
            case 2:
                  PrintHistory(HistoryDestination);
                  break;
            case 3:
                  SearchDestination(HistoryDestination);
                  break;
            case 4:
                  TimeSearchDestination(HistoryDestination);
                  break;
            case 5:
                  COVID19_Trace(HistoryDestination);
                  break;
            case 6:
                  freeMemory(HistoryDestination);
                  printf("Cam on ban da su dung chuong trinh!\n");
                  return 0;
            default:
                  printf("Vui long nhap dung dinh dang!\n");
                  break;
            }
      }
}