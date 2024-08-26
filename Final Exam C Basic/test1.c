#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 256

typedef struct DatPhong
{
      char MaYeuCau[MAX_LENGTH];
      int SoLuong;
      int SoPhong;
      char MaKS[MAX_LENGTH];
      char NgayDat[MAX_LENGTH];
      int TreEm;

      struct DatPhong *next;
} DatPhong;

typedef struct Cay_DatPhong
{
      char MaYeuCau[MAX_LENGTH];
      int SoLuong;
      int SoPhong;
      char MaKS[MAX_LENGTH];
      char NgayDat[MAX_LENGTH];
      int TreEm;

      struct Cay_DatPhong *left;
      struct Cay_DatPhong *right;
} Cay_DatPhong;

void freeTree(Cay_DatPhong * root)
{
      if(root != NULL)
      {
            freeTree(root->left);
            freeTree(root->right);
            free(root);
      }
}

void freeList(DatPhong * head)
{
      DatPhong * p;
      while(head != NULL)
      {
            p = head;
            head = head->next;
            free(p);
      }
}

Cay_DatPhong *CreateNodes(char *MaYeuCau, int SoLuong, int SoPhong, char *MaKS, char *NgayDat, int TreEm)
{
      Cay_DatPhong *NewRoom = (Cay_DatPhong *)malloc(sizeof(Cay_DatPhong));
      if (NewRoom == NULL)
      {
            printf("Error allocate memroy\n");
            exit(1);
      }

      strcpy(NewRoom->MaYeuCau, MaYeuCau);
      strcpy(NewRoom->MaKS, MaKS);
      strcpy(NewRoom->NgayDat, NgayDat);
      NewRoom->SoLuong = SoLuong;
      NewRoom->SoPhong = SoPhong;
      NewRoom->TreEm = TreEm;
      NewRoom->left = NULL;
      NewRoom->right = NULL;

      return NewRoom;
}

Cay_DatPhong *InsertNodes(Cay_DatPhong *root, char *MaYeuCau, int SoLuong, int SoPhong, char *MaKS, char *NgayDat, int TreEm)
{
      if (root == NULL)
      {
            return CreateNodes(MaYeuCau, SoLuong, SoPhong, MaKS, NgayDat, TreEm);
      }
      if (strcmp(root->MaYeuCau, MaYeuCau) > 0)
      {
            root->left = InsertNodes(root->left, MaYeuCau, SoLuong, SoPhong, MaKS, NgayDat, TreEm);
      }
      else if (strcmp(root->MaYeuCau, MaYeuCau) < 0)
      {
            root->right = InsertNodes(root->right, MaYeuCau, SoLuong, SoPhong, MaKS, NgayDat, TreEm);
      }
}

Cay_DatPhong *SearchNodes(Cay_DatPhong *root, char *MaYeuCau)
{
      if (root == NULL)
      {
            return root;
      }
      if (strcmp(root->MaYeuCau, MaYeuCau) == 0)
      {
            return root;
      }
      if (strcmp(root->MaYeuCau, MaYeuCau) > 0)
      {
            SearchNodes(root->left, MaYeuCau);
      }
      else if (strcmp(root->MaYeuCau, MaYeuCau) < 0)
      {
            SearchNodes(root->right, MaYeuCau);
      }
}

Cay_DatPhong *FindMin(Cay_DatPhong *root)
{
      Cay_DatPhong *p = root;

      while (p && p->left != NULL)
      {
            p = p->left;
      }

      return p;
}

Cay_DatPhong *DeleteNode(Cay_DatPhong *root, char *MaYeuCau)
{
      if (root == NULL)
      {
            return root;
      }
      if (strcmp(root->MaYeuCau, MaYeuCau) > 0)
      {
            root->left = DeleteNode(root->left, MaYeuCau);
      }
      else if (strcmp(root->MaYeuCau, MaYeuCau) < 0)
      {
            root->right = DeleteNode(root->right, MaYeuCau);
      }
      else
      {
            if (root->left == NULL)
            {
                  Cay_DatPhong *temp = root->right;
                  free(root);
                  return temp;
            }
            else if (root->right == NULL)
            {
                  Cay_DatPhong *temp = root->left;
                  free(root);
                  return temp;
            }

            Cay_DatPhong *temp = FindMin(root->right);
            strcpy(root->MaYeuCau, temp->MaYeuCau);
            root->right = DeleteNode(root->right, temp->MaYeuCau);
      }
      return root;
}

void sub_printTree(Cay_DatPhong *root)
{
      if (root != NULL)
      {
            sub_printTree(root->left);
            printf("%s %d %d %s %s %d\n", root->MaYeuCau, root->SoLuong, root->SoPhong, root->MaKS, root->NgayDat, root->TreEm);
            sub_printTree(root->right);
      }
}

