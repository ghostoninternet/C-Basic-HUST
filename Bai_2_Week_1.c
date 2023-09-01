#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int current_device = 0;

typedef struct ThietBi
{
      char ma_thiet_bi[50];
      char ten_thiet_bi[100];
      char nam_san_xuat[5];
      char hang_san_xuat[50];
      char vi_tri_dat[50];
} TB;

void HienThiThongTin(TB DeviceInfo[])
{
      char *room;
      char answer;
      while (1)
      {
            printf("Ban co muon tra cuu thiet bi cua phong? [Hay nhap Y/N]");
            scanf("%c", &answer);
            fflush(stdin);
            if (answer == 'Y')
            {
                  printf("Hay nhap phong ma ban muon tim: ");
                  gets(room);
                  for (int i = 0; i < current_device; i++)
                  {
                        if ((strcmp(room, DeviceInfo[i].vi_tri_dat)) == 0)
                        {
                              printf("Thong tin thiet bi phong %s\n:", room);
                              printf("%s\n%s\n%s\n%s\n%s\n", DeviceInfo[i].ma_thiet_bi, DeviceInfo[i].ten_thiet_bi, DeviceInfo[i].nam_san_xuat, DeviceInfo[i].hang_san_xuat, DeviceInfo[i].vi_tri_dat);
                        }
                  }
            }
            else
            {
                  break;
            }
      }
}

void TraCuuThongTin(TB DeviceInfo[])
{
      char *device_code;
      char answer;
      while (1)
      {
            printf("Ban co muon tra cuu thong tin thiet bi? [Hay nhap Y/N]\n");
            scanf("%c", &answer);
            fflush(stdin);
            if (answer == 'Y')
            {
                  printf("Hay nhap ma thiet bi: \n");
                  gets(device_code);
                  for (int i = 0; i < current_device; i++)
                  {
                        if (strcmp(device_code, DeviceInfo[i].ma_thiet_bi) == 0)
                        {
                              printf("Thong tin thiet bi %s\n:", device_code);
                              printf("%s\n%s\n%s\n%s\n%s\n", DeviceInfo[i].ma_thiet_bi, DeviceInfo[i].ten_thiet_bi, DeviceInfo[i].nam_san_xuat, DeviceInfo[i].hang_san_xuat, DeviceInfo[i].vi_tri_dat);
                        }
                  }
            }
            else
            {
                  break;
            }
      }
}

void GhiThongTin(TB DeviceInfo[])
{
      char *filename = "C:\\Users\\admin\\OneDrive - Hanoi University of Science and Technology\\Documents\\C Programming\\.vscode\\C Basic\\Text Examples\\DeviceInformation.txt";
      FILE *UpdateDevice;
      if ((UpdateDevice = fopen(filename, "w")) == NULL)
      {
            printf("Can't open file.\n");
            exit(1);
      }
      fprintf(UpdateDevice, "%d\n", current_device);
      for (int i = 0; i < current_device; i++)
      {
            fprintf(UpdateDevice, "%s\n%s\n%s\n%s\n%s\n", DeviceInfo[i].ma_thiet_bi, DeviceInfo[i].ten_thiet_bi, DeviceInfo[i].nam_san_xuat, DeviceInfo[i].hang_san_xuat, DeviceInfo[i].vi_tri_dat);
      }
      fclose(UpdateDevice);
}

void CapNhatThongTin(TB DeviceInfo[])
{
      int thietbi;
      char answer;
      while (1)
      {
            printf("Ban co muon cap nhat thong tin thiet bi khong? [Hay nhap dung Y/N]\n");
            scanf("%c", &answer);
            fflush(stdin);
            if (answer == 'Y')
            {
                  printf("Hay nhap thu tu cua thiet bi ban muon sua: \n");
                  scanf("%d", &thietbi);
                  fflush(stdin);
                  printf("Thong tin ve phong cua thiet bi thu %d: %s\n", thietbi, DeviceInfo[thietbi - 1].vi_tri_dat);
                  printf("Hay nhap phong moi cho thiet bi: ");
                  gets(DeviceInfo[thietbi - 1].vi_tri_dat);
                  printf("Thong tin moi ve phong cua thiet bi thu %d: %s\n", thietbi, DeviceInfo[thietbi - 1].vi_tri_dat);
            }
            else
            {
                  break;
            }
      }
}

