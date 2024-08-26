#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DOI_BONG 30

typedef struct DoiBong
{
      int team_ID;
      char team_name[DOI_BONG];
      int score;
      int win;
      int lose;
      struct DoiBong * next;
}DB;

typedef struct TranDau
{
      char TeamA[DOI_BONG];
      char TeamB[DOI_BONG];
      int TeamA_Score;
      int TeamB_Score;
      struct TranDau * next;
}TD;

typedef struct VongDau
{
      char TenVongDau[DOI_BONG];
      int updated;
      TD * TranDau;
      struct VongDau * next;
}VD;

VD * makeNodeVD(char * name)
{
      VD * newNode = (VD *)malloc(sizeof(VD));
      if(newNode == NULL)
      {
            printf("Error allocate memory!\n");
            exit(1);
      }

      strcpy(newNode->TenVongDau, name);
      newNode->TranDau = NULL;
      newNode->next = NULL;
      newNode->updated = 0;

      return newNode;
}

VD * InsertVD(VD * head_VD, char *name)
{
      if(head_VD == NULL)
      {
            return makeNodeVD(name);
      }
      
      VD * newNode = makeNodeVD(name);
      VD * p = head_VD;
      while(p->next != NULL)
      {
            p = p->next;
      }
      
      p->next = newNode;
      return head_VD;
}

TD * makeNodeTD(char * A, char * B)
{
      TD * newNode = (TD *)malloc(sizeof(TD));
      if(newNode == NULL)
      {
            printf("Error allocate memory!\n");
            exit(1);
      }

      strcpy(newNode->TeamA, A);
      strcpy(newNode->TeamB, B);
      newNode->TeamA_Score = newNode->TeamB_Score = 0;
      newNode->next = NULL;

      return newNode;
}

TD * InsertTD(TD * head_TD, char * A, char * B)
{
      if(head_TD == NULL)
      {
            return makeNodeTD(A, B);
      }

      TD * newNode = makeNodeTD(A, B);
      TD * p = head_TD;
      while(p->next != NULL)
      {
            p = p->next;
      }

      p->next = newNode;
      return head_TD;
}

DB * makeNode(int ID, char *name)
{
      DB * newNode = (DB *)malloc(sizeof(DB));
      if(newNode == NULL)
      {
            printf("Error allocate memory!\n");
            exit(1);
      }

      newNode->team_ID = ID;
      strcpy(newNode->team_name, name);
      newNode->score = 0;
      newNode->win = 0;
      newNode->lose = 0;
      newNode->next = NULL;

      return newNode;
}

DB * InsertTeam(DB * head, int ID, char *name)
{
      if(head == NULL)
      {
            return makeNode(ID, name);
      }

      DB * newNode = makeNode(ID, name);
      newNode->next = head;
      return newNode;
}

DB * GetInfo(DB * head, int * Team)
{
      FILE * BongDa;
      FILE * VongDau;

      if((VongDau = fopen("vongdau.txt", "w")) == NULL)
      {
            printf("Error writing file\n");
            exit(1);
      }
      if((BongDa = fopen("bongda.txt", "r")) == NULL)
      {
            printf("Error reading file\n");
            exit(1);
      }

      int *N = Team;
      int ID;
      char name[DOI_BONG];
      fscanf(BongDa, "%d", N);
      fgetc(BongDa);

      for(int i = 1; i <= *N; i++)
      {
            fscanf(BongDa, "%d", &ID);
            fgetc(BongDa);

            fgets(name, DOI_BONG, BongDa);
            if(name[strlen(name) - 1] == 10)
            {
                  name[strlen(name) - 1] = '\0';
            }

            head = InsertTeam(head, ID, name);
      }

      char VongDauThu[DOI_BONG];
      int Doi1;
      int Doi2;
      for(int i = 1; i <= (*N-1); i++)
      {
            fgets(VongDauThu, DOI_BONG, BongDa);
            VongDauThu[strlen(VongDauThu) - 1] = '\0';
            fprintf(VongDau, "%s\n", VongDauThu);
            for(int i = 1; i <= *N/2; i++)
            {
                  fscanf(BongDa, "%d %d", &Doi1, &Doi2);
                  fgetc(BongDa);
                  fprintf(VongDau, "%d\t%d\n", Doi1, Doi2);
            }
      }
      fclose(VongDau);
      fclose(BongDa);
      return head;
}

void printTeam(DB * head)
{
      if(head == NULL)
      {
            printf("Danh sach trong!\n");
            return ;
      }
      printf("%-10s%-35s%-10s%-20s%-20s\n", "ID", "Tendoibong", "Diem", "Sobanthang", "Sobanthua");
      DB * p = head;
      while(p != NULL)
      {
            printf("%-10d%-35s%-10d%-20d%-20d\n", p->team_ID, p->team_name, p->score, p->win, p->lose);
            p = p->next;
      }
}

