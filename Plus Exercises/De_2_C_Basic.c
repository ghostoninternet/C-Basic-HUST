#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 256

typedef struct SanPham
{
      int maSP;
      char ten[MAX_LENGTH];
      int gia;
      int soluong;

      struct SanPham * next;
} SP;

typedef struct QuanLySanPham
{
      char ten_sanpham[MAX_LENGTH];
      int count;
      struct QuanLySanPham * left;
      struct QuanLySanPham * right;
}QLSP;

SP * makeNode(int Ma_SP, char *ten, int Gia_SP, int So_Luong)
{
      SP * newNode = (SP *)malloc(sizeof(SP));
      newNode->maSP = Ma_SP;
      newNode->gia = Gia_SP;
      newNode->soluong = So_Luong;
      strcpy(newNode->ten, ten);
      newNode->next = NULL;
      
      return newNode;
}

SP * insert_at_head(SP * head, int Ma_SP, char *ten, int Gia_SP, int So_Luong)
{
      if(head == NULL)
      {
            return makeNode(Ma_SP, ten, Gia_SP, So_Luong);
      }

      SP * p = makeNode(Ma_SP, ten, Gia_SP, So_Luong);
      p->next = head;
      return p;
}

void printList(SP * head)
{
      if(head == NULL)
      {
            printf("Danh sach trong!\n");
            return;
      }

      SP * p = head;
      int i = 1;
      while(p != NULL)
      {
            printf("%d %d %d %d %s\n", i, p->maSP, p->gia, p->soluong, p->ten);
            i++;
            p = p->next;
      }
}

SP * Doc_San_Pham(SP * head)
{
      int Ma_SP;
      char ten[MAX_LENGTH];
      int Gia_SP;
      int So_Luong;

      FILE *San_Pham;
      if((San_Pham = fopen("sanpham.txt", "r")) == NULL)
      {
            printf("Error reading file!\n");
            exit(1);
      }

      do
      {
            fscanf(San_Pham, "%d", &Ma_SP);
            fgetc(San_Pham);

            if(feof(San_Pham) != 0)
            {
                  break;
            }

            fscanf(San_Pham, "%d", &Gia_SP);
            fgetc(San_Pham);

            fscanf(San_Pham, "%d", &So_Luong);
            fgetc(San_Pham);

            fgets(ten, MAX_LENGTH, San_Pham);
            if(ten[strlen(ten) - 1] == 10)
            {
                  ten[strlen(ten) - 1] = '\0';
            }
            //printf("%d %d %d %s\n", Ma_SP, Gia_SP, So_Luong, ten);

            head = insert_at_head(head, Ma_SP, ten, Gia_SP, So_Luong);
      } while (feof(San_Pham) == 0);
      fclose(San_Pham);
      //printList(head);
      return head;
}

void Nhap_San_Pham()
{
      FILE *San_Pham;
      if ((San_Pham = fopen("sanpham.txt", "w")) == NULL)
      {
            printf("Error writing file!\n");
            exit(1);
      }

      int Ma_SP;
      char ten[MAX_LENGTH];
      int Gia_SP;
      int So_Luong;
      int prev_Ma_SP = 0;

      while (1)
      {
            printf("Hay nhap ma san pham: ");
            scanf("%d", &Ma_SP);
            if (prev_Ma_SP != 0 && Ma_SP != 0)
            {
                  if (prev_Ma_SP > Ma_SP)
                  {
                        while (prev_Ma_SP > Ma_SP)
                        {
                              printf("Ma san pham sau phai lon hon ma san pham truoc (%d). Yeu cau nhap lai!\n", prev_Ma_SP);
                              printf("Hay nhap ma san pham: ");
                              scanf("%d", &Ma_SP);
                        }
                  }
            }
            
            if (Ma_SP == 0)
            {
                  break;
            }
            else
            {
                  prev_Ma_SP = Ma_SP;
            }
            fflush(stdin);

            printf("Hay nhap ten san pham: ");
            gets(ten);

            do
            {
                  printf("Hay nhap gia san pham: ");
                  scanf("%d", &Gia_SP);
                  if (Gia_SP <= 0)
                  {
                        printf("Gia san pham phai la so duong! Yeu cau nhap lai!\n");
                  }
            } while (Gia_SP <= 0);

            do
            {
                  printf("Hay nhap so luong san pham: ");
                  scanf("%d", &So_Luong);
                  if (So_Luong < 0)
                  {
                        printf("So luong san pham phai la so khong am! Yeu cau nhap lai!\n");
                  }

            } while (So_Luong < 0);
            fprintf(San_Pham, "%d %d %d %s\n", Ma_SP, Gia_SP, So_Luong, ten);
      }

      fclose(San_Pham);
}

