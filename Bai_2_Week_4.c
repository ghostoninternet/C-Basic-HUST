#include <stdio.h>
#include <stdlib.h>

int flag = 0;

void printSolution(int row, int column, int row_move, int column_move, int x_end, int y_end, int marked[row][column], int BOARD[row][column])
{
      for (int i = 0; i < row; i++)
      {
            for (int j = 0; j < column; j++)
            {
                  if (marked[i][j] == 1)
                  {
                        BOARD[i][j] = 8;
                  }
            }
      }
      printf("Found the destination! %d %d\n", row_move, column_move);
      flag = 1;
}

void Try(int row, int column, int BOARD[row][column], int x_start, int y_start, int x_end, int y_end, int marked[row][column], int row_move, int column_move)
{

      if (((y_start + 1) != (column)) && marked[x_start][y_start + 1] == 0 && BOARD[x_start][y_start + 1] != 0)
      {
            row_move = x_start;
            column_move = y_start + 1;
            marked[row_move][column_move] = 1;
            if (row_move == x_end && column_move == y_end)
            {
                  printSolution(row, column, row_move, column_move, x_end, y_end, marked, BOARD);
            }
            else
            {
                  Try(row, column, BOARD, row_move, column_move, x_end, y_end, marked, row_move, column_move);
            }
      }
      if (((x_start + 1) != (row)) && marked[x_start + 1][y_start] == 0 && BOARD[x_start + 1][y_start] != 0)
      {
            row_move = x_start + 1;
            column_move = y_start;
            marked[row_move][column_move] = 1;
            if (row_move == x_end && column_move == y_end)
            {
                  printSolution(row, column, row_move, column_move, x_end, y_end, marked, BOARD);
            }
            else
            {
                  Try(row, column, BOARD, row_move, column_move, x_end, y_end, marked, row_move, column_move);
            }
      }
      if (((y_start - 1) != -1) && marked[x_start][y_start - 1] == 0 && BOARD[x_start][y_start - 1] != 0)
      {
            row_move = x_start;
            column_move = y_start - 1;
            marked[row_move][column_move] = 1;
            if (row_move == x_end && column_move == y_end)
            {
                  printSolution(row, column, row_move, column_move, x_end, y_end, marked, BOARD);
            }
            else
            {
                  Try(row, column, BOARD, row_move, column_move, x_end, y_end, marked, row_move, column_move);
            }
      }
      if (((x_start - 1) != -1) && marked[x_start - 1][y_start] == 0 && BOARD[x_start - 1][y_start] != 0)
      {
            row_move = x_start - 1;
            column_move = y_start;
            marked[row_move][column_move] = 1;
            if (row_move == x_end && column_move == y_end)
            {
                  printSolution(row, column, row_move, column_move, x_end, y_end, marked, BOARD);
            }
            else
            {
                  Try(row, column, BOARD, row_move, column_move, x_end, y_end, marked, row_move, column_move);
            }
      }
}

int main()
{
      char *filename = "C:\\Users\\admin\\OneDrive - Hanoi University of Science and Technology\\Documents\\C Programming\\.vscode\\C Basic\\Text Examples\\the maze 1.txt";
      FILE *MAZE;
      if ((MAZE = fopen(filename, "r")) == NULL)
      {
            printf("Can't open file.\n");
            exit(1);
      }
      int row, column;
      fscanf(MAZE, "%d %d", &row, &column);
      int BOARD[row][column];

      for (int i = 0; i < row; i++)
      {
            for (int j = 0; j < column; j++)
            {
                  fscanf(MAZE, "%d", &BOARD[i][j]);
            }
      }

      int row_move, column_move;

      int x_start, y_start;
      fscanf(MAZE, "%d %d", &x_start, &y_start);
      int x_end, y_end;
      fscanf(MAZE, "%d %d", &x_end, &y_end);
      fclose(MAZE);

      int marked[row][column];
      for (int i = 0; i < row; i++)
      {
            for (int j = 0; j < column; j++)
            {
                  marked[i][j] = 0;
            }
      }
      marked[0][0] = 1;

      for (int i = 0; i < row; i++)
      {
            for (int j = 0; j < column; j++)
            {
                  printf("%d ", BOARD[i][j]);
            }
            printf("\n");
      }
      Try(row, column, BOARD, x_start, y_start, x_end, y_end, marked, row_move, column_move);
      for (int i = 0; i < row; i++)
      {
            for (int j = 0; j < column; j++)
            {
                  printf("%d ", BOARD[i][j]);
            }
            printf("\n");
      }
      if (flag == 0)
      {
            printf("Can't reach the destination!\n");
      }
      return 0;
}