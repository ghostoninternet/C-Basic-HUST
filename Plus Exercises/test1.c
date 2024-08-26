#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
      int id;
      struct Node * next;
}Node;

Node * makeNode(int k)
{
      Node * newNode = (Node *)malloc(sizeof(Node));
      newNode->id = k;
      newNode->next = NULL;
      return newNode;
}

Node * insertNode(Node * head, int k)
{
      if(head == NULL)
      {
            return makeNode(k);
      }
      Node * newNode = makeNode(k);
      newNode->next = head;
      return newNode;
}

Node * inverse(Node * head)
{
      Node * p = head;
      Node * pp = NULL;
      Node * np = NULL;

      while(p != NULL)
      {
            np = p->next;
            p->next = pp;
            pp = p;
            p = np;
      }

      return pp;
}

void printList(Node * head)
{
      while(head != NULL)
      {
            printf("%d ", head->id);
            head = head->next;
      }
      printf("\n\n");
}

int main()
{
      Node * random = NULL;
      for(int i = 0; i < 10; i++)
      {
            random = insertNode(random, i+1);
      }
      printf("Before: ");
      printList(random);

      printf("After: ");
      random = inverse(random);
      printList(random);

      return 0;
}