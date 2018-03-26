#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define MAXBUFF	1024

void client(int readfd, int writefd)
{
	char buff[MAXBUFF];
	int n;

	if (fgets(buff, MAXBUFF, stdin) == NULL)
		printf("client: filename read error\n");

	n = strlen(buff);
	if (buff[n-1] == '\n')
		n--;

	if (write(writefd, buff, n) != n)
		printf("client: filename write error\n");

	while ((n = read(readfd, buff, MAXBUFF)) > 0) {
		if (write(1, buff, n) != n)
			printf("client: data write error\n");
	}

	if (n < 0)
		printf("client: data read error\n");
}
