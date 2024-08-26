#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <process.h>

struct Tnode
{
      char word[20];
      struct Tnode *left;
      struct Tnode *right;
};

typedef struct Tnode treeNode;

treeNode *makeTreeNode(char *word);
treeNode *RandomInsert(treeNode *tree, char *word);
void freeTree(treeNode *tree);
void printPreorder(treeNode *tree);
void printPostorder(treeNode *tree);
void printInorder(treeNode *tree);
int countNodes(treeNode *tree);
int depth(treeNode *tree);

int main()
{
      treeNode *randomTree = NULL;
      char word[20] = "a";
      while (strcmp(word, "~") != 0)
      {
            printf("\nEnter item (~ to finish): ");
            scanf("%s", word);
            if (strcmp(word, "~") == 0)
            {
                  printf("Cham dut nhap thong tin nut...\n");
            }
            else
            {
                  randomTree = RandomInsert(randomTree, word);
            }
      }

      printf("The tree in preorder: \n");
      printPreorder(randomTree);
      printf("***********************************************\n");

      printf("The tree in postorder: \n");
      printPostorder(randomTree);
      printf("***********************************************\n");

      printf("The tree in inorder: \n");
      printInorder(randomTree);
      printf("***********************************************\n");

      printf("The number of nodes is: %d\n", countNodes(randomTree));
      printf("The depth of the tree is: %d\n", depth(randomTree));

      freeTree(randomTree);
      getchar();
      return 0;
}

treeNode *makeTreeNode(char *word)
{
      treeNode *newNode = NULL;
      newNode = (treeNode *)malloc(sizeof(treeNode));
      if (newNode == NULL)
      {
            printf("Out of memory!\n");
            exit(1);
      }
      else
      {
            newNode->left = NULL;
            newNode->right = NULL;
            strcpy(newNode->word, word);
      }
      return newNode;
}

treeNode *RandomInsert(treeNode *tree, char *word)
{
      treeNode *newNode, *p;

      newNode = makeTreeNode(word);
      if (tree == NULL)
      {
            return newNode;
      }
      if (rand() % 2 == 0)
      {
            p = tree;
            while (p->left != NULL)
            {
                  p = p->left;
            }
            p->left = newNode;
            printf("Node %s is left child of %s\n", word, (*p).word);
      }
      else
      {
            p = tree;
            while(p->right != NULL)
            {
                  p = p->right;
            }
            p->right = newNode;
            printf("Node %s is right child of %s\n", word, (*p).word);
      }

      return tree;
}

void freeTree(treeNode * tree)
{
      if(tree == NULL) return;
      freeTree(tree->left);
      freeTree(tree->right);
      free(tree);
      return;
}

void printPreorder(treeNode * tree)
{
      if(tree != NULL)
      {
            printf("%s\n", tree->word);
            printPreorder(tree->left);
            printPreorder(tree->right);
      }
}

void printPostorder(treeNode * tree)
{
      if(tree != NULL)
      {
            printPostorder(tree->left);
            printPostorder(tree->right);
            printf("%s\n", tree->word);
      }
}

void printInorder(treeNode * tree)
{
      if(tree != NULL)
      {
            printInorder(tree->left);
            printf("%s\n", tree->word);
            printInorder(tree->right);
      }
}

int countNodes(treeNode * tree)
{
      if(tree == NULL) return 0;
      else
      {
            int ld = countNodes(tree->left);
            int rd = countNodes(tree->right);
            return 1 + ld + rd;
      }
}

int depth(treeNode * tree)
{
      if(tree == NULL) return 0;
      int ld = depth(tree->left);
      int rd = depth(tree->right);
      if(ld > rd) return 1 + ld; 
      else return 1 + rd;

      return 1 + (ld > rd ? ld : rd);
}