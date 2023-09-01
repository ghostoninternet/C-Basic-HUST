#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

const int monthDays[12] = {31, 28, 31, 30, 31, 30,
                           31, 31, 30, 31, 30, 31};

typedef struct Car_Info
{
      char bienSo[5];
      int maThe;
      int hourIN, minuteIN, secondIN;
      int dayIN, monthIN, yearIN;
} CI;

void traCuuTheoBienSo(CI Info_BaiXe[1000])
{
      char timBienSo[5];
      printf("HAY NHAP BIEN SO XE CAN TIM: ");
      gets(timBienSo);

      for (int i = 0; i < 1000; i++)
      {
            if (strcmp(timBienSo, Info_BaiXe[i].bienSo) == 0)
            {
                  printf("Da tim thay xe cua ban\n");
                  printf("Thoi Gian Vao: %d/%d/%d %d:%d:%d\n", Info_BaiXe[i].dayIN, Info_BaiXe[i].monthIN, Info_BaiXe[i].yearIN, Info_BaiXe[i].hourIN, Info_BaiXe[i].minuteIN, Info_BaiXe[i].secondIN);
                  return;
            }
      }
      printf("RAT TIEC. KHONG TIM THAY XE CUA BAN O TRONG BAI XE.\n");
}

void traCuuTheoMaThe()
{
      CI temp;
      int dayOUT, monthOUT, yearOUT, hourOUT, minuteOUT, secondOUT;
      int tienGuiXe;
      int catch_newline;
      char *filename = "C:\\Users\\admin\\OneDrive - Hanoi University of Science and Technology\\Documents\\C Programming\\.vscode\\C Basic\\Text Examples\\Bai Gui Xe Ra.txt";
      FILE *BAIXERA;
      if ((BAIXERA = fopen(filename, "r")) == NULL)
      {
            printf("Can't open file\n");
            return;
      }

      int flag = 0;
      int maTheTim;
      printf("HAY NHAP MA THE CUA BAN: ");
      scanf("%d", &maTheTim);
      fflush(stdin);

      while (fscanf(BAIXERA, "%d%s%d/%d/%d%d:%d:%d%d/%d/%d%d:%d:%d%d", &temp.maThe, &temp.bienSo, &temp.dayIN, &temp.monthIN, &temp.yearIN, &temp.hourIN, &temp.minuteIN, &temp.secondIN, &dayOUT, &monthOUT, &yearOUT, &hourOUT, &minuteOUT, &secondOUT, &tienGuiXe) != EOF)
      {
            catch_newline = fgetc(BAIXERA);
            if (maTheTim == temp.maThe)
            {
                  flag = 1;
                  printf("KET QUA: %-10d%-10s%d/%d/%-05d%d:%d:%d\t%d/%d/%-05d%d:%d:%d\n", temp.maThe, temp.bienSo, temp.dayIN, temp.monthIN, temp.yearIN, temp.hourIN, temp.minuteIN, temp.secondIN, dayOUT, monthOUT, yearOUT, hourOUT, minuteOUT, secondOUT, tienGuiXe);
            }
      }
      fclose(BAIXERA);
      if (flag == 0)
      {
            printf("RAT TIEC! KHONG TIM THAY LICH SU VE XE CUA BAN O TRONG BAI!\n");
      }
}

int countLeapyear(int day, int month, int year)
{
      int years = year;
      if (month <= 2)
      {
            years--;
      }

      return years / 4 - years / 100 + years / 400;
}

int getDifference(int dayIN, int monthIN, int yearIN, int dayOUT, int monthOUT, int yearOUT)
{
      long int n1 = yearIN * 365 + dayIN;
      for (int i = 0; i < monthIN - 1; i++)
      {
            n1 += monthDays[i];
      }
      n1 += countLeapyear(dayIN, monthIN, yearIN);

      long int n2 = yearOUT * 365 + dayOUT;
      for (int i = 0; i < monthOUT - 1; i++)
      {
            n2 += monthDays[i];
      }
      n2 += countLeapyear(dayOUT, monthOUT, yearOUT);

      return (n2 - n1);
}

