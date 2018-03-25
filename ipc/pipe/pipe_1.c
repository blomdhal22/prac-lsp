#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define MSG_SIZE 16

char *msg1 = "hello, world #1";
char *msg2 = "hello, world #2";
char *msg3 = "hello, world #3";

int main()
{
	char inbuf[MSG_SIZE];
	int p[2], j;

	if (pipe(p) < 0) {
		perror("pipe call");
		exit(1);
	}

	/* write down pipe */
	write(p[1], msg1, MSG_SIZE);
	write(p[1], msg2, MSG_SIZE);
	write(p[1], msg3, MSG_SIZE);

	for (j = 0; j < 3; j++) {
		read(p[0], inbuf, MSG_SIZE);
		printf("%s\n", inbuf);
	}

	return 0;
}
