#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct NodeSP
{
      char ma_sp[10];
      char ten_sp[250];
      char hang_sx[100];
      int soluong;
      struct NodeSP *next;
} NSP;

NSP *makeNode(NSP value)
{
      NSP *p = (NSP *)malloc(sizeof(NSP));
      strcpy(p->ma_sp, value.ma_sp);
      strcpy(p->ten_sp, value.ten_sp);
      strcpy(p->hang_sx, value.hang_sx);
      p->soluong = value.soluong;
      p->next = NULL;
      return p;
}

NSP *insertLast(NSP *List, NSP value)
{
      if (List == NULL)
      {
            List = makeNode(value);
            return List;
      }

      NSP *p = List;
      NSP *q = makeNode(value);

      while (p->next != NULL)
      {
            p = p->next;
      }
      p->next = q;

      return List;
}

NSP *deleteNode(NSP *List, NSP *p)
{
      if (List == p)
      {
            List = List->next;
            return List;
      }
      NSP *q = List;
      while (q->next != p)
      {
            q = q->next;
      }
      q->next = p->next;
      free(p);
      return List;
}

NSP *Lay_Thong_Tin(NSP *List)
{
      char *filename = "C:\\Users\\admin\\OneDrive - Hanoi University of Science and Technology\\Documents\\C Programming\\.vscode\\C Basic\\Text Examples\\Quan Ly San Pham.txt";
      FILE *SP1;
      if ((SP1 = fopen(filename, "r")) == NULL)
      {
            printf("Can't open file\n");
            exit(1);
      }

      NSP value;
      int newline;
      do
      {
            fscanf(SP1, "%s", value.ma_sp);
            newline = fgetc(SP1);
            fscanf(SP1, "%[^\n]%*c", value.ten_sp);
            fscanf(SP1, "%[^\n]%*c", value.hang_sx);
            fscanf(SP1, "%d", &value.soluong);
            newline = fgetc(SP1);

            List = insertLast(List, value);
      } while (feof(SP1) == 0);

      return List;
}

NSP *Bo_Sung(NSP *List)
{
      char *filename = "C:\\Users\\admin\\OneDrive - Hanoi University of Science and Technology\\Documents\\C Programming\\.vscode\\C Basic\\Text Examples\\Bo Sung San Pham.txt";
      FILE *BoSung;
      if ((BoSung = fopen(filename, "r")) == NULL)
      {
            printf("Can't open file\n");
            exit(1);
      }

      NSP value;
      int newline;
      int flag = 0;
      do
      {
            fscanf(BoSung, "%s", value.ma_sp);
            newline = fgetc(BoSung);
            fscanf(BoSung, "%[^\n]%*c", value.ten_sp);
            fscanf(BoSung, "%[^\n]%*c", value.hang_sx);
            fscanf(BoSung, "%d", &value.soluong);
            newline = fgetc(BoSung);

            NSP *p = List;
            while (p != NULL)
            {
                  if (strcmp(p->ma_sp, value.ma_sp) == 0)
                  {
                        flag = 1;
                        p->soluong += value.soluong;
                        break;
                  }
                  p = p->next;
            }
            if (flag == 0)
            {
                  List = insertLast(List, value);
            }
            else
            {
                  flag = 0;
            }

      } while (feof(BoSung) == 0);
      return List;
}

NSP *Xuat_Kho(NSP *List)
{
      char code[10];
      int luong_san_pham;

      printf("Hay nhap ma san pham ban muon xuat: ");
      gets(code);
      fflush(stdin);
      printf("Hay nhap so luong: ");
      scanf("%d", &luong_san_pham);
      fflush(stdin);

      NSP *p = List;
      int flag = 0;
      while (p != NULL)
      {
            if (strcmp(p->ma_sp, code) == 0)
            {
                  flag = 1;
                  printf("So luong san pham ma %s con trong kho: %d\n", p->ma_sp, p->soluong);
                  if (p->soluong > luong_san_pham)
                  {
                        p->soluong -= luong_san_pham;
                        return List;
                  }
                  else if (p->soluong < luong_san_pham)
                  {
                        printf("Khong du so luong de xuat kho\n");
                        return List;
                  }
                  else if (p->soluong == luong_san_pham)
                  {
                        deleteNode(List, p);
                        return List;
                  }
            }
            p = p->next;
      }
      if (flag == 0)
      {
            printf("Khong tim thay san pham o trong kho\n");
            return List;
      }
}