void TraXe(CI Info_BaiXe[1000], int marked[1000])
{
      char *filename = "C:\\Users\\admin\\OneDrive - Hanoi University of Science and Technology\\Documents\\C Programming\\.vscode\\C Basic\\Text Examples\\Bai Gui Xe Ra.txt";
      FILE *BAIXERA;
      if ((BAIXERA = fopen(filename, "a")) == NULL)
      {
            printf("Can't open file\n");
            return;
      }

      int dayOUT, monthOUT, yearOUT, hourOUT, minuteOUT, secondOUT;
      int tienGuiXe;
      int maTheTim;
      while (1)
      {
            time_t t = time(NULL);
            struct tm tm = *localtime(&t);
            int i = 0;
            printf("HAY NHAP MA THE: ");
            scanf("%d", &maTheTim);
            fflush(stdin);
            while (i < 1000)
            {
                  if (maTheTim == Info_BaiXe[i].maThe)
                  {
                        dayOUT = tm.tm_mday;
                        monthOUT = tm.tm_mon + 1;
                        yearOUT = tm.tm_year + 1900;
                        hourOUT = tm.tm_hour;
                        minuteOUT = tm.tm_min;
                        secondOUT = tm.tm_sec;
                        break;
                  }

                  i++;
                  if (i == 1000)
                  {
                        printf("KHONG TIM THAY XE TRONG BAI\n");
                        return;
                  }
            }

            if ((Info_BaiXe[i].dayIN == dayOUT) && (Info_BaiXe[i].monthIN == monthOUT) && (Info_BaiXe[i].yearIN == yearOUT))
            {
                  if (hourOUT <= 18)
                  {
                        tienGuiXe = 3000;
                  }
                  else
                  {
                        tienGuiXe = 5000;
                  }
            }
            else
            {
                  int date = getDifference(Info_BaiXe[i].dayIN, Info_BaiXe[i].monthIN, Info_BaiXe[i].yearIN, dayOUT, monthOUT, yearOUT);
                  tienGuiXe = 10000 * date;
            }

            fprintf(BAIXERA, "\n%-10d%-10s%-02d/%-02d/%-05d%d:%d:%d  %-02d/%-02d/%-05d%d:%d:%d  %d", Info_BaiXe[i].maThe, Info_BaiXe[i].bienSo, Info_BaiXe[i].dayIN, Info_BaiXe[i].monthIN, Info_BaiXe[i].yearIN, Info_BaiXe[i].hourIN, Info_BaiXe[i].minuteIN, Info_BaiXe[i].secondIN, dayOUT, monthOUT, yearOUT, hourOUT, minuteOUT, secondOUT, tienGuiXe);

            marked[i] = 0;
            Info_BaiXe[i].maThe = 0;
            strcpy(Info_BaiXe[i].bienSo, "\0");
            Info_BaiXe[i].dayIN = 0;
            Info_BaiXe[i].monthIN = 0;
            Info_BaiXe[i].yearIN = 0;
            Info_BaiXe[i].hourIN = 0;
            Info_BaiXe[i].minuteIN = 0;
            Info_BaiXe[i].secondIN = 0;

            char answer;
            printf("XE RA TIEP? [Y/N] ");
            scanf("%c", &answer);
            fflush(stdin);
            if (answer != 'Y')
            {
                  fclose(BAIXERA);
                  return;
            }
      }
}

