#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
Chương trình đọc vào 1 văn bản từ file, in ra các từ viết hoa, các tên riêng.
*/

void CleanParagraph(FILE *fIN1) // Làm sạch văn bản, thay các dấu . , ! ? thành dấu cách
{
      FILE *fOUT1;
      char *filename2 = "C:\\Users\\admin\\OneDrive - Hanoi University of Science and Technology\\Documents\\C Programming\\.vscode\\C Basic\\Text Examples\\CopyOfParagraph3.txt";

      int c;
      if ((fOUT1 = fopen(filename2, "w")) == NULL)
      {
            printf("Can't open or write file.");
      }
      else
      {
            while ((c = fgetc(fIN1)) != EOF)
            {
                  if (c == 33 || c == 44 || c == 46 || c == 63)
                  {
                        c = 32;
                        fputc(c, fOUT1);
                  }
                  else
                  {
                        fputc(c, fOUT1);
                  }
            }
      }
      fclose(fOUT1);
      fclose(fIN1);
}

char **loadWORDS(int num_of_words, char *fileParagraph) // Cấp phát động để lưu trữ các từ trong văn bản.
{
      char **WORDS = (char **)malloc(sizeof(char *) * num_of_words);
      FILE *Paragraph;
      if ((Paragraph = fopen(fileParagraph, "r")) == NULL)
      {
            printf("Can't open file.");
            exit(1);
      }

      char *a;
      int length;
      for (int i = 0; i < num_of_words; i++)
      {
            fscanf(Paragraph, "%s", a);
            length = strlen(a);
            WORDS[i] = (char *)malloc(sizeof(char) * (length + 1));
            strcpy(WORDS[i], a);
      }
      fclose(Paragraph);
      return WORDS;
}

int checkWords(int num_of_words, char **BagOfWords) // Kiểm tra các từ thỏa mãn yêu cầu đầu bài.
{
      int satisfied = 0;
      for (int i = 0; i < num_of_words; i++)
      {
            if (isupper(BagOfWords[i][0]))
            {
                  printf("%s\n", BagOfWords[i]);
                  satisfied++;
            }
      }
      return satisfied;
}

char **satisfiedBagOfWords(int num_of_satis_words, int num_of_words, char **BagOfWords) // Lưu trữ các từ thỏa mãn vào trong một vùng nhớ cấp phát động.
{
      char **satis_words = (char **)malloc(sizeof(char *) * num_of_satis_words);
      int index = 0;
      for (int i = 0; i < num_of_words; i++)
      {
            if (isupper(BagOfWords[i][0]))
            {
                  satis_words[index] = (char *)malloc(sizeof(char) * (strlen(BagOfWords[i]) + 1));
                  strcpy(satis_words[index], BagOfWords[i]);
                  index++;
            }
      }
      return satis_words;
}

void NumberOfOccurence(int num_satisfied_word, int num_word, char **SatisfiedWords, char **BagOfWords)
{
      int occurence[num_satisfied_word];
      int counting = 0;
      for (int i = 0; i < num_satisfied_word; i++)
      {
            for (int j = 0; j < num_word; j++)
            {
                  if (strcmp(SatisfiedWords[i], BagOfWords[j]) == 0)
                  {
                        counting++;
                  }
            }
            occurence[i] = counting;
            counting = 0;
      }

      printf("\n\n%-50s%-50s\n", "Words", "Number of appearance");
      for (int i = 0; i < num_satisfied_word; i++)
      {
            printf("%-50s%-50d\n", SatisfiedWords[i], occurence[i]);
      }
}

void freeMem(int num1, int num2, char **DPointer1, char **DPointer2) // Giải phóng bộ nhớ.
{
      for (int i = 0; i < num1; i++)
      {
            free(DPointer1[i]);
      }
      free(DPointer1);

      for (int i = 0; i < num2; i++)
      {
            free(DPointer2[i]);
      }
      free(DPointer2);
}

int main()
{
      // Open and Clean the Paragraph.
      char *filename = "C:\\Users\\admin\\OneDrive - Hanoi University of Science and Technology\\Documents\\C Programming\\.vscode\\C Basic\\Text Examples\\Paragraph3.txt";
      FILE *fIN, *fOUT;
      if ((fIN = fopen(filename, "r")) == NULL)
      {
            printf("Can't open file.");
            return 1;
      }
      CleanParagraph(fIN);
      fclose(fIN);

      // Open and count number of words
      char *filename3 = "C:\\Users\\admin\\OneDrive - Hanoi University of Science and Technology\\Documents\\C Programming\\.vscode\\C Basic\\Text Examples\\CopyOfParagraph3.txt";
      if ((fOUT = fopen(filename3, "r")) == NULL)
      {
            printf("Can't open file.");
            return 1;
      }

      char word[50];
      int count = 0;

      while ((fscanf(fOUT, "%s", word)) != EOF)
      {
            count++; // Count number of words
      }
      fclose(fOUT);

      // Save all words in Paragraph to a double pointer character.
      char **wordsParagraph = loadWORDS(count, filename3);

      // Check all words and return number of satisfied words.
      int number_of_satisfied_words;
      number_of_satisfied_words = checkWords(count, wordsParagraph);

      // Save all satisfied words to a double pointer character.
      char **satisfiledWORDS = satisfiedBagOfWords(number_of_satisfied_words, count, wordsParagraph);

      // Compare each satisfied word with a word in paragraph, count number of occurence and print the word and number of word's occurence.
      NumberOfOccurence(number_of_satisfied_words, count, satisfiledWORDS, wordsParagraph);

      // Free the memory
      freeMem(count, number_of_satisfied_words, wordsParagraph, satisfiledWORDS);
      return 0;
}