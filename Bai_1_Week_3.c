#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
Chương trình đọc vào 1 văn bản từ file, in ra các từ viết hoa, các tên riêng.
*/

void CleanParagraph(FILE *fIN1) //Làm sạch văn bản, thay các dấu . , ! ? thành dấu cách
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

char **loadWORDS(int num_of_words, char *fileParagraph) //Cấp phát động để lưu trữ các từ trong văn bản.
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

void checkWords(int num_of_words, char ** BagOfWords) //Kiểm tra các từ thỏa mãn yêu cầu đầu bài.
{
      for(int i = 0; i < num_of_words; i++)
      {
            if(isupper(BagOfWords[i][0]))
            {
                  printf("%s\n", BagOfWords[i]);
            }
      }
}

void freeMem(int num, char ** DPointer) //Giải phóng bộ nhớ.
{
      for(int i = 0; i < num; i++)
      {
            free(DPointer[i]);
      }
      free(DPointer);
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
            count++;
      }
      fclose(fOUT);
      
      //Save all words in Paragraph to a double pointer character.
      char **wordsParagraph = loadWORDS(count, filename3);
      
      //Check all words.
      checkWords(count, wordsParagraph);
      freeMem(count, wordsParagraph);
      return 0;
}