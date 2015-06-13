
#ifndef TRICHESS_DECISION_
#define TRICHESS_DECISION_

#define elif else if
#define TOWIN 0
#define TIED 1
#define LOSE 2

extern char board[5][5];
extern steps history;

/* return 1 or 0
 * check the game is over or not
 * */
int iswin();
/* return TOEIN TIED LOSE
 * the best point was written in result
 * */
int decision(int *result);

int decision(int *result)
{
	int i, j, k, l;
	int flag, temp;
	int tie[3] = { 0 };
	if (history.n == 8) {
		for (i = 1; i < 4; i++) {
			for (j = 1; j < 4; j++) {
				if (putone(i, j)) {
					*result = i, result[1] = j;
					temp = iswin();
					backone();
					if (!temp) {
						return TIED;
					} else {
						return TOWIN;
					}
				}
			}
		}
	}

	for (i = 1; i < 4; i++) {
		for (j = 1; j < 4; j++) {
			if (putone(i, j)) {
				if (iswin()) {
					*result = i, result[1] = j;
					backone();
					return TOWIN;
				} else {
					flag = TOWIN;
					for (k = 1; k < 4 && flag != LOSE; k++) {
						for (l = 1;
						     l < 4 && flag != LOSE;
						     l++) {
							if (putone(k, l)) {
								if (iswin()
								    || (temp =
									decision
									(result))
								    == LOSE) {
									flag =
									    LOSE;
									backone
									    ();
									continue;
								}
								if (temp ==
								    TIED) {
									flag =
									    TIED;
								}
								backone();
							}
						}
					}
					backone();
					if (flag == TOWIN) {
						*result = i, result[1] = j;
						return TIED;
					}
					elif(flag == TIED) {
						*tie = 1, tie[1] = i, tie[2] =
						    j;
					}
				}
			}
		}
	}
	if (*tie) {
		*result = tie[1], result[1] = tie[2];
		return TIED;
	}
	return LOSE;
}

int iswin()
{
	int i, j;
	int result;
	for (i = 1; i < 4; i++) {
		result = board[i][1];
		if (result == EMPTY)
			continue;
		for (j = 2; j < 4; j++)
			if (board[i][j] != result) {
				result = 0;
				break;
			}
		if (result)
			return 1;
	}
	for (i = 1; i < 4; i++) {
		result = board[1][i];
		if (result == EMPTY)
			continue;
		for (j = 2; j < 4; j++)
			if (board[j][i] != result) {
				result = 0;
				break;
			}
		if (result)
			return 1;
	}
	if (board[1][1] != EMPTY && board[1][1] == board[2][2]
	    && board[1][1] == board[3][3])
		return 1;
	if (board[1][3] != EMPTY && board[1][3] == board[2][2]
	    && board[1][3] == board[3][1])
		return 1;
	return 0;
}

#endif
