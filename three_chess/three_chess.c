
#include <stdio.h>
#include <stdlib.h>

#include "three_chess_lib.h"
#include "three_chess_decision.h"

steps history;
char board[5][5];

int main(int argc, char *argv[])
{
	int temp[2];
	int result;

	boardinit();
	putone(1, 1);
	//result=decision(temp);
	//putone(*temp,temp[1]);

	printf("Please input like this (a,1)-7 (a,2)-8 (c,1)-1\n\n");
	while (flush()) {
		input();
		if (iswin())
			continue;
		result = decision(temp);
		putone(*temp, temp[1]);
	}
	return 0;
}