void GuiXe(CI Info_BaiXe[1000], int marked[1000])
{
      char *filename = "C:\\Users\\admin\\OneDrive - Hanoi University of Science and Technology\\Documents\\C Programming\\.vscode\\C Basic\\Text Examples\\Bai Gui Xe Vao.txt";
      FILE *BAIXEVAO;
      if ((BAIXEVAO = fopen(filename, "a")) == NULL)
      {
            printf("Can't open file");
            return;
      }

      int i = 0;
      char answer;
      while (i < 1000)
      {
            if (marked[i] == 1)
            {
                  if (i == 999)
                  {
                        printf("XIN LOI! BAI XE DA HET CHO GUI!\n");
                  }
                  else
                  {
                        i++;
                        continue;
                  }
            }
            printf("Nhap Bien So Xe: ");
            gets(Info_BaiXe[i].bienSo);
            printf("Nhap Ma The: ");
            scanf("%d", &Info_BaiXe[i].maThe);
            printf("Nhap gio vao: ");
            scanf("%d %d %d", &Info_BaiXe[i].hourIN, &Info_BaiXe[i].minuteIN, &Info_BaiXe[i].secondIN);
            printf("Nhap ngay vao: ");
            scanf("%d %d %d", &Info_BaiXe[i].dayIN, &Info_BaiXe[i].monthIN, &Info_BaiXe[i].yearIN);
            fflush(stdin);
            marked[i] = 1;
            fprintf(BAIXEVAO, "\n%-10d%-10s%-02d/%-02d/%-05d%d:%d:%d", Info_BaiXe[i].maThe, Info_BaiXe[i].bienSo, Info_BaiXe[i].dayIN, Info_BaiXe[i].monthIN, Info_BaiXe[i].yearIN, Info_BaiXe[i].hourIN, Info_BaiXe[i].minuteIN, Info_BaiXe[i].secondIN);
            printf("BAN CO MUON NHAP TIEP? [Y/N] ");
            scanf("%c", &answer);
            fflush(stdin);
            if (answer == 'Y')
            {
                  i++;
            }
            else
            {
                  fclose(BAIXEVAO);
                  return;
            }
      }
}

int main()
{
      CI Info_BaiXe[1000];
      int marked[1000];
      char *filename = "C:\\Users\\admin\\OneDrive - Hanoi University of Science and Technology\\Documents\\C Programming\\.vscode\\C Basic\\Text Examples\\Bai Gui Hien Tai.txt";
      FILE *BAIXE;
      if ((BAIXE = fopen(filename, "r")) == NULL)
      {
            printf("Can't open file.");
            return 1;
      }
      int catch_newline;
      for (int i = 0; i < 24; i++)
      {
            fscanf(BAIXE, "%d%s%d/%d/%d%d:%d:%d", &Info_BaiXe[i].maThe, &Info_BaiXe[i].bienSo, &Info_BaiXe[i].dayIN, &Info_BaiXe[i].monthIN, &Info_BaiXe[i].yearIN, &Info_BaiXe[i].hourIN, &Info_BaiXe[i].minuteIN, &Info_BaiXe[i].secondIN);
            if(strcmp(Info_BaiXe[i].bienSo, "XXXX") != 0)
            {
                  marked[i] = 1;
            }
            catch_newline = fgetc(BAIXE);
      }
      for (int i = 24; i < 1000; i++)
      {
            marked[i] = 0;
      }

      time_t t = time(NULL);
      struct tm tm = *localtime(&t);
      int choose;
      while (1)
      {
            printf("NGAY %d, THANG %d, NAM %d  %d:%d:%d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
            printf("MOI CHON CHUC NANG:\n");
            printf("1. GUI XE\n");
            printf("2. TRA XE\n");
            printf("3. TRA CUU THEO MA THE\n");
            printf("4. TRA CUU THEO BIEN SO\n");
            printf("5. THOAT\n");
            scanf("%d", &choose);
            fflush(stdin);

            if (choose >= 1 && choose <= 5)
            {
                  if (choose == 1)
                  {
                        GuiXe(Info_BaiXe, marked);
                  }
                  if (choose == 2)
                  {
                        TraXe(Info_BaiXe, marked);
                  }
                  if (choose == 3)
                  {
                        traCuuTheoMaThe();
                  }
                  if (choose == 4)
                  {
                        traCuuTheoBienSo(Info_BaiXe);
                  }
                  if (choose == 5)
                  {
                        printf("HAVE A NICE DAY\n");
                        return 1;
                  }
            }
            else
            {
                  printf("NHAP SAI DINH DANG!\n");
            }
      }
      return 0;
}