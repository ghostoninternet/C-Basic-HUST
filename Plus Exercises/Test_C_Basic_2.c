#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct Computers
{
      int ID;
      char CPU[3];
      int RAM;
      struct Computers *next;
} Computers;

Computers *CreateComputer(char *CPU, int RAM)
{
      Computers *NewComputer = (Computers *)malloc(sizeof(Computers));
      if (NewComputer == NULL)
      {
            printf("In function CreateComputer error allocate memory!\n");
            exit(1);
      }

      strcpy(NewComputer->CPU, CPU);
      NewComputer->RAM = RAM;
      NewComputer->ID = 1;
      NewComputer->next = NULL;

      return NewComputer;
}

Computers *AddComputer(Computers *head, char *CPU, int RAM)
{
      if (head == NULL)
      {
            return CreateComputer(CPU, RAM);
      }

      Computers *NewComputer = CreateComputer(CPU, RAM);
      Computers *p = head;
      while (p->next != NULL)
      {
            p = p->next;
      }
      p->next = NewComputer;
      NewComputer->ID = p->ID + 1;
      return head;
}

Computers *LoadDataFiles(Computers *head)
{
      int n;
      char CPU[3];
      int RAM;

      char filename[20];
      printf("Enter filename: ");
      gets(filename);
      FILE *COMPUTER;
      if ((COMPUTER = fopen(filename, "r")) == NULL)
      {
            printf("File khong ton tai!\n");
            return head;
      }

      Computers *count = head;
      while (count != NULL)
      {
            if (count->ID == 20)
            {
                  printf("Danh sach da day, khong them duoc\n");
                  return head;
            }
            count = count->next;
      }

      fscanf(COMPUTER, "%d", &n);
      fgetc(COMPUTER);
      for (int i = 1; i <= n; i++)
      {
            fscanf(COMPUTER, "%s    %d", CPU, &RAM);
            head = AddComputer(head, CPU, RAM);
      }
      printf("So may vua them: %d\n", n);
      fclose(COMPUTER);
      return head;
}

void printList(Computers *head)
{
      while (head != NULL)
      {
            printf("%d\t%s\t%d\n", head->ID, head->CPU, head->RAM);
            head = head->next;
      }
}

int check_CPU_Name(char *CPU)
{
      if (strlen(CPU) != 2)
      {
            printf("Strlen != 2\n");
            return 1;
      }
      if (CPU[0] != 'i' && CPU[0] != 'I')
      {
            printf("CPU[0]\n");
            return 1;
      }
      if (CPU[1] != '3' && CPU[1] != '5' && CPU[1] != '7')
      {
            printf("CPU[1]\n");
            return 1;
      }
      return 0;
}

Computers *UpdateCPU_Info(Computers *head)
{
      int N = 0;
      Computers *p = head;
      while (p != NULL)
      {
            N++;
            p = p->next;
      }

      int input_ID;
      do
      {
            printf("Hay nhap ID (1 <= ID <= %d) cua CPU can tim: ", N);
            scanf("%d", &input_ID);
            getchar();
            if (input_ID < 1 || input_ID > N)
            {
                  printf("ID vuot qua gioi han. Vui long nhap lai!\n");
            }
      } while (input_ID < 1 || input_ID > N);

      Computers *q = head;
      int flag = 0;
      int out = 0;
      char newCPU[5];
      while (q != NULL)
      {
            if (flag == 0)
            {
                  if (q->ID == input_ID)
                  {
                        flag = 1;
                        do
                        {
                              printf("ID: %d Ten CPU cu: %s\n", q->ID, q->CPU);
                              printf("ID: %d Ten CPU moi: ", q->ID);
                              gets(newCPU);
                              if (strcmp(newCPU, "STOP") == 0)
                              {
                                    out = 1;
                                    break;
                              }
                              if (check_CPU_Name(newCPU))
                              {
                                    printf("Dinh dang ten CPU khong hop le. Vui long nhap lai!\n");
                              }
                        } while (check_CPU_Name(newCPU));
                        if (strcmp(newCPU, "STOP") != 0)
                              strcpy(q->CPU, newCPU);
                  }
            }
            else if (flag == 1)
            {
                  do
                  {
                        printf("ID: %d Ten CPU cu: %s\n", q->ID, q->CPU);
                        printf("ID: %d Ten CPU moi: ", q->ID);
                        gets(newCPU);
                        if (strcmp(newCPU, "STOP") == 0)
                        {
                              out = 1;
                              break;
                        }
                        if (check_CPU_Name(newCPU))
                        {
                              printf("Dinh dang ten CPU khong hop le. Vui long nhap lai!\n");
                        }
                  } while (check_CPU_Name(newCPU));
                  if (strcmp(newCPU, "STOP") != 0)
                        strcpy(q->CPU, newCPU);
            }

            if (out == 1)
            {
                  break;
            }

            q = q->next;
      }
      return head;
}

int RAM_check(int RAM)
{
      int Value[6] = {1, 2, 4, 8, 16, 32};
      for (int i = 0; i < 6; i++)
      {
            if (RAM == Value[i])
                  return 0;
      }
      return 1;
}

