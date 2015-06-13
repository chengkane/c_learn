
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define is(x) ((x)%4==0&&((x)%100||(x)%400==0))

int step(int s, int len);
int main(int argc, char *argv[])
{
	int a, b, c, x, y;
	int carry = 2, flag;
	int i, j, k, l;
	int temp;
	int m[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	scanf("%d%d%d%d%d", &a, &b, &c, &x, &y);
	b--;
	k = m[a - 1];
	for (i = 0, j = 0; i < a - 1; i++)
		j += m[i];
	l = j;

	for (i = 1850; i < x; i++)
		carry = step(carry, 365 + is(i));
	for (; i <= y; i++) {
		if (a == 2) {
			k = 28 + is(i);
		} else if (a > 2) {
			l = j + is(i);
		}
		temp = step(carry, l);
		temp = (c + 7 - temp) % 7 + 1 + b * 7;
		if (temp <= k)
			printf("%d/%02d/%02d\n", i, a, temp);
		else
			puts("none");
		carry = step(carry, 365 + is(i));
	}

	return 0;
}

int step(int s, int len)
{
	return (s + len - 1) % 7 + 1;
}
