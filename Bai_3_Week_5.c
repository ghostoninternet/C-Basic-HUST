#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printSolution(char *found_word)
{
      printf("Found %s\n", found_word);
}

int check(char *word, char **WORD, int num_of_word)
{
      
      if (word == NULL)
      {
            return 0;
      }
      for (int i = 0; i < num_of_word; i++)
      {
            if (strcmp(word, WORD[i]) == 0)
            {
                  return 1;
            }
      }
      return 0;
}


void Try(int row, int column, char board_character[row][column], int x_move, int y_move, int x_initial, int y_initial, int current_column, int current_row, int length[8], int locked[8], char **WORD, int num_of_word)
{
      if (locked[0] == 0 && (current_column + 1) != column)
      {
            x_move = current_column + 1;
            y_move = current_row;
            length[0] += 1;
            char *current_word = (char *)malloc(sizeof(char) * (length[0] + 1));
            for(int i = 0; i < length[0]; i++)
            {
                  current_word[i] = board_character[y_initial][x_initial + i];
            }
            current_word[length[0]] = '\0';
            if (check(current_word, WORD, num_of_word))
            {
                  printSolution(current_word);
                  free(current_word);
            }
            else
            {
                  if ((x_move + 1) == column)
                  {
                        free(current_word);
                        length[0] = 1;
                        locked[0] = 1;
                        Try(row, column, board_character, x_move, y_move, x_initial, y_initial, x_initial, y_initial, length, locked, WORD, num_of_word);
                  }
                  free(current_word);
                  Try(row, column, board_character, x_move, y_move, x_initial, y_initial, x_move, y_move, length, locked, WORD, num_of_word);
            }
      }

      if (locked[1] == 0 && (current_column - 1) != -1)
      {
            x_move = current_column - 1;
            y_move = current_row;
            length[1] += 1;
            char *current_word = (char *)malloc(sizeof(char) * (length[1] + 1));
            for(int i = 0; i < length[1]; i++)
            {
                  current_word[i] = board_character[y_initial][x_initial - i];
            }
            current_word[length[1]] = '\0';
            if (check(current_word, WORD, num_of_word))
            {
                  printSolution(current_word);
                  free(current_word);
            }
            else
            {
                  if ((x_move - 1) == -1)
                  {
                        free(current_word);
                        length[1] = 1;
                        locked[1] = 1;
                        Try(row, column, board_character, x_move, y_move, x_initial, y_initial, x_initial, y_initial, length, locked, WORD, num_of_word);
                  }
                  free(current_word);
                  Try(row, column, board_character, x_move, y_move, x_initial, y_initial, x_move, y_move, length, locked, WORD, num_of_word);
            }
      }

      if (locked[2] == 0 && (current_row - 1) != -1)
      {
            x_move = current_column;
            y_move = current_row - 1;
            length[2] += 1;
            char *current_word = (char *)malloc(sizeof(char) * (length[2] + 1));
            for(int i = 0; i < length[2]; i++)
            {
                  current_word[i] = board_character[y_initial - i][x_initial];
            }
            current_word[length[2]] = '\0';
            if (check(current_word, WORD, num_of_word))
            {
                  printSolution(current_word);
                  free(current_word);
            }
            else
            {
                  if ((y_move - 1) == -1)
                  {
                        free(current_word);
                        length[2] = 1;
                        locked[2] = 1;
                        Try(row, column, board_character, x_move, y_move, x_initial, y_initial, x_initial, y_initial, length, locked, WORD, num_of_word);
                  }
                  free(current_word);
                  Try(row, column, board_character, x_move, y_move, x_initial, y_initial, x_move, y_move, length, locked, WORD, num_of_word);
            }
      }

      if (locked[3] == 0 && (current_row + 1) != row)
      {
            x_move = current_column;
            y_move = current_row + 1;
            length[3] += 1;
            char *current_word = (char *)malloc(sizeof(char) * (length[3] + 1));
            for(int i = 0; i < length[3]; i++)
            {
                  current_word[i] = board_character[y_initial + i][x_initial];
            }
            current_word[length[3]] = '\0';
            if (check(current_word, WORD, num_of_word))
            {
                  printSolution(current_word);
                  free(current_word);
            }
            else
            {
                  if ((y_move + 1) == row)
                  {
                        free(current_word);
                        length[3] = 1;
                        locked[3] = 1;
                        Try(row, column, board_character, x_move, y_move, x_initial, y_initial, x_initial, y_initial, length, locked, WORD, num_of_word);
                  }
                  free(current_word);
                  Try(row, column, board_character, x_move, y_move, x_initial, y_initial, x_move, y_move, length, locked, WORD, num_of_word);
            }
      }

      if (locked[4] == 0 && ((current_row - 1 != -1) && (current_column + 1 != column)))
      {
            x_move = current_column + 1;
            y_move = current_row - 1;
            length[4] += 1;
            char *current_word = (char *)malloc(sizeof(char) * (length[4] + 1));
            for(int i = 0; i < length[4]; i++)
            {
                  current_word[i] = board_character[y_initial - i][x_initial + i];
            }
            current_word[length[4]] = '\0';
            if (check(current_word, WORD, num_of_word))
            {
                  printSolution(current_word);
                  free(current_word);
            }
            else
            {
                  if ((y_move - 1 == -1) || (x_move + 1 == column))
                  {
                        free(current_word);
                        length[4] = 1;
                        locked[4] = 1;
                        Try(row, column, board_character, x_move, y_move, x_initial, y_initial, x_initial, y_initial, length, locked, WORD, num_of_word);
                  }
                  free(current_word);
                  Try(row, column, board_character, x_move, y_move, x_initial, y_initial, x_move, y_move, length, locked, WORD, num_of_word);
            }
      }

      if (locked[5] == 0 && ((current_row + 1 != row) && (current_column + 1 != column)))
      {
            x_move = current_column + 1;
            y_move = current_row + 1;
            length[5] += 1;
            char *current_word = (char *)malloc(sizeof(char) * (length[5] + 1));
            for(int i = 0; i < length[5]; i++)
            {
                  current_word[i] = board_character[y_initial + i][x_initial + i];
            }
            current_word[length[5]] = '\0';
            if (check(current_word, WORD, num_of_word))
            {
                  printSolution(current_word);
                  free(current_word);
            }
            else
            {
                  if ((y_move + 1 == row) || (x_move + 1 == column))
                  {
                        free(current_word);
                        length[5] = 1;
                        locked[5] = 1;
                        Try(row, column, board_character, x_move, y_move, x_initial, y_initial, x_initial, y_initial, length, locked, WORD, num_of_word);
                  }
                  free(current_word);
                  Try(row, column, board_character, x_move, y_move, x_initial, y_initial, x_move, y_move, length, locked, WORD, num_of_word);
            }
      }

      if (locked[6] == 0 && ((current_row - 1 != -1) && (current_column - 1 != -1)))
      {
            x_move = current_column - 1;
            y_move = current_row - 1;
            length[6] += 1;
            char *current_word = (char *)malloc(sizeof(char) * (length[6] + 1));
            for(int i = 0; i < length[6]; i++)
            {
                  current_word[i] = board_character[y_initial - i][x_initial - i];
            }
            current_word[length[6]] = '\0';
            if (check(current_word, WORD, num_of_word))
            {
                  printSolution(current_word);
                  free(current_word);
            }
            else
            {
                  if ((y_move - 1 == -1) || (x_move - 1 == -1))
                  {
                        free(current_word);
                        length[6] = 1;
                        locked[6] = 1;
                        Try(row, column, board_character, x_move, y_move, x_initial, y_initial, x_initial, y_initial, length, locked, WORD, num_of_word);
                  }
                  free(current_word);
                  Try(row, column, board_character, x_move, y_move, x_initial, y_initial, x_move, y_move, length, locked, WORD, num_of_word);
            }
      }

      if (locked[7] == 0 && ((current_row + 1 != row) && (current_column - 1 != -1)))
      {
            x_move = current_column - 1;
            y_move = current_row + 1;
            length[7] += 1;
            char *current_word = (char *)malloc(sizeof(char) * (length[7] + 1));
            for(int i = 0; i < length[7]; i++)
            {
                  current_word[i] = board_character[y_initial + i][x_initial - i];
            }
            current_word[length[7]] = '\0';
            if (check(current_word, WORD, num_of_word))
            {
                  printSolution(current_word);
                  free(current_word);
            }
            else
            {
                  if ((y_move + 1 == row) || (x_move - 1 == -1))
                  {
                        free(current_word);
                        length[7] = 1;
                        locked[7] = 1;
                        Try(row, column, board_character, x_move, y_move, x_initial, y_initial, x_initial, y_initial, length, locked, WORD, num_of_word);
                  }
                  free(current_word);
                  Try(row, column, board_character, x_move, y_move, x_initial, y_initial, x_move, y_move, length, locked, WORD, num_of_word);
            }
      }
}

