#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define MSG_SIZE 16

char *msg1 = "hello, world #1";
char *msg2 = "hello, world #2";
char *msg3 = "hello, world #3";

int main()
{
	char inbuf[1024];
	int p[2], j;
	int ret;

	if (pipe(p) < 0) {
		perror("pipe call");
		exit(1);
	}

	/* write down pipe */
	write(p[1], msg1, strlen(msg1));
	write(p[1], msg2, strlen(msg1));
	write(p[1], msg3, strlen(msg1));

	ret = read(p[0], inbuf, sizeof inbuf);
	inbuf[ret] = 0;

	printf("%s\n", inbuf);

	return 0;
}
