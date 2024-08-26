#include <stdio.h>
#include <stdlib.h>

int loaiTienQuyDoi[4] = {500000, 200000, 100000, 50000};
int luongTienQuyDoi[4] = {800, 500, 500, 400};

typedef struct Human_Info
{
      int PIN;
      long long int So_Du_Tai_Khoan;
} HI;

int feasible(int tienQuyDoi[20], int index, int tienHienTai, int tienRut)
{
      int sum = 0;
      if (index == 0)
      {
            return 1;
      }
      else
      {
            for (int i = 0; i < index; i++)
            {
                  sum += tienQuyDoi[i];
            }
            sum += tienHienTai;
            if (sum <= tienRut)
            {
                  return 1;
            }
            else
            {
                  return 0;
            }
      }
}

int checkMarked(int marked[4])
{
      for (int i = 0; i < 4; i++)
      {
            if (marked[i] == 0)
            {
                  return 1;
            }
      }
      return 0;
}

void rutTien(HI Account_Info[], int index)
{
      int tienQuyDoi[20];
      int marked[4] = {0, 0, 0, 0};

      int tienRut;
      do
      {
            printf("HAY NHAP SO TIEN: ");
            scanf("%d", &tienRut);
            if (tienRut > 10000000)
            {
                  printf("GIAO DICH TOI DA 10000000\n");
            }
            if (tienRut > Account_Info[index].So_Du_Tai_Khoan)
            {
                  printf("KHONG DU TIEN TRONG SO DU TAI KHOAN DE THUC HIEN GIAO DICH\n");
            }
      } while (tienRut > 10000000 || tienRut > Account_Info[index].So_Du_Tai_Khoan);

      int indexTienQuyDoi = 0;
      int indexLoaiTienQuyDoi = 0;
      int tienHienTai;

      while (checkMarked(marked))
      {
            tienHienTai = loaiTienQuyDoi[indexLoaiTienQuyDoi];
            if (feasible(tienQuyDoi, indexTienQuyDoi, tienHienTai, tienRut))
            {
                  tienQuyDoi[indexTienQuyDoi] = tienHienTai;
                  indexTienQuyDoi++;
                  luongTienQuyDoi[indexLoaiTienQuyDoi]--;
            }
            else
            {
                  marked[indexLoaiTienQuyDoi] = 1;
                  indexLoaiTienQuyDoi++;
            }
      }
      Account_Info[index].So_Du_Tai_Khoan -= tienRut;
      printf("RUT TIEN THANH CONG\n");
      printf("SO TIEN CUA BAN BAO GOM: \n");
      printf("%-10d TIEN 500000\n", 800 - luongTienQuyDoi[0]);
      printf("%-10d TIEN 200000\n", 500 - luongTienQuyDoi[1]);
      printf("%-10d TIEN 100000\n", 500 - luongTienQuyDoi[2]);
      printf("%-10d TIEN 50000\n", 400 - luongTienQuyDoi[3]);
}

int checkTienNap(int tienNap)
{
      if (tienNap > 100000000)
      {
            printf("GIAO DICH TOI DA 100000000/LAN\n");
            return 0;
      }
      if (tienNap < 50000)
      {
            printf("GIAO DICH TOI THIEU 50000/LAN\n");
            return 0;
      }

      for (int i = 0; i <= 200; i++)
      {
            for (int v = 0; v <= 500; v++)
            {
                  for (int j = 0; j <= 1000; j++)
                  {
                        for (int k = 0; k <= 2000; k++)
                        {
                              if ((50000 * k + 100000 * j + 200000 * v + 500000 * i) == tienNap)
                              {
                                    return 1;
                              }
                        }
                  }
            }
      }
      printf("KHONG THE QUY DOI\n");
      return 0;
}

void napTien(HI Account_Info[], int index)
{
      int tienNap;
      do
      {
            printf("HAY NHAP SO TIEN CAN NAP: ");
            scanf("%d", &tienNap);
      } while (checkTienNap(tienNap) == 0);
      printf("NAP TIEN THANH CONG\n");
      Account_Info[index].So_Du_Tai_Khoan += tienNap;
}