Computers *RAM_Update(Computers *head)
{
      int N = 0;
      Computers *p = head;
      while (p != NULL)
      {
            N++;
            p = p->next;
      }

      int input_ID;
      do
      {
            printf("Hay nhap ID (1 <= ID <= %d) cua RAM can tim: ", N);
            scanf("%d", &input_ID);
            getchar();
            if (input_ID < 1 || input_ID > N)
            {
                  printf("ID vuot qua gioi han. Vui long nhap lai!\n");
            }
      } while (input_ID < 1 || input_ID > N);

      Computers *q = head;
      int flag = 0;
      int out = 0;
      int newRAM;

      while (q != NULL)
      {
            if (flag == 0)
            {
                  if (q->ID == input_ID)
                  {
                        flag = 1;
                        do
                        {
                              printf("Cap nhat RAM <Nhan so 0 de ngung cap nhat>\n");
                              printf("ID %d CPU %s RAM cu: %d\n", q->ID, q->CPU, q->RAM);
                              printf("ID %d CPU %s RAM moi: ", q->ID, q->CPU);
                              scanf("%d", &newRAM);
                              getchar();
                              if (newRAM == 0)
                              {
                                    out = 1;
                                    break;
                              }
                              if (RAM_check(newRAM))
                              {
                                    printf("Dung luong RAM khong hop le. Vui long nhap lai!\n");
                              }
                        } while (RAM_check(newRAM));
                        if (newRAM != 0)
                              q->RAM = newRAM;
                  }
            }
            else
            {
                  do
                  {
                        printf("Cap nhat RAM <Nhan so 0 de ngung cap nhat>\n");
                        printf("ID %d CPU %s RAM cu :%d\n", q->ID, q->CPU, q->RAM);
                        printf("ID %d CPU %s RAM moi : ", q->ID, q->CPU);
                        scanf("%d", &newRAM);
                        getchar();
                        if (newRAM == 0)
                        {
                              out = 1;
                              break;
                        }
                        if (RAM_check(newRAM))
                        {
                              printf("Dung luong RAM khong hop le. Vui long nhap lai!\n");
                        }
                  } while (RAM_check(newRAM));
                  if (newRAM != 0)
                        q->RAM = newRAM;
            }

            if (out == 1)
                  break;
            q = q->next;
      }
      printList(head);
      return head;
}

void SearchComputer(Computers *head)
{
      int control;
      int RAM;
      char search_CPU[3];
      int found = 0;
      do
      {
            printf("1. Tim kiem theo ten CPU\n");
            printf("2. Tim kiem theo dung luong RAM\n");
            printf("Hay chon phuong thuc tim kiem: ");
            scanf("%d", &control);
            getchar();
            if (control != 1 && control != 2)
            {
                  printf("Dinh dang khong hop le! Vui long nhap lai\n");
            }
      } while (control != 1 && control != 2);

      if (control == 1)
      {
            do
            {
                  printf("Hay nhap ten CPU can tim: ");
                  gets(search_CPU);
                  if (check_CPU_Name(search_CPU))
                  {
                        printf("Dinh dang ten CPU khong hop le! Vui long nhap lai\n");
                  }
            } while (check_CPU_Name(search_CPU));

            if (islower(search_CPU[0]))
                  search_CPU[0] -= 32;

            Computers *p = head;
            while (p != NULL)
            {
                  if (strcmp(p->CPU, search_CPU) == 0)
                  {
                        found = 1;
                        printf("ID %d CPU %s RAM %d\n", p->ID, p->CPU, p->RAM);
                  }
                  p = p->next;
            }
      }
      else if (control == 2)
      {
            do
            {
                  printf("Hay nhap dung luong RAM can tim: ");
                  scanf("%d", &RAM);
                  getchar();
                  if (RAM_check(RAM))
                  {
                        printf("Dung luong RAM khong hop le! Vui long nhap lai!\n");
                  }
            } while (RAM_check(RAM));

            Computers *p = head;
            while (p != NULL)
            {
                  if (p->RAM == RAM)
                  {
                        found = 1;
                        printf("ID %d CPU %s RAM %d\n", p->ID, p->CPU, p->RAM);
                  }
                  p = p->next;
            }
      }

      if (found == 0)
      {
            printf("Khong tim thay may tinh can tim!\n");
      }
}

void freeList(Computers * head)
{
      Computers * p;
      while(head != NULL)
      {
            p = head;
            head = head->next;
            free(p);
      }
}

int main()
{
      int control;
      Computers *QuanLy_MayTinh = NULL;
      while (1)
      {
            printf("===Program for management computers===\n");
            printf("1. Load Data Files\n");
            printf("2. Update CPU Info\n");
            printf("3. Update RAM Info\n");
            printf("4. Search\n");
            printf("5. Quit\n");
            printf("Hay chon 1 trong 5 chuc nang tren: ");
            scanf("%d", &control);
            getchar();

            switch (control)
            {
            case 1:
                  QuanLy_MayTinh = LoadDataFiles(QuanLy_MayTinh);
                  printList(QuanLy_MayTinh);
                  break;
            case 2:
                  QuanLy_MayTinh = UpdateCPU_Info(QuanLy_MayTinh);
                  printList(QuanLy_MayTinh);
                  break;
            case 3:
                  QuanLy_MayTinh = RAM_Update(QuanLy_MayTinh);
                  break;
            case 4:
                  SearchComputer(QuanLy_MayTinh);
                  break;
            case 5:
                  freeList(QuanLy_MayTinh);
                  return 0;
            default:
                  printf("Vui long nhap dung dinh dang\n");
                  break;
            }
      }
}