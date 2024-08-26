#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 256

typedef struct ThongTin
{
      char Username[MAX_LENGTH];
      char Password[MAX_LENGTH];
      float Diem;

      struct ThongTin *left;
      struct ThongTin *right;
} TT;

///////////////////////////////////////////////////////////////////////////////////////////////////
/*Các hàm làm việc với cây bao gồm:
1. makeNode --> Tạo nút mới cho cây
2. insertNode --> Thêm nút mới cho cây
3. printTree --> In cây theo thứ tự giữa
4. findMin --> Tìm kế sau của nút x
5. Delete --> Xóa nút x
*/
TT *makeNode(char *name, char *password, float diem)
{
      TT *p = (TT *)malloc(sizeof(TT));
      if (p == NULL)
      {
            printf("Error allocate memory!\n");
            exit(1);
      }

      strcpy(p->Username, name);
      strcpy(p->Password, password);
      p->Diem = diem;
      p->left = NULL;
      p->right = NULL;

      return p;
}

TT *insertNode(TT *root, char *name, char *password, float diem)
{
      if (root == NULL)
      {
            return makeNode(name, password, diem);
      }
      if (strcmp(root->Username, name) > 0)
      {
            root->left = insertNode(root->left, name, password, diem);
      }
      if (strcmp(root->Username, name) < 0)
      {
            root->right = insertNode(root->right, name, password, diem);
      }
      return root;
}

void printTree(TT *root)
{
      if (root != NULL)
      {
            printTree(root->left);
            printf("%s\t%s\t%.2f\n", root->Username, root->Password, root->Diem);
            printTree(root->right);
      }
}

TT *find_min(TT *root)
{
      if (root != NULL)
      {
            if (root->left == NULL)
            {
                  return root;
            }
            while (root->left != NULL)
            {
                  root = root->left;
            }
            return root;
      }
}