void chuyenTien(HI Account_Info[], int index)
{
      int tienChuyen;
      long long int STK;
      printf("\nHAY NHAP SO TAI KHOAN: ");
      scanf("%lld", &STK);

      do
      {
            printf("HAY NHAP SO TIEN CAN CHUYEN: ");
            scanf("%d", &tienChuyen);
            if (tienChuyen > 5000000)
            {
                  printf("\nCHI CO THE CHUYEN TOI DA 5000000.\n");
            }
      } while (tienChuyen > 5000000);
      Account_Info[index].So_Du_Tai_Khoan -= tienChuyen;
      printf("\nCHUYEN TIEN THANH CONG\n");
}

int checkPIN(int PIN, HI Account_Info[], int num_of_account)
{
      for (int i = 0; i < num_of_account; i++)
      {
            if (PIN == Account_Info[i].PIN)
            {
                  return i;
            }
      }
      return 0;
}

int main()
{
      char *filename = "C:\\Users\\admin\\OneDrive - Hanoi University of Science and Technology\\Documents\\C Programming\\.vscode\\C Basic\\Text Examples\\Bank Account Database.txt";
      FILE *BANK;
      if ((BANK = fopen(filename, "r")) == NULL)
      {
            printf("Can't open file.\n");
            exit(1);
      }

      int num_of_account;
      int catch_newline;
      fscanf(BANK, "%d", &num_of_account);
      catch_newline = fgetc(BANK);

      HI Account_Info[num_of_account];
      for (int i = 0; i < num_of_account; i++)
      {
            fscanf(BANK, "%d", &Account_Info[i].PIN);
            catch_newline = fgetc(BANK);
            fscanf(BANK, "%lld", &Account_Info[i].So_Du_Tai_Khoan);
            catch_newline = fgetc(BANK);
      }

      for (int i = 0; i < num_of_account; i++)
      {
            printf("Ma PIN: %d\n", Account_Info[i].PIN);
            printf("So du tai khoan: %d\n", Account_Info[i].So_Du_Tai_Khoan);
            printf("\n");
      }

      int inputPIN;
      int inputCount = 3;
      int account_index;
      do
      {
            for (int i = 0; i < 20; i++)
            {
                  printf("=");
            }
            printf("ATM");
            for (int i = 0; i < 20; i++)
            {
                  printf("=");
            }
            printf("\n");
            printf("HAY NHAP MA PIN: ");
            scanf("%d", &inputPIN);
            if ((account_index = checkPIN(inputPIN, Account_Info, num_of_account)) == 0)
            {
                  inputCount--;
                  if (inputCount == 0)
                  {
                        printf("BAN DA BI KHOA THE.\n");
                        exit(1);
                  }
                  printf("MA PIN KHONG DUNG. BAN CON %d LAN NHAP.\n", inputCount);
            }

      } while (checkPIN(inputPIN, Account_Info, num_of_account) == 0);

      int choose;
      while (1)
      {

            for (int i = 0; i < 20; i++)
            {
                  printf("=");
            }
            printf("ATM");
            for (int i = 0; i < 20; i++)
            {
                  printf("=");
            }
            printf("\nXIN VUI LONG LUA CHON GIAO DICH\n");
            printf("1. KIEM TRA SO DU TAI KHOAN\n");
            printf("2. CHUYEN TIEN\n");
            printf("3. RUT TIEN\n");
            printf("4. NAP TIEN\n");
            printf("5. THOAT\n");
            scanf("%d", &choose);
            fflush(stdin);

            if (choose >= 1 && choose <= 5)
            {
                  if (choose == 1)
                  {
                        printf("So du tai khoan la: %lld\n", Account_Info[account_index].So_Du_Tai_Khoan);
                  }
                  if (choose == 2)
                  {
                        chuyenTien(Account_Info, account_index);
                  }
                  if (choose == 3)
                  {
                        rutTien(Account_Info, account_index);
                  }
                  if (choose == 4)
                  {
                        napTien(Account_Info, account_index);
                  }
                  if (choose == 5)
                  {
                        printf("\nCHUC BAN MOT NGAY TOT LANH\n");
                        exit(1);
                  }
            }
            else
            {
                  printf("NHAP SAI DINH DANG!\n");
            }
      }

      fclose(BANK);
      return 0;
}