int main()
{
      char *filename = "C:\\Users\\admin\\OneDrive - Hanoi University of Science and Technology\\Documents\\C Programming\\.vscode\\C Basic\\Text Examples\\Board of Word.txt";
      FILE *boardFILE;
      if ((boardFILE = fopen(filename, "r")) == NULL)
      {
            printf("Can't open file.\n");
            exit(1);
      }
      int row, column;
      int newline_catch;
      fscanf(boardFILE, "%d %d", &row, &column);
      newline_catch = fgetc(boardFILE);

      char board_character[row][column];
      for (int i = 0; i < row; i++)
      {
            for (int j = 0; j < column; j++)
            {
                  fscanf(boardFILE, "%c", &board_character[i][j]);
            }
            newline_catch = fgetc(boardFILE);
      }
      long size = ftell(boardFILE);

      int num_of_word = 0;
      char word[90];
      while (fgets(word, 90, boardFILE) != 0)
      {
            num_of_word++;
      }

      char **WORD = (char **)malloc(sizeof(char *) * num_of_word);
      fseek(boardFILE, size, SEEK_SET);
      for (int i = 0; i < row; i++)
      {
            for (int j = 0; j < column; j++)
            {
                  printf("%c ", board_character[i][j]);
            }
            printf("\n");
      }

      int index = 0;
      while (fgets(word, 90, boardFILE) != 0)
      {
            WORD[index] = (char *)malloc(sizeof(char) * (strlen(word) + 1));
            word[strcspn(word, "\n")] = 0;
            strcpy(WORD[index], word);
            index++;
      }
      for (int i = 0; i < num_of_word; i++)
      {
            printf("%s\n", WORD[i]);
      }

      int y_move, x_move;
      int locked[8], length[8];
      for (int i = 0; i < 8; i++)
      {
            locked[i] = 0;
            length[i] = 1;
      }
      int count = 0;
      for (int i = 0; i < row; i++)
      {
            for (int j = 0; j < column; j++)
            {
                  Try(row, column, board_character, x_move, y_move, j, i, j, i, length, locked, WORD, num_of_word);
                  for (int k = 0; k < 8; k++)
                  {
                        locked[k] = 0;
                        length[k] = 1;
                  }
            }
      }
      fclose(boardFILE);
      return 0;
}
