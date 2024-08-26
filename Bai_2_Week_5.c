#include <stdio.h>
#include <stdlib.h>
int **a, **p;
int m, n;
int count;

void TRY(int i, int j)
{
      p[i][j] = 1;
      count++;
      if (i > 0 && a[i - 1][j] == 1 && !p[i - 1][j])
      {
            TRY(i - 1, j);
      }

      if (i < m - 1 && a[i + 1][j] == 1 && !p[i + 1][j])
      {
            TRY(i + 1, j);
      }

      if (j > 0 && a[i][j - 1] == 1 && !p[i][j - 1])
      {
            TRY(i, j - 1);
      }

      if (j < n - 1 && a[i][j + 1] == 1 && !p[i][j + 1])
      {
            TRY(i, j + 1);
      }
}

int main()
{
      // Lay input
      FILE *fp = fopen("C:\\Users\\admin\\OneDrive - Hanoi University of Science and Technology\\Documents\\C Programming\\.vscode\\C Basic\\Text Examples\\the maze 2.txt", "r");
      fscanf(fp, "%d %d", &m, &n);
      a = (int **)malloc(m * sizeof(int *));
      int i, j;
      for (i = 0; i < m; i++)
      {
            a[i] = (int *)malloc(n * sizeof(int));
            for (j = 0; j < n; j++)
            {
                  fscanf(fp, "%d", &a[i][j]);
            }
      }

      // Khoi tao mang p danh dau phan tu vi tri (i, j) duoc tham hay chua
      p = (int **)malloc(m * sizeof(int *));
      for (i = 0; i < m; i++)
      {
            p[i] = (int *)malloc(n * sizeof(int));
            for (j = 0; j < n; j++)
            {
                  p[i][j] = 0;
            }
      }

      // Duyet qua cac vung anh
      int *area = (int *)malloc(sizeof(int)); // Luu dien tich cac vung anh tim duoc
      int index = 0;
      for (i = 0; i < m; i++)
      {
            for (j = 0; j < n; j++)
            {
                  if (!p[i][j] && a[i][j] == 1)
                  {
                        count = 0;
                        TRY(i, j);
                        realloc(area, (index + 1) * sizeof(int));
                        area[index] = count;
                        index++;
                  }
            }
      }

      int max = 0;
      int min = 999999;
      for (i = 0; i < index; i++)
      {
            if (area[i] > max)
                  max = area[i];
            if (area[i] < min)
                  min = area[i];
      }
      printf("So vung anh: %d\n", index);
      printf("Max area: %d\nMin area: %d\n", max, min);
}