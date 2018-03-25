#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#define MAXBUFF	1024

void server(int readfd, int writefd)
{
	char buff[MAXBUFF];
	int n, fd;
	extern int errno;

	if ((n = read(readfd, buff, MAXBUFF)) <= 0)		/* recv file name */
		printf("server: filename read error\n");
	buff[n] = '\0';

	if ((fd = open(buff, O_RDONLY)) < 0) {
		strcat(buff, " can't open\n");
		n = strlen(buff);
		if (write(writefd, buff, n) != n)			/* send error msg */
			printf("server: errmesg write error\n");
	} else {
		while ((n = read(fd, buff, MAXBUFF)) > 0)
			if (write(writefd, buff, n) != n)		/* send file contents */
				printf("server: data write error\n");
	}

	return;
}
