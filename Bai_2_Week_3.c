#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Tạo Cấu Trúc DanhBa (DB) với 1 pointer name và 1 double pointer number
typedef struct DanhBa
{
      char *name;
      char **number;
} DB;

int main()
{
      //Đọc file, lấy ra số lượng dòng trong file và số lượng contacts.
      char *filename = "C:\\Users\\admin\\OneDrive - Hanoi University of Science and Technology\\Documents\\C Programming\\.vscode\\C Basic\\Text Examples\\Contacts.txt";
      FILE *Contacts;
      if ((Contacts = fopen(filename, "r")) == NULL)
      {
            printf("Can't open file");
            exit(1);
      }

      int num_contacts;
      fscanf(Contacts, "%d", &num_contacts);
      fgetc(Contacts);
      DB *Contact_Info = (DB *)malloc(sizeof(DB) * num_contacts); // Cấp phát bộ nhớ động cho biến DB Contact_Info với số lượng tương ứng với số lượng contacts.

      char word[256];
      int number_of_line = 0;
      while (fgets(word, 256, Contacts))
      {
            number_of_line++;
      }
      printf("%d\n", number_of_line);
      fclose(Contacts);

      // Lưu trữ các Contacts ở trong file vào 1 double pointer WORDS
      FILE *reContacts;
      if ((reContacts = fopen(filename, "r")) == NULL)
      {
            printf("Can't open file");
            exit(1);
      }

      fscanf(reContacts, "%d", &num_contacts);
      fgetc(reContacts);

      char **WORDS = (char **)malloc(sizeof(char *) * number_of_line);
      for (int i = 0; i < number_of_line; i++)
      {
            fgets(word, 256, reContacts);
            word[strcspn(word, "\n")] = 0;
            WORDS[i] = (char *)malloc(sizeof(char) * (strlen(word) + 1));
            strcpy(WORDS[i], word);
      }
      fclose(reContacts);

      // Gán tên vào biến name trong cấu trúc DanhBa (DB), Lấy ra số lượng số điện thoại của mỗi người và lưu vào mảng number_of_phoneNum
      int index = 0;
      int count = 0;
      int number_of_phoneNum[num_contacts];
      for (int i = 0; i < number_of_line; i++)
      {
            if (WORDS[i][0] >= 'A' && WORDS[i][0] <= 'Z')
            {
                  Contact_Info[index].name = (char *)malloc(sizeof(char) * (strlen(WORDS[i]) + 1));
                  strcpy(Contact_Info[index].name, WORDS[i]);
                  printf("%s\n", Contact_Info[index].name);
                  index++;
                  count = 0;
            }
            else
            {
                  count++;
                  number_of_phoneNum[index - 1] = count;
            }
      }

      // Cấp phát bộ nhớ cho double pointer number tương ứng với mỗi Contact_Info (Tên biến con trỏ kiểu DanhBa (DB)).
      for (int i = 0; i < num_contacts; i++)
      {
            Contact_Info[i].number = (char **)malloc(sizeof(char *) * number_of_phoneNum[i]);
      }

      /*
      1. Chạy vòng lặp, lấy các phần tử trong mảng WORDS mang giá trị là số điện thoại
      2. Cấp phát bộ nhớ động cho mỗi phần tử của number trong Contact_Info
      3. Lưu phần tử WORDS là số điện thoại vào trong number.
      4. Cập nhật 2 biến index2 (Vị trí của Contact_Info) và index3 (Vị trí của number)
      */
      int index2 = 0;
      int index3 = 0;
      for (int i = 0; i < number_of_line; i++)
      {
            if (WORDS[i][0] >= '0' && WORDS[i][0] <= '9')
            {
                  Contact_Info[index2 - 1].number[index3] = (char *)malloc(sizeof(char) * (strlen(WORDS[i]) + 1));
                  strcpy(Contact_Info[index2 - 1].number[index3], WORDS[i]);
                  index3++;
            }
            else
            {
                  index2++;
                  index3 = 0;
            }
      }

      // In ra danh sách Contacts
      for (int i = 0; i < num_contacts; i++)
      {
            printf("%s\n", Contact_Info[i].name);
            for (int j = 0; j < number_of_phoneNum[i]; j++)
            {
                  printf("%s\n", Contact_Info[i].number[j]);
            }
      }

      // Tìm kiếm thông tin contact.
      char answer;
      int flag = 0;
      while (1)
      {
            printf("\nHay nhap nguoi ban muon tim:\n");
            char search_name[50];
            scanf("%s", search_name);
            fflush(stdin);
            for (int i = 0; i < num_contacts; i++)
            {

                  if (strstr(Contact_Info[i].name, search_name) != NULL)
                  {
                        flag = 1;
                        printf("Found: %s\n", Contact_Info[i].name);
                        for (int j = 0; j < number_of_phoneNum[i]; j++)
                        {
                              printf("%s\n", Contact_Info[i].number[j]);
                        }
                  }
            }
            if(flag == 0)
            {
                  printf("\nKhong tim thay ten nguoi dung.");
            }
            else
            {
                  flag = 0;
            }

            printf("\nBan co muon tiep tuc tim? [Hay nhap Y/N]");
            scanf("%c", &answer);
            fflush(stdin);
            if (answer == 'N')
            {
                  break;
            }
      }

      // Giải phóng bộ nhớ.
      for (int i = 0; i < num_contacts; i++)
      {
            free(Contact_Info[i].name);
            for (int j = 0; j < number_of_phoneNum[i]; j++)
            {
                  free(Contact_Info[i].number[j]);
            }
      }
      free(Contact_Info);
      return 0;
}
