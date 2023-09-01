#include <stdio.h>
#include <math.h>

#define SIZE 7

int main()
{
      double open_price[SIZE];
      double close_price[SIZE];

      for(int i=0; i<SIZE; i++)
      {
            scanf("%lf", &open_price[i]);
            scanf("%lf", &close_price[i]);
            fflush(stdin);
      }

      double maxdiff = 0;
      int day_diffmax;
      for(int i=0; i<SIZE; i++)
      {
            double current_diff = fabs(open_price[i] - close_price[i]);
            if( current_diff > maxdiff)
            {
                  maxdiff = current_diff;
                  day_diffmax = i+1;
            }
      }
      printf("\nMax difference is: %.2lf \nDay with max difference: %d", maxdiff, day_diffmax);


      int length = 1;
      int max_length = 1;
      int end_index, start_index;
      for(int i=0; i<SIZE-1; i++)
      {
            if(open_price[i] < open_price[i+1])
            {
                  length++;
            }
            else
            {
                  if(max_length < length)
                  {
                        max_length = length;
                        end_index = i;
                        start_index = i - length + 1 ;
                  }
                  length = 1;
                  
            }
      }
      for(int i=start_index; i<=end_index; i++)
      {
            printf("%.2lf ", open_price[i]);
      }

      double max_decrese = 0;
      int current_day, previous_day;
      for (int i = 1; i < SIZE-1; i++)
      {
            double decrese = fabs(close_price[i-1] - close_price[i]);
            if(decrese > max_decrese)
            {
                  max_decrese = decrese;
                  current_day = i+1;
                  previous_day = i;
            }
      }
      printf("Max decrese: %.2lf\nDay that has max decrese: %d\nThe previous day: %d", max_decrese, current_day, previous_day);
      
      return 0;
}