TT *Delete(TT *root, char *name)
{
      TT *tmp;
      if (strcmp(name, "Admin") == 0)
      {
            printf("Khong the xoa Admin\n");
            return root;
      }
      if (root == NULL)
      {
            printf("Khong tim thay sinh vien\n");
      }
      else if (strcmp(root->Username, name) > 0)
      {
            root->left = Delete(root->left, name);
      }
      else if (strcmp(root->Username, name) < 0)
      {
            root->right = Delete(root->right, name);
      }
      else
      {
            if (root->left && root->right)
            {
                  tmp = find_min(root->right);
                  strcpy(root->Username, tmp->Username);
                  strcpy(root->Password, tmp->Password);
                  root->Diem = tmp->Diem;
                  root->right = Delete(root->right, root->Username);
                  printf("Thong tin sinh vien da xoa: %s\t%s\t%.2f\n", tmp->Username, tmp->Password, tmp->Diem);
            }
            else
            {
                  tmp = root;
                  if (root->left == NULL)
                  {
                        root = root->right;
                  }
                  else
                  {
                        if (root->right == NULL)
                        {
                              root = root->left;
                        }
                  }
                  printf("Thong tin sinh vien da xoa: %s\t%s\t%.2f\n", tmp->Username, tmp->Password, tmp->Diem);
                  free(tmp);
            }
      }
      return root;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////
/*
Hàm kiểm tra mật khẩu người dùng nhập vào, nếu có thì trả về nút chứa mật khẩu cần tìm, ngược lại thì trả về NULL
*/
TT *CheckPassword(TT *root, char *pass)
{
      if (root != NULL)
      {
            if (strcmp(root->Password, pass) > 0)
            {
                  root = CheckPassword(root->left, pass);
            }
            else if (strcmp(root->Password, pass) < 0)
            {
                  root = CheckPassword(root->right, pass);
            }
      }
      return root;
}
///////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////
/*
Viết thông tin mới cập nhật ra file
*/
void WriteToFile(TT *root, FILE *NewList)
{
      if (root != NULL)
      {
            WriteToFile(root->left, NewList);
            fprintf(NewList, "%s\t%s\t%.2f\n", root->Username, root->Password, root->Diem);
            WriteToFile(root->right, NewList);
      }
}
///////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////
/*
Tìm tên bị trùng trong danh sách sinh viên
*/
TT *TimTenTrung(TT *root, char *name)
{
      if (root != NULL)
      {
            if (strcmp(root->Username, name) > 0)
            {
                  root = TimTenTrung(root->left, name);
            }
            else if (strcmp(root->Username, name) < 0)
            {
                  root = TimTenTrung(root->right, name);
            }
      }
      return root;
}
///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
/*
Thêm một sinh viên mới vào trong danh sách
*/
TT *ThemSinhVienMoi(TT *root)
{
      char ten[MAX_LENGTH];
      char matKhau[MAX_LENGTH];
      float diemSo;

      TT *found = NULL;
      do
      {
            found = root;
            printf("Nhap ten sinh vien: ");
            gets(ten);
            if ((found = TimTenTrung(found, ten)) != NULL)
            {
                  printf("Ten bi trung! Vui long nhap lai\n");
            }
      } while ((found = TimTenTrung(found, ten)) != NULL);

      printf("Nhap mat khau sinh vien: ");
      gets(matKhau);

      printf("Nhap diem so sinh vien: ");
      scanf("%f", &diemSo);
      getchar();

      root = insertNode(root, ten, matKhau, diemSo);
      return root;
}
///////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////
/*
In ra danh sách sinh viên trừ Admin
*/
void printList2(TT *root)
{
      if (root != NULL)
      {
            printList2(root->left);
            if (strcmp(root->Username, "Admin") != 0)
            {
                  printf("%s\t%s\t%.2f\n", root->Username, root->Password, root->Diem);
            }
            printList2(root->right);
      }
}
///////////////////////////////////////////////////////////////////////////////////////////////////


TT *XoaSinhVien(TT *root)
{
      char name[MAX_LENGTH];
      printf("Hay nhap ten sinh vien can xoa: ");
      gets(name);

      root = Delete(root, name);
      return root;
}

void freeTree(TT *freeProfileTree)
{
      if (freeProfileTree != NULL)
      {
            freeTree(freeProfileTree->left);
            freeTree(freeProfileTree->right);
            free(freeProfileTree);
      }
}

TT *GetDatabase(TT *root)
{
      char ten[MAX_LENGTH];
      char matKhau[MAX_LENGTH];
      float diemSo;

      FILE *fileThongTin;
      if ((fileThongTin = fopen("sinhvien.txt", "r")) == NULL)
      {
            printf("Error reading file!\n");
            exit(1);
      }
      while (feof(fileThongTin) == 0)
      {
            fscanf(fileThongTin, "%s", ten);
            fgetc(fileThongTin);

            fscanf(fileThongTin, "%s", matKhau);
            fgetc(fileThongTin);

            fscanf(fileThongTin, "%f", &diemSo);
            fgetc(fileThongTin);

            root = insertNode(root, ten, matKhau, diemSo);
      }
      printTree(root);
      fclose(fileThongTin);
      return root;
}

void Login()
{
      TT *ProfileTree = NULL;
      ProfileTree = GetDatabase(ProfileTree);

      TT *found = NULL;
      char matKhau[MAX_LENGTH];
      int count = 3;
      do
      {
            found = ProfileTree;
            printf("Hay nhap mat khau: ");
            gets(matKhau);
            count--;

            if ((found = CheckPassword(found, matKhau)) == NULL)
            {
                  printf("Nhap sai mat khau! Con %d lan nhap!\n", count);
            }

      } while ((found = CheckPassword(found, matKhau)) == NULL && count > 0);

      if (count == 0)
      {
            printf("Da qua 3 lan nhap mat khau sai!\n");
            exit(1);
      }

      int control;
      char matKhauMoi[MAX_LENGTH];
      char xacNhan[MAX_LENGTH];
      FILE *DanhSachMoi;
      if (strcmp(matKhau, "Admin12") == 0)
      {
            while (1)
            {
                  printf("Chao mung Admin!\n");
                  printf("1. Them mot sinh vien moi\n");
                  printf("2. In ra danh sach sinh vien\n");
                  printf("3. Xoa sinh vien\n");
                  printf("4. Ghi lai vao file du lieu\n");
                  printf("Hay chon 1 trong 4: ");
                  scanf("%d", &control);
                  getchar();

                  if (control == 1)
                  {
                        ProfileTree = ThemSinhVienMoi(ProfileTree);
                  }
                  else if (control == 2)
                  {
                        printList2(ProfileTree);
                  }
                  else if (control == 3)
                  {
                        ProfileTree = XoaSinhVien(ProfileTree);
                  }
                  else if (control == 4)
                  {
                        DanhSachMoi = fopen("sinhvien.txt", "w");
                        if (DanhSachMoi == NULL)
                        {
                              printf("Can't create file\n");
                              exit(1);
                        }
                        WriteToFile(ProfileTree, DanhSachMoi);
                        fclose(DanhSachMoi);
                        break;
                        // freeTree(ProfileTree);
                  }
                  else
                  {
                        printf("Vui long nhap dung dinh dang!\n");
                  }
            }
      }
      else
      {
            while (1)
            {
                  printf("Chao mung sinh vien %s\n", found->Username);
                  printf("1. Xem diem\n");
                  printf("2. Thay doi mat khau\n");
                  printf("3. Ghi vao file du lieu\n");
                  printf("Hay chon 1 trong 3: ");
                  scanf("%d", &control);
                  getchar();

                  if (control == 1)
                  {
                        printf("Diem cua sinh vien %s: %.2f\n", found->Username, found->Diem);
                  }
                  else if (control == 2)
                  {
                        do
                        {
                              printf("Hay nhap mat khau moi: ");
                              gets(matKhauMoi);
                              if (strlen(matKhauMoi) < 6)
                              {
                                    printf("Mat khau qua ngan. Hay nhap mat khau it nhat 6 ki tu\n");
                              }
                        } while (strlen(matKhauMoi) < 6);

                        do
                        {
                              printf("Hay xac nhan mat khau moi: ");
                              gets(xacNhan);
                              if (strcmp(xacNhan, matKhauMoi) != 0)
                              {
                                    printf("Mat khau khong khop! Vui long nhap lai!\n");
                              }
                        } while (strcmp(xacNhan, matKhauMoi) != 0);
                        strcpy(found->Password, matKhauMoi);
                  }
                  else if (control == 3)
                  {
                        DanhSachMoi = fopen("sinhvien.txt", "w");
                        if (DanhSachMoi == NULL)
                        {
                              printf("Can't create file\n");
                              exit(1);
                        }
                        WriteToFile(ProfileTree, DanhSachMoi);
                        fclose(DanhSachMoi);
                        break;
                        // freeTree(ProfileTree);
                  }
                  else
                  {
                        printf("Vui long nhap dung dinh dang!\n");
                  }
            }
      }
}

int main()
{
      int control;
      while (1)
      {
            printf("Chuong trinh quan ly thong tin sinh vien\n");
            printf("1. Dang Nhap\n");
            printf("2. Thoat\n");
            printf("Hay nhap lua chon: ");
            scanf("%d", &control);
            getchar();
            switch (control)
            {
            case 1:
                  Login();
                  break;
            case 2:
                  printf("Cam on ban da su dung chuong trinh\n");
                  return 0;
            default:
                  printf("Vui long nhap lua chon 1 hoac 2\n");
                  break;
            }
      }
}