char * TimDoiBong(DB * head, int code)
{
      if(head == NULL)
      {
            return NULL;
      }
      while(head != NULL)
      {
            if(head->team_ID == code)
            {
                  return head->team_name;
            }
            head = head->next;
      }
}

VD * ThongTinVongDau(DB* head, VD * head_VD, int N)
{
      TD * TranDauThu = NULL;
      VD * p;
      FILE *VongDau;
      if((VongDau = fopen("vongdau.txt", "r")) == NULL)
      {
            printf("Error reading file!\n");
            exit(1);
      }

      char VongDauThu[DOI_BONG];
      int Doi1;
      int Doi2;
      char TeamA[DOI_BONG];
      char TeamB[DOI_BONG];

      for(int i = 1; i <= (N - 1); i++)
      {
            fgets(VongDauThu, DOI_BONG, VongDau);
            VongDauThu[strlen(VongDauThu)-1] = '\0';
            head_VD = InsertVD(head_VD, VongDauThu);
            p = head_VD;
            //printf("Inserted!\n");
            for(int i = 1; i <= N/2; i++)
            {
                  fscanf(VongDau, "%d %d", &Doi1, &Doi2);
                  fgetc(VongDau);
                  strcpy(TeamA, TimDoiBong(head, Doi1));
                  strcpy(TeamB, TimDoiBong(head, Doi2));
                  TranDauThu = InsertTD(TranDauThu, TeamA, TeamB);
            }
            for(int j = 1; j < i; j++)
            {
                  p = p->next;
            }
            p->TranDau = TranDauThu;
            TranDauThu = NULL;
      }

      return head_VD;
}

void printTranDau(VD * head_VD)
{
      TD * p;
      if(head_VD == NULL)
      {
            printf("Danh sach trong!\n");
      }
      while(head_VD != NULL)
      {
            printf("%s\n", head_VD->TenVongDau);
            p = head_VD->TranDau;
            while(p != NULL)
            {
                  printf("%s\t%s\n", p->TeamA, p->TeamB);
                  p = p->next;
            }
            head_VD = head_VD->next;
      }
}

VD * CapNhatVongDau(VD * head_VD)
{
      VD * q = head_VD;
      while((q != NULL) && q->updated == 1)
      {
            q = q->next;
      }
      if(q == NULL)
      {
            printf("Da cap nhat het ket qua cac vong dau!\n");
            return head_VD;
      }
      q->updated = 1;

      TD *p = q->TranDau;
      int teamA;
      int teamB;
      printf("Cap nhat ket qua %s:\n", q->TenVongDau);
      printf("%s\n", q->TenVongDau);
      while(p != NULL)
      {
            printf("%s\t%s : ", p->TeamA, p->TeamB);
            scanf("%d-%d", &teamA, &teamB);
            p->TeamA_Score = teamA;
            p->TeamB_Score = teamB;
            //printf("%d\t\t%d\n", p->TeamA_Score, p->TeamB_Score);
            p = p->next;
      }
      return head_VD;
}

DB * CapNhatBXH(DB * head, VD * head_VD)
{
      if(head_VD == NULL)
      {
            return head;
      }
      TD * p = head_VD->TranDau;
      if(p == NULL)
      {
            printf("Error\n");
      }
      DB * q1, *q2;
      while(p != NULL)
      {
            q1 = head;
            q2 = head;
            if(p->TeamA_Score > p->TeamB_Score)
            {
                  printf("%s\n", q1->team_name);
                  while(q1 != NULL)
                  {
                        if(strcmp(q1->team_name, p->TeamA) == 0)
                        {
                              printf("%s\n", q1->team_name);
                              q1->score += 3;
                              q1->win += 1;
                              break;
                        }
                        q1 = q1->next;
                  }

                  while(q2 != NULL)
                  {
                        if(strcmp(q2->team_name, p->TeamB) == 0)
                        {
                              q2->score += 0;
                              q2->lose += 1;
                        }
                        q2 = q2->next;
                  }
            }
            else if(p->TeamA_Score < p->TeamB_Score)
            {
                  while(q1 != NULL)
                  {
                        if(strcmp(q1->team_name, p->TeamA) == 0)
                        {
                              q1->score += 0;
                              q1->lose += 1;
                              break;
                        }
                        q1 = q1->next;
                  }

                  while(q2 != NULL)
                  {
                        if(strcmp(q2->team_name, p->TeamB) == 0)
                        {
                              q2->score += 3;
                              q2->win += 1;
                              break;
                        }
                        q2 = q2->next;
                  }
            }
            else if(p->TeamA_Score == p->TeamB_Score)
            {
                  while(q1 != NULL)
                  {
                        if(strcmp(q1->team_name, p->TeamA) == 0)
                        {
                              q1->score += 1;
                              break;
                        }
                        q1 = q1->next;
                  }

                  while(q2 != NULL)
                  {
                        if(strcmp(q2->team_name, p->TeamB) == 0)
                        {
                              q2->score += 1;
                              break;
                        }
                        q2 = q2->next;
                  }
            }
            p = p->next;
      }
      return head;
}

