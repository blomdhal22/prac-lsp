#include <stdio.h>
#include <stdlib.h>

// # a.out a.txt
// argv[0] argv[1]
// argc=2
int main(int argc, char **argv)
{
	FILE *fp;
	int ch, flag; 
	int cnt[3] = {0, };

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

	printf("%d %d %d %s\n", cnt[0], cnt[1], cnt[2], argv[1]);

	fclose(fp);
	return 0;
}
