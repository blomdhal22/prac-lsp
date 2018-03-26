#include <unistd.h>

/*
 * 문제점: 잘동작하나, 1byte 단위로 읽기때문에, 비효율적임.
 * 개선  : 커널과는 4k단위로 읽어오고, 
           호출자에게는 1바이트로 리턴하는 함수 작성
 * 문제점 : static을 사용하면서, 멀티 스레드에 대한 대응이 안된다.
            재진입 문제가 발생한다.
 *
 */

#define MAXLINE	4096

static size_t my_read(int fd, char *ptr)
{
	static int read_cnt = 0;
	static char *read_ptr;
	static char read_buff[MAXLINE];

	if (read_cnt <= 0) {
		if ((read_cnt = read(fd, read_buff, sizeof(read_buff))) < 0) {
			return -1;
		} else if (read_cnt == 0) {
			return 0;
		}
		read_ptr = read_buff;
	}

	read_cnt--;
	*ptr = *read_ptr++;
	return 1;
}

ssize_t readline(int fd, void *vptr, size_t maxlen)
{
	int n, rc;
	char c, *ptr;
	ptr = vptr;

	for (n = 1; n < maxlen; n++) {
		if ((rc = my_read(fd, &c)) == 1 ) {
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