DatPhong *CreateRoom(char *MaYeuCau, int SoLuong, int SoPhong, char *MaKS, char *NgayDat, int TreEm)
{
      DatPhong *NewRoom = (DatPhong *)malloc(sizeof(DatPhong));
      if (NewRoom == NULL)
      {
            printf("Error allocate memroy\n");
            exit(1);
      }

      strcpy(NewRoom->MaYeuCau, MaYeuCau);
      strcpy(NewRoom->MaKS, MaKS);
      strcpy(NewRoom->NgayDat, NgayDat);
      NewRoom->SoLuong = SoLuong;
      NewRoom->SoPhong = SoPhong;
      NewRoom->TreEm = TreEm;
      NewRoom->next = NULL;

      return NewRoom;
}

DatPhong *InsertRoom(DatPhong *head, char *MaYeuCau, int SoLuong, int SoPhong, char *MaKS, char *NgayDat, int TreEm)
{
      if (head == NULL)
      {
            return CreateRoom(MaYeuCau, SoLuong, SoPhong, MaKS, NgayDat, TreEm);
      }

      DatPhong *NewRoom = CreateRoom(MaYeuCau, SoLuong, SoPhong, MaKS, NgayDat, TreEm);
      DatPhong *p = head;
      while (p->next != NULL)
      {
            p = p->next;
      }
      p->next = NewRoom;
      return head;
}

void printList(DatPhong *head)
{
      while (head != NULL)
      {
            printf("%s %d %d %s %s %d\n", head->MaYeuCau, head->SoLuong, head->SoPhong, head->MaKS, head->NgayDat, head->TreEm);
            head = head->next;
      }
}

DatPhong *ReadFile(DatPhong *head)
{
      FILE *Booking;
      if ((Booking = fopen("booking_orders.txt", "r")) == NULL)
      {
            printf("In function ReadFile error reading file!\n");
            exit(1);
      }

      int N;
      char MaYeuCau[MAX_LENGTH];
      int SoLuong;
      int SoPhong;
      char MaKS[MAX_LENGTH];
      char NgayDat[MAX_LENGTH];
      int TreEm;

      fscanf(Booking, "%d", &N);
      fgetc(Booking);
      for (int i = 1; i <= N; i++)
      {
            fscanf(Booking, "%s %d %d %s %s %d", MaYeuCau, &SoLuong, &SoPhong, MaKS, NgayDat, &TreEm);
            fgetc(Booking);
            head = InsertRoom(head, MaYeuCau, SoLuong, SoPhong, MaKS, NgayDat, TreEm);
      }
      fclose(Booking);
      printf("So luong yeu cau: %d\n", N);
      printList(head);
      return head;
}

void Yeu_Cau_Khong_Hop_Le(DatPhong *head)
{
      DatPhong *p = head;
      int flag = 0;
      int count = 0;
      while (p != NULL)
      {
            if ((p->SoLuong - p->TreEm) < 1)
            {
                  flag = 1;
                  printf("%s %d %d %s %s %d\n", p->MaYeuCau, p->SoLuong, p->SoLuong, p->MaKS, p->NgayDat, p->TreEm);
                  count++;
            }
            p = p->next;
      }
      if (flag == 0)
      {
            printf("Cac yeu cau deu hop le!\n");
      }
      printf("Co %d yeu cau khong hop le!\n", count);
}

Cay_DatPhong *Tao_Cay_Ma_Yeu_Cau(Cay_DatPhong *root, DatPhong *head)
{
      while (head != NULL)
      {
            root = InsertNodes(root, head->MaYeuCau, head->SoLuong, head->SoPhong, head->MaKS, head->NgayDat, head->TreEm);
            head = head->next;
      }
      return root;
}

int check_MaYeuCau(char *code)
{
      for (int i = 0; i < 3; i++)
      {
            if (isalpha(code[i]) == 0)
            {
                  printf("Not alpha!\n");
                  return 1;
            }
      }
      for (int i = 3; i < 7; i++)
      {
            if (isdigit(code[i]) == 0)
            {
                  printf("Not digit!\n");
                  return 1;
            }
      }
      return 0;
}

void Tim_Kiem_MaYeuCau(Cay_DatPhong *root)
{
      Cay_DatPhong *search;
      char MaYeuCau[MAX_LENGTH];

      do
      {
            printf("Hay nhap ma yeu cau can tim kiem: ");
            gets(MaYeuCau);
            if(check_MaYeuCau(MaYeuCau))
            {
                  printf("Sai dinh dang! Hay nhap lai!\n");
            }
      } while (check_MaYeuCau(MaYeuCau));

      search = SearchNodes(root, MaYeuCau);
      if(search == NULL)
      {
            printf("Not found\n");
      }
      else
      {
            printf("%s %d %d %s %s %d\n", search->MaYeuCau, search->SoLuong, search->SoPhong, search->MaKS, search->NgayDat, search->TreEm);
      }
}

int check_SoLuong(int SoLuong, int TreEm)
{
      if(SoLuong < 0 || TreEm < 0)
      {
            return 1;
      }
      else if((SoLuong - TreEm) < 1)
      {
            return 1;
      }
      return 0;
}