void Check_San_Pham(NSP *List)
{
      char code[10];
      printf("Hay nhap ma san pham ban muon check: ");
      gets(code);
      fflush(stdin);
      int flag = 0;

      while (List != NULL)
      {
            if (strcmp(List->ma_sp, code) == 0)
            {
                  flag = 1;
                  printf("San pham van con trong kho\n");
                  printf("Thong tin san pham:\n");
                  printf("%s\n%s\n%s\n%d\n", List->ma_sp, List->ten_sp, List->hang_sx, List->soluong);
            }
            List = List->next;
      }
      if (flag == 0)
      {
            printf("San pham khong co trong kho\n");
      }
}

void printList(NSP *List)
{
      for(int i = 1; i <= 125; i++)
      {
            printf("_");
      }
      printf("\n");

      printf("%-5s|%-15s|%-40s|%-40s|%-20s|\n", "STT", "Ma San Pham", "Ten San Pham", "Hang San Xuat", "So Luong");
      
      for (int i = 1; i <= 120; i++)
      {
            printf("-");
            if (i == 5 || i == 20|| i == 60 || i == 100 || i == 120)
            {
                  printf("|");
            }
      }
      printf("\n");

      int count = 1;
      while (List != NULL)
      {
            printf("%-5d|%-15s|%-40s|%-40s|%-20d|\n", count, List->ma_sp, List->ten_sp, List->hang_sx, List->soluong);
            for (int i = 1; i <= 120; i++)
            {
                  printf("-");
                  if (i == 5 || i == 20 || i == 60 || i == 100 || i == 120)
                  {
                        if(List->next != NULL)
                        {
                              printf("|");
                        }
                        else
                        {
                              printf("-");
                        }
                        
                  }
            }
            printf("\n");
            List = List->next;
            count++;
      }
}

void Ghi_Vao_File(NSP *List)
{
      char *filename = "C:\\Users\\admin\\OneDrive - Hanoi University of Science and Technology\\Documents\\C Programming\\.vscode\\C Basic\\Text Examples\\Quan Ly San Pham 2.txt";
      FILE *SP2;
      if ((SP2 = fopen(filename, "w")) == NULL)
      {
            printf("Can't create file\n");
            exit(1);
      }
      while (List != NULL)
      {
            fprintf(SP2, "%s\n%s\n%s\n%d\n", List->ma_sp, List->ten_sp, List->hang_sx, List->soluong);
            List = List->next;
      }
}

int main()
{
      NSP *DanhSach = NULL;
      DanhSach = Lay_Thong_Tin(DanhSach);
      int choose;
      while (1)
      {
            for (int i = 0; i < 10; i++)
            {
                  printf("=");
            }
            printf("CHAO MUNG DEN VOI KHO QUAN LY SAN PHAM");
            for (int i = 0; i < 10; i++)
            {
                  printf("=");
            }
            printf("\n");

            printf("1. BO SUNG VAO KHO\n");
            printf("2. XUAT KHO\n");
            printf("3. KIEM TRA SAN PHAM TRONG KHO\n");
            printf("4. SHOW SAN PHAM\n");
            printf("5. GHI SAN PHAM RA FILE\n");
            printf("6. THOAT CHUONG TRINH\n");
            printf("HAY CHON MOT CHUC NANG: ");
            scanf("%d", &choose);
            fflush(stdin);

            if (choose >= 1 && choose <= 6)
            {
                  if (choose == 1)
                  {
                        DanhSach = Bo_Sung(DanhSach);
                  }
                  if (choose == 2)
                  {
                        DanhSach = Xuat_Kho(DanhSach);
                  }
                  if (choose == 3)
                  {
                        Check_San_Pham(DanhSach);
                  }
                  if (choose == 4)
                  {
                        printList(DanhSach);
                  }
                  if (choose == 5)
                  {
                        Ghi_Vao_File(DanhSach);
                  }
                  if (choose == 6)
                  {
                        printf("HAVE A NICE DAY!");
                        return 0;
                  }
            }
            else
            {
                  printf("VUI LONG NHAP DUNG DINH DANH\n");
            }
      }
      return 0;
}