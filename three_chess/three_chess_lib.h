
#ifndef TRICHESS_LIB
#define TRICHESS_LIB

#define EDGE '\0'
#define EMPTY '-'
#define WHITE 'O'
#define BLACK 'X'

typedef unsigned char byte;
typedef struct trichess_history {
	byte steps[9][2];
	int n;
} steps;

extern steps history;
extern char board[5][5];

/* to initialize the chess board */
void boardinit();
/* return 0 or 1 means the game is over or not
 *  to print the lastest chess board on screen */
int flush();
/* let the user to input an point */
void input();
/* return 0 or 1
 *  means the chess pieces you want to put on chess board is legal or not
 *  if it is legali, it will be put on the board */
int putone(int i, int j);
/* return 0 or 1
 * roll back a step , only if there is no chess piece on the board ,it return 0*/
int backone();

void boardinit()
{
	int i, j;
	history.n = 0;
	for (i = 0; i < 5; i++)
		board[0][i] = board[4][i] = board[i][0] = board[i][4] = 0;
	for (i = 1; i < 4; i++)
		for (j = 1; j < 4; j++)
			board[i][j] = EMPTY;
}

int flush()
{
	int i, j;
	int result;
	printf("   ");
	for (i = 1; i < 4; i++)
		printf(" %d", i);
	printf("\n");
	for (i = 1; i < 4; i++) {
		printf(" %c ", 'a' - 1 + i);
		for (j = 1; j < 4; j++)
			printf(" %c", board[i][j]);
		printf("\n");
	}
	printf("\n");
	printf("steps:%2d", history.n);
	if (iswin()) {
		printf("\n %s\n\n",
		       history.
		       n & 1 ? "You lose the game..." :
		       "Great, you beated the coputer!");
#ifdef WIN32
		system("pause");
#endif
		return 0;
	} else if (history.n == 9) {
		printf("\ntie\n\n");
		return 0;
	} else {
		printf("     waiting for  %s \n\n", history.n & 1 ? "O" : "X");
		return 1;
	}
}

void input()
{
	char c = '\n';
	while (isspace(c))
		c = getchar();
	if (tolower(c) == 'q')
		backone();
	else if (isdigit(c)) {
		c -= '0';
		if (!putone((12 - c) / 3, (c + 2) % 3 + 1))
			input();
	} else
		input();

}

int putone(int i, int j)
{
	if (board[i][j] == EMPTY)
		return history.steps[history.n][0] =
		    i, history.steps[history.n++][1] = j, board[i][j] =
		    history.n & 1 ? BLACK : WHITE, 1;
	else
		return 0;
}

int backone()
{
	if (history.n) {
		history.n--;
		int i = history.n, j = history.steps[i][1];
		i = history.steps[i][0];
		board[i][j] = EMPTY;
		return 1;
	}
	return 0;
}

#endif