Cay_DatPhong * Cap_Nhat_Yeu_Cau(Cay_DatPhong * root)
{
      int SoLuong;
      int TreEm;
      char NgayDat[MAX_LENGTH];
      do
      {
            printf("Hay nhap so luong nguoi di va so luong tre em: ");
            scanf("%d %d", &SoLuong, &TreEm);
            getchar();
            if(check_SoLuong(SoLuong, TreEm))
            {
                  printf("Invalid!\n");
            }
      } while (check_SoLuong(SoLuong, TreEm));
      printf("Nhap ngay thang nam moi: ");
      gets(NgayDat);

      Cay_DatPhong *search;
      char MaYeuCau[MAX_LENGTH];
      do
      {
            printf("Hay nhap ma yeu cau can cap nhat: ");
            gets(MaYeuCau);
            if(check_MaYeuCau(MaYeuCau))
            {
                  printf("Sai dinh dang! Hay nhap lai!\n");
            }
      } while (check_MaYeuCau(MaYeuCau));

      search = SearchNodes(root, MaYeuCau);
      if (search == NULL)
      {
            printf("Not found!\n");
            return root;
      }
      else
      {
            search->SoLuong = SoLuong;
            search->TreEm = TreEm;
            strcpy(search->NgayDat, NgayDat);
            printf("Update!\n");
            return root;
      }
}

Cay_DatPhong * Huy_Yeu_Cau(Cay_DatPhong * root)
{
      Cay_DatPhong *search;
      char MaYeuCau[MAX_LENGTH];

      do
      {
            printf("Hay nhap ma yeu cau can xoa: ");
            gets(MaYeuCau);
            if(check_MaYeuCau(MaYeuCau))
            {
                  printf("Sai dinh dang! Hay nhap lai!\n");
            }
      } while (check_MaYeuCau(MaYeuCau));

      search = SearchNodes(root, MaYeuCau);

      if(search == NULL)
      {
            printf("Not found!\n");
            return root;
      }
      else
      {
            root = DeleteNode(root, MaYeuCau);
            printf("Delete!\n");
            return root;
      }
}

void CountNode(Cay_DatPhong * root, int * N)
{
      if(root != NULL)
      {
            CountNode(root->left, N);
            *N += 1;
            CountNode(root->right, N);
      }
}

void Update(Cay_DatPhong * root, FILE * UpdateFile)
{
      if(root != NULL)
      {
            Update(root->left, UpdateFile);
            fprintf(UpdateFile, "%s %d %d %s %s %d\n", root->MaYeuCau, root->SoLuong, root->SoPhong, root->MaKS, root->NgayDat, root->TreEm);
            Update(root->right, UpdateFile);
      }
}

int main()
{
      int control;
      DatPhong *Info_DatHang = NULL;
      Cay_DatPhong *Tree_Info_DatHang = NULL;
      int count = 0;
      FILE * Booking_Updated;
      while (1)
      {
            printf("Chuong trinh quan ly dat phong\n");
            printf("Vui long chon mot trong cac chuc nang sau\n");
            printf("[1] Doc du lieu tu file log\n");
            printf("[2] Kiem tra so luong yeu cau khong hop le\n");
            printf("[3] Tra cuu theo ma yeu cau\n");
            printf("[4] Thay doi yeu cau\n");
            printf("[5] Huy yeu cau\n");
            printf("[6] Luu dang sach yeu cau ra file\n");
            printf("Lua chon cua ban la: ");
            scanf("%d", &control);
            getchar();

            switch (control)
            {
            case 1:
                  Info_DatHang = ReadFile(Info_DatHang);
                  Tree_Info_DatHang = Tao_Cay_Ma_Yeu_Cau(Tree_Info_DatHang, Info_DatHang);
                  printf("\n\n");
                  sub_printTree(Tree_Info_DatHang);
                  break;
            case 2:
                  Yeu_Cau_Khong_Hop_Le(Info_DatHang);
                  break;
            case 3:
                  Tim_Kiem_MaYeuCau(Tree_Info_DatHang);
                  break;
            case 4:
                  Tree_Info_DatHang = Cap_Nhat_Yeu_Cau(Tree_Info_DatHang);
                  break;
            case 5:
                  Huy_Yeu_Cau(Tree_Info_DatHang);
                  break;
            case 6:
                  CountNode(Tree_Info_DatHang, &count);
                  if((Booking_Updated = fopen("booking_output.txt", "w")) == NULL)
                  {
                        printf("Error writing booking_output.txt\n");
                        exit(1);
                  }
                  fprintf(Booking_Updated, "%d\n", count);
                  Update(Tree_Info_DatHang, Booking_Updated);
                  fclose(Booking_Updated);
                  break;
            default:
                  printf("Thoat Chuong Trinh........");
                  freeList(Info_DatHang);
                  freeTree(Tree_Info_DatHang);
                  return 0;
            }
      }
}