void FreeNode(SP * head)
{
      SP * p;
      while(head->next != NULL)
      {
            p = head;
            head = head->next;
            free(p); 
      }
      free(head);
}

SP * insert_in_order(SP * head, int Ma_SP, int Gia, int So_Luong, char *ten)
{
      if(head == NULL)
      {
            return makeNode(Ma_SP, ten, Gia, So_Luong);
      }

      SP * p = makeNode(Ma_SP, ten, Gia, So_Luong);
      SP * q = head;
      while(q != NULL)
      {
            if(q == head && (q->gia >= p->gia))
            {
                  p->next = q;
                  return p;
            }

            if(q->next == NULL)
            {
                  q->next = p;
                  return head;
            }

            if((q->gia <= p->gia) && (p->gia <= q->next->gia))
            {
                  break;
            }
            
            q = q->next;
      }

      p->next = q->next;
      q->next = p;
      return head;
}

SP * Sap_Xep_Danh_Sach(SP * head)
{
      SP * p = head;
      SP * newHead = NULL;

      while(p != NULL)
      {
            newHead = insert_in_order(newHead, p->maSP, p->gia, p->soluong, p->ten);
            p = p->next;
      }
      return newHead;
}

void Tinh_Tong(SP * head)
{
      if(head == NULL)
      {
            printf("Danh sach trong!\n");
            return;
      }

      SP * p = head;
      long int sum = 0;
      while(p != NULL)
      {
            sum += p->gia * p->soluong;
            p = p->next;
      }
      printf("Tong tien cac san pham: %ld\n", sum);
}

void Trung_Gia(SP * head)
{
      int length = 1;
      int groups = 0;
      
      SP * p = head;
      while(p->next != NULL)
      {
            if(p->next->gia != p->gia)
            {
                  if(length >= 2)
                  {
                        groups++;
                  }
                  length = 1;
            }
            else
            {
                  length++;
            }
            if(p->next->next == NULL)
            {
                  if(length >= 2)
                  {
                        groups++;
                  }
            }
            p = p->next;
      }
      printf("So luong nhom: %d\n", groups);
}

QLSP * makeTreeNode(char * name)
{
      QLSP * newNode = (QLSP *)malloc(sizeof(QLSP));
      if(newNode == NULL)
      {
            printf("Error allocate memory!\n");
            exit(1);
      }

      strcpy(newNode->ten_sanpham, name);
      newNode->count = 0;
      return newNode;
}

QLSP * InsertNode(QLSP * root, char * name)
{
      if(root == NULL)
      {
            return makeTreeNode(name);
      }
      if(strcmp(root->ten_sanpham, name) > 0)
      {
            root->left = InsertNode(root->left, name);
      }
      else if (strcmp(root->ten_sanpham, name) < 0)
      {
            root->right = InsertNode(root->right, name);
      }
      else if (strcmp(root->ten_sanpham, name) == 0)
      {
            root->count += 1;
      }
      return root;
      
}

void printTrungTen(QLSP * root)
{
      if(root != NULL)
      {
            printTrungTen(root->left);
            if(root->count >= 1)
            {
                  printf("San pham trung ten: %s\n", root->ten_sanpham);
            }
            printTrungTen(root->right);
      }
}

void FreeTree(QLSP * root)
{
      if(root != NULL)
      {
            FreeTree(root->left);
            FreeTree(root->right);
            free(root);
      }
}

void TrungTen(SP * head)
{
      QLSP * CaySanPham = NULL;
      while(head != NULL)
      {
            CaySanPham = InsertNode(CaySanPham, head->ten);
            head = head->next;
      }
      printTrungTen(CaySanPham);
      FreeTree(CaySanPham);
}

int main()
{
      SP * Cua_Hang = NULL;
      //Nhap_San_Pham();
      Cua_Hang = Doc_San_Pham(Cua_Hang);
      printList(Cua_Hang);
      Cua_Hang = Sap_Xep_Danh_Sach(Cua_Hang);
      printf("\n");
      printList(Cua_Hang);
      Tinh_Tong(Cua_Hang);
      Trung_Gia(Cua_Hang);
      TrungTen(Cua_Hang);
      FreeNode(Cua_Hang);
      return 0;
}