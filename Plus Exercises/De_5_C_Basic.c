#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 256
#define A 10000000
#define B 50000000
#define C 80000000

typedef struct NguoiMuaHang
{
      char customerName[MAX_LENGTH];
      char customerContact[MAX_LENGTH];
      struct NguoiMuaHang *next;
} NMH;

NMH *makeNode(char *customer, char *phone)
{
      NMH *newNode = (NMH *)malloc(sizeof(NMH));
      if (newNode == NULL)
      {
            printf("Error allocate memory!\n");
            exit(1);
      }

      strcpy(newNode->customerName, customer);
      strcpy(newNode->customerContact, phone);
      newNode->next = NULL;
      return newNode;
}

NMH *InsertCustomer(NMH *head, char *customer, char *phone)
{
      if (head == NULL)
      {
            return makeNode(customer, phone);
      }

      NMH *p = makeNode(customer, phone);
      NMH *q = head;
      while (q->next != NULL)
      {
            q = q->next;
      }
      q->next = p;
      return head;
}

void Print_Customer_List(NMH *head)
{
      if (head == NULL)
      {
            printf("List is empty\n");
            return;
      }
      NMH *p = head;
      while (p != NULL)
      {
            printf("%s \t %s\n", p->customerName, p->customerContact);
            p = p->next;
      }
}

NMH *Read_Customer_File(NMH *head)
{
      FILE *Customer;
      if ((Customer = fopen("danhsach.txt", "r")) == NULL)
      {
            printf("Error reading file!\n");
            exit(1);
      }

      char name[MAX_LENGTH];
      char contact[MAX_LENGTH];
      while (feof(Customer) == 0)
      {
            fscanf(Customer, "%s", name);
            fgetc(Customer);

            fscanf(Customer, "%s", contact);
            fgetc(Customer);

            head = InsertCustomer(head, name, contact);
      }
      fclose(Customer);
      return head;
}

int check_space(char *name)
{
      for (int i = 0; i < strlen(name); i++)
      {
            if (name[i] == 32)
            {
                  return 1;
            }
      }
      return 0;
}

NMH *Add_Customer(NMH *head)
{
      char name[MAX_LENGTH];
      char contact[MAX_LENGTH];
      do
      {
            printf("Nhap ten khach hang moi (khong co dau cach): ");
            gets(name);
            if (check_space(name))
            {
                  printf("Ten khach hang khong dung dinh dang! Vui long nhap lai!\n");
            }
      } while (check_space(name));

      printf("Nhap so dien thoai khach hang: ");
      gets(contact);

      head = InsertCustomer(head, name, contact);
      return head;
}

void Additional_Print(NMH *head)
{
      if (head == NULL)
      {
            printf("List is empty\n");
            return;
      }
      NMH *p = head;
      while (p != NULL)
      {
            printf("%s \t %s\n", p->customerName, p->customerContact);
            p = p->next;
      }
}

NMH *DeleteNode(NMH *head)
{
      if (head == NULL)
      {
            printf("Empty List!\n");
            return head;
      }
      NMH *p = head;
      head = head->next;
      free(p);
      return head;
}

NMH *Sell(NMH *head)
{
      if (head == NULL)
      {
            printf("Empty List!\n");
            return head;
      }

      int hangA, hangB, hangC;
      printf("Thong tin khach hang: \n");
      printf("%s\t%s\n", head->customerName, head->customerContact);

      do
      {
            printf("Hay nhap so luong mat hang A muon mua: ");
            scanf("%d", &hangA);
            if (hangA < 0)
            {
                  printf("Yeu cau so luong >= 0!\n");
            }
      } while (hangA < 0);

      do
      {
            printf("Hay nhap so luong mat hang B muon mua: ");
            scanf("%d", &hangB);
            if (hangB < 0)
            {
                  printf("Yeu cau so luong >= 0!\n");
            }
      } while (hangB < 0);

      do
      {
            printf("Hay nhap so luong mat hang C muon mua: ");
            scanf("%d", &hangC);
            if (hangC < 0)
            {
                  printf("Yeu cau so luong >= 0!\n");
            }
      } while (hangC < 0);

      FILE *BanHang;
      if ((BanHang = fopen("banhang.txt", "a")) == NULL)
      {
            printf("Error opening file!\n");
            exit(1);
      }

      fprintf(BanHang, "%d %d %d\n", hangA, hangB, hangC);
      fclose(BanHang);
      head = DeleteNode(head);
      return head;
}

