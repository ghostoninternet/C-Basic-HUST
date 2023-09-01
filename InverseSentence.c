#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[])
{
      int num_word = argc - 1;
      if (num_word <= 1)
      {
            printf("Please provide a full sentence not a word!");
            return 1;
      }
      else
      {
            while(num_word >= 1)
            {
                  printf("%s ", argv[num_word]);
                  num_word--;
            }
      }
      return 0;
}