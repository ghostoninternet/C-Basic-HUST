#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>

int *generateArray(int size)
{
      srand(time(NULL));
      int *retArr = (int *)malloc(size * (sizeof(int)));
      for (int i = 0; i < size; i++)
      {
            retArr[i] = rand();
      }
      return retArr;
}

int *cloneArr(int *input, int size)
{
      int *copyArr = (int *)malloc(size * sizeof(int));
      memcpy(copyArr, input, size * sizeof(int));
      return copyArr;
}

void swap(int *a, int *b)
{
      int c = *a;
      *a = *b;
      *b = c;
}

void printArr(const int *input, int size)
{
      printf("Cac phan tu trong mang kich thuoc %d la: \n", size);
      for (int i = 0; i < size; i++)
      {
            printf("%d ", input[i]);
            if((i+1) % 100 == 0)
            {
                  printf("\n");
            }
      }
}

struct timeval timeSub(struct timeval s, struct timeval e)
{
      struct timeval tval_result;
      tval_result.tv_sec = e.tv_sec - s.tv_sec;
      tval_result.tv_usec = e.tv_usec - s.tv_usec;
      if (tval_result.tv_usec < 0)
      {
            tval_result.tv_usec = 1000000 + tval_result.tv_usec;
            tval_result.tv_sec--;
      }
      return tval_result;
}

// Bubble Sort
void bubblesort(int *input, int size)
{
      for (int i = size; i > 1; i--)
      {
            for (int j = 1; j < i; j++)
            {
                  if (input[j - 1] > input[j])
                        swap(&input[j - 1], &input[j]);
            }
      }
}

// Selection Sort
void selectionsort(int *input, int size)
{
      for (int i = size; i > 1; i--) // cuoi day la i-1
      {
            int postMax = 0;
            for (int j = 1; j < i; j++)
            {
                  if (input[j] > input[postMax])
                  {
                        postMax = j;
                  }
            }
            swap(&input[postMax], &input[i - 1]);
      }
}

int main()
{
      int *A, size;
      size = 100000;
      struct timeval tval_before, tval_after, tval_result;
      time_t start, end;
      double diff_t;
      FILE * RunningTime = fopen("thoi gian chay.txt", "w");
      if(RunningTime == NULL)
      {
            printf("Can't create or write to file!\n");
            exit(1);
      }
      fprintf(RunningTime, "So luong phan tu %d\n", size);

      A = generateArray(size);
      //printf("Mang ban dau: \n");
      //printArr(A, size);

      // minh hoa bubble sort
      int *coppiedArr = cloneArr(A, size);

      gettimeofday(&tval_before, NULL);
      bubblesort(coppiedArr, size);
      gettimeofday(&tval_after, NULL);
      tval_result = timeSub(tval_before, tval_after);

      fprintf(RunningTime, "\nThoi gian bubblesort voi %d phan tu: %ld.%.06ld\n",size, (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);

      //printf("\nMang sau khi bubblesort: \n");
      //printArr(coppiedArr, size);
      free(coppiedArr);

      // minh hoa selection sort
      coppiedArr = cloneArr(A, size);
      gettimeofday(&tval_before, NULL);
      selectionsort(coppiedArr, size);
      gettimeofday(&tval_after, NULL);
      tval_result = timeSub(tval_before, tval_after);
      fprintf(RunningTime, "\nThoi gian selectionsort voi %d phan tu: %ld.%.06ld\n",size, (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);
      //printf("\nMang sau khi selectionsort: \n");
      //printArr(coppiedArr, size);
      free(coppiedArr);
      fclose(RunningTime);

      return 0;
}