void ThemThietBiMoi(TB DeviceInfo[])
{
      char answer;
      int index = current_device;
      while (1)
      {
            printf("Ban co muon them thiet bi moi? [Hay nhap dung Y/N]\n");
            scanf("%c", &answer);
            fflush(stdin);
            if (answer == 'Y')
            {
                  current_device++;
                  index = current_device;
                  gets(DeviceInfo[index].ma_thiet_bi);
                  gets(DeviceInfo[index].ten_thiet_bi);
                  gets(DeviceInfo[index].nam_san_xuat);
                  gets(DeviceInfo[index].hang_san_xuat);
                  gets(DeviceInfo[index].vi_tri_dat);
                  fflush(stdin);
            }
            else
            {
                  break;
            }
      }
}

void DocThongTinThietBi(TB DeviceInfo[])
{
      char *filename = "C:\\Users\\admin\\OneDrive - Hanoi University of Science and Technology\\Documents\\C Programming\\.vscode\\C Basic\\Text Examples\\DeviceInformation.txt";
      FILE *Device;
      if ((Device = fopen(filename, "r")) == NULL)
      {
            printf("Can't open file.");
            exit(1);
      }

      int number_device;
      fscanf(Device, "%d", &number_device);
      fgetc(Device);
      current_device += number_device;

      char word[256];
      for (int i = 0; i < number_device; i++)
      {
            fgets(word, 256, Device);
            word[strcspn(word, "\n")] = 0;
            strcpy(DeviceInfo[i].ma_thiet_bi, word);
            printf("%s\n", DeviceInfo[i].ma_thiet_bi);

            fgets(word, 256, Device);
            word[strcspn(word, "\n")] = 0;
            strcpy(DeviceInfo[i].ten_thiet_bi, word);
            printf("%s\n", DeviceInfo[i].ten_thiet_bi);

            fgets(word, 256, Device);
            word[strcspn(word, "\n")] = 0;
            strcpy(DeviceInfo[i].nam_san_xuat, word);
            printf("%s\n", DeviceInfo[i].nam_san_xuat);

            fgets(word, 256, Device);
            word[strcspn(word, "\n")] = 0;
            strcpy(DeviceInfo[i].hang_san_xuat, word);
            printf("%s\n", DeviceInfo[i].hang_san_xuat);

            fgets(word, 256, Device);
            word[strcspn(word, "\n")] = 0;
            strcpy(DeviceInfo[i].vi_tri_dat, word);
            printf("%s\n", DeviceInfo[i].vi_tri_dat);
      }

      fclose(Device);
}

int main()
{
      TB DeviceInfo[200];

      int choose;
      while (1)
      {
            printf("WELCOME TO THE MENU:\n");
            printf("1. Doc thong tin thiet bi vao tu file.\n");
            printf("2. Them 1 thiet bi moi.\n");
            printf("3. Cap nhat thong tin thiet bi (chi sua doi vi tri dat).\n");
            printf("4. Ghi thong tin thiet bi vao file.\n");
            printf("5. Tra cuu thong tin 1 ma thiet bi.\n");
            printf("6. Hien thi thong tin cac thiet bi dang co cua 1 phong nao do.\n");
            printf("Hay chon 1 chuc nang: ");
            scanf("%d", &choose);
            fflush(stdin);

            if (choose == 1)
            {
                  DocThongTinThietBi(DeviceInfo);
            }
            else if (choose == 2)
            {
                  ThemThietBiMoi(DeviceInfo);
            }
            else if (choose == 3)
            {
                  CapNhatThongTin(DeviceInfo);
            }
            else if (choose == 4)
            {
                  GhiThongTin(DeviceInfo);
            }
            else if (choose == 5)
            {
                  TraCuuThongTin(DeviceInfo);
            }
            else if (choose == 6)
            {
                  HienThiThongTin(DeviceInfo);
            }
            else
            {
                  printf("\nCam on ban da su dung chuong trinh. Chuc ban mot ngay tot lanh.\n");
                  return 1;
            }
      }
}
