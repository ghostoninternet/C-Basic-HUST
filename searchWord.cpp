#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

const int TOTAL_WORDS = 370100;
const int WORD_LEN = 30;

void standalizeWord(char *Word)
{
	int i = 0;
	while (i < strlen(Word))
	{
		if (Word[i] == '\r' || Word[i] == '\n')
		{
			Word[i] = '\0';
			break;
		}
		else
			i++;
	}
}
char **loadDict(char *filename, int *dict_size)
{
	char **Words;
	int i, total_size = 0;
	;
	char buff[50];
	FILE *fPtr;
	fPtr = fopen(filename, "r");
	if (fPtr == NULL)
	{
		perror("Error in opening file");
		return (NULL);
	}
	// cap phat mang con tro
	Words = (char **)malloc(sizeof(char *) * TOTAL_WORDS);

	i = 0;
	while (fgets(buff, WORD_LEN, fPtr) != NULL)
	{
		standalizeWord(buff);
		Words[i] = (char *)malloc(sizeof(char) * (strlen(buff) + 1));
		strcpy(Words[i], buff);
		// puts(Words[i]);
		total_size = total_size + strlen(buff) + 1;
		i++;
	}
	fclose(fPtr);
	// printf("Total Read: %d\n",i);
	// printf("Total size: %d\n",total_size);
	*dict_size = i;
	return Words;
}

void freeMem(char **pointer)
{
	// giai phong bo nho
	for (int i = 0; i < TOTAL_WORDS; i++)
		free(pointer[i]);
	free(pointer);
}
int checkWord(char *word, char **Dict, int dict_size)
{
	for (int i = 0; i < dict_size; i++)
		if (strcmp(word, Dict[i]) == 0)
			return 1;
	return 0;
}

char table[7][10] = {
    'A', 'S', 'S', 'H', 'S', 'W', 'E', 'E', 'M', 'T',
    'M', 'H', 'S', 'U', 'N', 'D', 'A', 'Y', 'I', 'H',
    'S', 'T', 'A', 'S', 'U', 'N', 'B', 'S', 'R', 'G',
    'A', 'S', 'S', 'T', 'A', 'B', 'L', 'E', 'R', 'E',
    'T', 'T', 'S', 'A', 'T', 'N', 'G', 'M', 'O', 'N',
    'S', 'T', 'A', 'B', 'L', 'E', 'O', 'N', 'R', 'M',
    'M', 'O', 'R', 'L', 'S', 'N', 'E', 'R', 'M', 'I'};
char d1[300][300], d2[300][300], hang[300][300], cot[300][300], x[300], str[2000][2000];
int i, j, k, m = 0, n = 0, a, b, c, d;

