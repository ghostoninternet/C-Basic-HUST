#include <stdio.h>
#define ALPHABET_LEN 26

int main()
{
      int i = 0;
      int count[ALPHABET_LEN] = {0};
      char c = '\0';
      c = getchar();
      while (c != '\n' && c >= 0)
      {
            if (c <= 'z' && c >= 'a')
            {
                  ++count[c - 'a'];
            }
            else if (c <= 'Z' && c >= 'A')
            {
                  ++count[c - 'A'];
            }

            c = getchar();
      }

      for (int i = 0; i < ALPHABET_LEN; i++)
      {
            if (count[i] != 0)
            {
                  printf("The letter \'%c\' appears %d time(s).\n", 'a' + i, count[i]);
            }
      }

      return 0;
}