void Result(NMH *head)
{
      FILE *DanhSach, *BanHang;
      if ((DanhSach = fopen("danhsach.txt", "w")) == NULL)
      {
            printf("Error opening file!\n");
            exit(1);
      }
      if ((BanHang = fopen("banhang.txt", "a")) == NULL)
      {
            printf("Error opening file!\n");
            exit(1);
      }

      fprintf(BanHang, "-1\n");

      while (head != NULL)
      {
            fprintf(DanhSach, "%s\t%s\n", head->customerName, head->customerContact);
            head = head->next;
      }

      fclose(DanhSach);
      fclose(BanHang);
}

NMH *Search(NMH *head, char *target)
{
      if (head == NULL)
      {
            printf("List is empty!\n");
            return head;
      }

      NMH *p = head;
      while (p != NULL)
      {
            if (strcmp(p->customerName, target) == 0)
            {
                  return p;
            }
            p = p->next;
      }
      printf("Customer %s Not Found!\n", target);
      return NULL;
}

NMH *prevNode(NMH *head, NMH *target)
{
      if (head == NULL)
      {
            printf("List is empty!\n");
            return head;
      }

      if (target == head)
      {
            printf("No previous Customer!\n");
            return head;
      }
      NMH *p = head;
      while (p != NULL)
      {
            if (p->next == target)
            {
                  return p;
            }
            p = p->next;
      }
}

void Satistic()
{
      int i;
      int day = 0;
      int index = 0;

      long long int hangA = 0;
      long long int hangB = 0;
      long long int hangC = 0;
      long long int sum = 0;

      FILE *BanHang;
      if ((BanHang = fopen("banhang.txt", "r")) == NULL)
      {
            printf("Error reading file!\n");
            exit(1);
      }

      while (feof(BanHang) == 0)
      {
            fscanf(BanHang, "%d", &i);
            if (i == -1 && feof(BanHang) == 0)
            {
                  sum = hangA + hangB + hangC;
                  day++;
                  printf("Thu nhap ngay %d: %lld\n", day, sum);

                  sum = hangA = hangB = hangC = 0;
            }
            else
            {
                  if (index == 0)
                  {
                        hangA += i * A;
                        index++;
                  }
                  else if (index == 1)
                  {
                        hangB += i * B;
                        index++;
                  }
                  else if (index == 2)
                  {
                        hangC += i * C;
                        index = 0;
                  }
            }
      }
      fclose(BanHang);
}

NMH *SpecialRequest(NMH *head)
{
      char Name[MAX_LENGTH];
      char Contact[MAX_LENGTH];

      do
      {
            printf("Nhap ten khach hang moi (khong co dau cach): ");
            gets(Name);
            if (check_space(Name))
            {
                  printf("Ten khach hang khong dung dinh dang! Vui long nhap lai!\n");
            }
      } while (check_space(Name));

      printf("Nhap so dien thoai khach hang: ");
      gets(Contact);

      NMH *target = Search(head, Name);
      NMH *prev;
      if (target == NULL)
      {
            return head;
      }
      else
      {
            prev = prevNode(head, target);
            if (prev == head)
            {
                  return head;
            }
            else
            {
                  prev->next = target->next;
                  target->next = head;
                  return target;
            }
      }
}

int main()
{
      int control;
      NMH *CustomeDatabase = NULL;
      while (1)
      {
            printf("CHUONG TRINH QUAN LY BAN HANG\n");
            printf("1. Doc file khach hang\n");
            printf("2. Them nguoi mua\n");
            printf("3. Ban hang\n");
            printf("4. Ghi thong tin sau mot ngay\n");
            printf("5. Thong ke thong tin ban hang\n");
            printf("6. Yeu cau dac biet\n");
            printf("Hay lua chon 1 trong 6 chuc nang: ");
            scanf("%d", &control);
            getchar();

            switch (control)
            {
            case 1:
                  CustomeDatabase = Read_Customer_File(CustomeDatabase);
                  Print_Customer_List(CustomeDatabase);
                  break;
            case 2:
                  CustomeDatabase = Add_Customer(CustomeDatabase);
                  Additional_Print(CustomeDatabase);
                  break;
            case 3:
                  CustomeDatabase = Sell(CustomeDatabase);
                  break;
            case 4:
                  Print_Customer_List(CustomeDatabase);
                  Result(CustomeDatabase);
                  break;
            case 5:
                  Satistic();
                  break;
            case 6:
                  CustomeDatabase = SpecialRequest(CustomeDatabase);
                  Print_Customer_List(CustomeDatabase);
                  break;
            default:
                  printf("Vui long nhap dung dinh dang!\n");
                  break;
            }
      }
}