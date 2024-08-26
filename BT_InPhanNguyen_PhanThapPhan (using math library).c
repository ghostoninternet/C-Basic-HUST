#include <stdio.h>
#include <math.h>
void printDouble(double number)
{
      int phanNguyen;
      double phanThapPhan;
      if (number < 0)
      {
            phanNguyen = ceil(number);
            phanThapPhan = number - phanNguyen;
            printf("Phan nguyen la: %d\n", phanNguyen * -1);
            printf("Phan thap phan la: %lf ", phanThapPhan * -1);
      }
      else
      {
            phanNguyen = floor(number);
            phanThapPhan = number - phanNguyen;
            printf("Phan nguyen la: %d\n", phanNguyen);
            printf("phan thap phan la: %lf", phanThapPhan);
      }

}
int main()
{
      double number;
      scanf("%lf", &number);
      printDouble(number);
      return 0;
}