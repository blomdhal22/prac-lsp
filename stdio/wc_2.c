#include <stdio.h>
#include <stdlib.h>

int get_width(int num);

// # a.out a.txt
// argv[0] argv[1]
// argc=2
int main(int argc, char **argv)
{
	FILE *fp;
	int ch, flag; 
	int cnt[3] = {0, };
	int width=0, i, w;

	fp = fopen(argv[1], "r");

	while ((ch = fgetc(fp)) != EOF) {
		if (ch == '\n')
			cnt[0]++;	/* line count */

		if (ch != '\n' && ch != ' ' && ch != '\t') {
			if (flag == 0) {
				cnt[1]++;   /* word count */
				flag = 1;
			}
		} else {
			flag = 0;
		}

		cnt[2]++;		/* character count */
	}

	for (i=0; i<3; i++) {
		w = get_width(cnt[i]);
		if (width < w)
			width = w;
	}

	printf("%*d %*d %*d %s\n"
			, width, cnt[0]
			, width, cnt[1]
			, width, cnt[2]
			, argv[1]);

	fclose(fp);
	return 0;
}

int get_width(int num)
{
	int i;

	// num=1234
	// num=123
	// num=12
	// num=1
	// num-0
	for (i=0; num != 0; i++) {
		num /= 10;	
	}

	return i;
}
