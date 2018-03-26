#include <unistd.h>

/*
 * 문제점: 잘동작하나, 1byte 단위로 읽기때문에, 비효율적임.
 */
ssize_t readline(int fd, void *vptr, size_t maxlen)
{
	int n, rc;
	char c, *ptr;
	ptr = vptr;

	for (n = 1; n < maxlen; n++) {
		if ((rc = read(fd, &c, 1)) == 1 ) {
			*ptr++ = c;
			if (c == '\n')
				break;	/* newline is stoared life fgets() */
		} else if (rc == 0) {
			if (n == 1)
				return (0);		/* EOF, no data read*/
			else
				break;			/* EOF, some data was read */
		} else
			return -1;
	}

	*ptr = 0;		/* null terminate like fgets() */
	return n;
}