void printBXH(DB * head)
{
      if(head == NULL)
      {
            printf("BXH trong!\n");
            return;
      }
      printf("%-10s%-35s%-10s%-20s%-20s\n", "ID", "Tendoibong", "Diem", "Sobanthang", "Sobanthua");
      DB * p = head;
      while(p != NULL)
      {
            printf("%-10d%-35s%-10d%-20d%-20d\n", p->team_ID, p->team_name, p->score, p->win, p->lose);
            p = p->next;
      }
}

int FindMin(DB * head)
{
      int min = head->score;
      while(head != NULL)
      {
            if(head ->score < min)
            {
                  min = head->score;
            }
            head = head->next;
      }
      return min;
}

DB * MinPosition(DB * head, int min)
{
      while(head != NULL)
      {
            if(head->score == min)
            {
                  return head;
            }
            head = head->next;
      }
      return NULL;
}

DB * DeleteNode(DB * head, DB * p)
{
      if(head == NULL)
      {
            return head;
      }
      if(head == p)
      {
            DB * q = head;
            head = head->next;
            free(q);
            return head;
      }

      DB * move = head;
      while(move->next != p)
      {
            move = move->next;
      }
      if(p->next == NULL)
      {
            move->next = NULL;
            free(p);
            return head;
      }
      else
      {
            move->next = p->next;
            free(p);
            return head;
      }
}

DB * LeastScoreTeam(DB * head)
{
      if(head == NULL)
      {
            printf("Danh sach trong! Hay cap nhat danh sach moi\n");
            return head;
      }
      DB * q;
      int minimum = FindMin(head); //Tìm điểm thấp nhất trong các đội
      printf("Cac doi co diem thap nhat la: \n");
      printf("%-10s%-35s%-10s%-20s%-20s\n", "ID", "Tendoibong", "Diem", "Sobanthang", "Sobanthua");
      while((q = MinPosition(head, minimum)) != NULL) //Tìm đội có số điểm thấp nhất và loại ra cho đến khi không tìm thấy đội nào nữa
      {
            printf("%-10d%-35s%-10d%-20d%-20d\n", q->team_ID, q->team_name, q->score, q->win, q->lose);
            head = DeleteNode(head, q);
      }
      return head;
}

void printStatistic(DB * head)
{
     if(head == NULL)
      {
            printf("Danh sach trong!\n");
            return ;
      }
      printf("Cac doi bong con lai la: \n");
      printf("%-10s%-35s%-10s%-20s%-20s\n", "ID", "Tendoibong", "Diem", "Sobanthang", "Sobanthua");
      DB * p = head;
      while(p != NULL)
      {
            printf("%-10d%-35s%-10d%-20d%-20d\n", p->team_ID, p->team_name, p->score, p->win, p->lose);
            p = p->next;
      }
}

int main()
{
      int control;
      DB * ThongTin = NULL;
      VD * VongDauCacDoi = NULL;
      int Num_of_Team;
      ThongTin = GetInfo(ThongTin, &Num_of_Team);
      VongDauCacDoi = ThongTinVongDau(ThongTin, VongDauCacDoi, Num_of_Team);
      while(1)
      {
            printf("Quan Ly Tran Dau Cac Doi Bong\n");
            printf("1. In thong tin cac doi bong\n");
            printf("2. In thong tin lich thi dau\n");
            printf("3. Cap nhat ket qua vong dau\n");
            printf("4. Thong ke\n");
            printf("Hay chon 1 trong 4 chuc nang: ");
            scanf("%d", &control);
            getchar();

            switch (control)
            {
            case 1:
                  printTeam(ThongTin);
                  break;
            case 2:
                  printTranDau(VongDauCacDoi);
                  break;
            case 3:
                  VongDauCacDoi = CapNhatVongDau(VongDauCacDoi);
                  ThongTin = CapNhatBXH(ThongTin, VongDauCacDoi);
                  VongDauCacDoi = VongDauCacDoi->next;
                  printBXH(ThongTin);
                  break;
            case 4:
                  ThongTin = LeastScoreTeam(ThongTin);
                  printStatistic(ThongTin);
                  break;
            default:
                  printf("Vui long nhap dung dinh dang\n");
                  break;
            }
      }
}