int main()
{
	char **Dict;
	char lookupW[30];
	int dict_size;
	char filename[] = "C:\\Users\\admin\\OneDrive - Hanoi University of Science and Technology\\Documents\\C Programming\\.vscode\\C Basic\\Text Examples\\words_alpha.txt";
	Dict = loadDict(filename, &dict_size);
	for (i = 0; i < 7; i++)
	{
		for (j = 0; j < 10; j++)
		{
			table[i][j] = tolower(table[i][j]);
		}
	}
	/*
	for (i=0;i<7;i++)
	for (j=0;j<10;j++) {
		if (j==9) printf("%c\n",table[i][j]);
		else printf("%c ",table[i][j]);
	};
	*/
	// printf("==================================================\n");
	//  duong cheo xuoi
	for (a = 1; a <= 16; a++)
	{
		for (i = 0; i < 7; i++)
		{
			for (j = 9; j >= 0; j--)
			{
				if (i - j + 10 == a)
				{
					d1[a][m] = table[i][j];
					m++;
				}
			}
		};
		// n++;
		m = 0;
	}
	// liet ke duong cheo xuoi
	for (i = 1; i <= 16; i++)
	{
		for (k = 1; k <= strlen(d1[i]); k++)
		{
			for (j = 0; j <= strlen(d1[i]) - k; j++)
			{
				strncpy(str[i], d1[i] + j, k);
				if (checkWord(str[i], Dict, dict_size))
				{
					for (n = 0; n < strlen(str[i]); n++)
					{
						str[i][n] = toupper(str[i][n]);
					}
					printf("%s\n", str[i]);
				}
				// else printf("Tu %s KHONG co trong tu dien!\n",str[i]);
			}
		}
	};
	for (i = 1; i <= 16; i++)
	{
		for (k = 1; k <= strlen(d1[i]); k++)
		{
			for (j = strlen(d1[i]) - k; j >= 0; j--)
			{
				strncpy(str[i], d1[i] + j, k);
				if (checkWord(str[i], Dict, dict_size))
				{
					for (n = 0; n < strlen(str[i]); n++)
					{
						str[i][n] = toupper(str[i][n]);
					}
					printf("%s\n", str[i]);
				}
				// else printf("Tu %s KHONG co trong tu dien!\n",str[i]);
			}
		}
	};

	// printf("==================================================\n");

	// duong cheo nguoc
	m = 0;
	for (k = 1; k <= 16; k++)
	{
		for (i = 0; i < 7; i++)
		{
			for (j = 0; j < 10; j++)
			{
				if (i + j + 1 == k)
				{
					d2[k][m] = table[i][j];
					m++;
				}
			}
		}
		m = 0;
	}

	// liet ke duong cheo nguoc
	for (i = 1; i <= 16; i++)
	{
		for (k = 1; k <= strlen(d2[i]); k++)
		{
			for (j = 0; j <= strlen(d2[i]) - k; j++)
			{
				strncpy(str[i], d2[i] + j, k);
				if (checkWord(str[i], Dict, dict_size))
				{
					for (n = 0; n < strlen(str[i]); n++)
					{
						str[i][n] = toupper(str[i][n]);
					}
					printf("%s\n", str[i]);
				}
				// else printf("Tu %s KHONG co trong tu dien!\n",str[i]);
			}
		}
	};
	for (i = 1; i <= 16; i++)
	{
		for (k = 1; k <= strlen(d2[i]); k++)
		{
			for (j = strlen(d2[i]) - k; j >= 0; j--)
			{
				strncpy(str[i], d2[i] + j, k);
				if (checkWord(str[i], Dict, dict_size))
				{
					for (n = 0; n < strlen(str[i]); n++)
					{
						str[i][n] = toupper(str[i][n]);
					}
					printf("%s\n", str[i]);
				}
				// else printf("Tu %s KHONG co trong tu dien!\n",str[i]);
			}
		}
	};

	// printf("==================================================\n");
	m = 0;

	// hang ngang
	for (i = 0; i < 7; i++)
	{
		for (j = 0; j < 10; j++)
		{
			hang[i][j] = table[i][j];
		}
	}

	// liet ke hang ngang
	for (i = 0; i < 7; i++)
	{
		for (k = 1; k <= strlen(hang[i]); k++)
		{
			for (j = 0; j <= strlen(hang[i]) - k; j++)
			{
				strncpy(str[i], hang[i] + j, k);
				if (checkWord(str[i], Dict, dict_size))
				{
					for (n = 0; n < strlen(str[i]); n++)
					{
						str[i][n] = toupper(str[i][n]);
					}
					printf("%s\n", str[i]);
				}
				// else printf("Tu %s KHONG co trong tu dien!\n",str[i]);
			}
		}
	}
	for (i = 0; i < 7; i++)
	{
		for (k = 1; k <= strlen(hang[i]); k++)
		{
			for (j = strlen(hang[i]) - k; j >= 0; j--)
			{
				strncpy(str[i], hang[i] + j, k);
				if (checkWord(str[i], Dict, dict_size))
				{
					for (n = 0; n < strlen(str[i]); n++)
					{
						str[i][n] = toupper(str[i][n]);
					}
					printf("%s\n", str[i]);
				}
				// else printf("Tu %s KHONG co trong tu dien!\n",str[i]);
			}
		}
	}

	// cot doc
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 7; j++)
		{
			cot[i][j] = table[j][i];
		}
	}

	// liet ke cot doc
	for (i = 0; i < 10; i++)
	{
		for (k = 1; k <= strlen(cot[i]); k++)
		{
			for (j = 0; j <= strlen(cot[i]) - k; j++)
			{
				strncpy(str[i], cot[i] + j, k);
				if (checkWord(str[i], Dict, dict_size))
				{
					for (n = 0; n < strlen(str[i]); n++)
					{
						str[i][n] = toupper(str[i][n]);
					}
					printf("%s\n", str[i]);
				}
				// else printf("Tu %s KHONG co trong tu dien!\n",str[i]);
			}
		}
	}
	for (i = 0; i < 10; i++)
	{
		for (k = 1; k <= strlen(cot[i]); k++)
		{
			for (j = strlen(cot[i]) - k; j >= 0; j--)
			{
				strncpy(str[i], cot[i] + j, k);
				if (checkWord(str[i], Dict, dict_size))
				{
					for (n = 0; n < strlen(str[i]); n++)
					{
						str[i][n] = toupper(str[i][n]);
					}
					printf("%s\n", str[i]);
				}
				// else printf("Tu %s KHONG co trong tu dien!\n",str[i]);
			}
		}
	}
	return 0;
}
