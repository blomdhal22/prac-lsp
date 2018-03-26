#include <unistd.h>

/*
 * 문제점: 잘동작하나, 1byte 단위로 읽기때문에, 비효율적임.
 * 개선  : 커널과는 4k단위로 읽어오고, 
 *         호출자에게는 1바이트로 리턴하는 함수 작성
 * 문제점 : static을 사용하면서, 멀티 스레드에 대한 대응이 안된다.
 *          재진입 문제가 발생한다.
 * 개선   : call by address 방식으로 구현
 * 문제점 : 그러나, API 사용이 어렵고, 호출자가 자원관리를 해야 한다.
 *          TLS를 이용하면, 개선 가능하다.
 *
 */

#define MAXLINE	4096

typedef struct {
	int read_cnt;
	char *read_ptr;
	char read_buff[MAXLINE];
} Rline;

static size_t my_read(int fd, char *ptr, Rline *buff)
{
	if (buff->read_cnt <= 0) {
		if ((buff->read_cnt = read(fd, buff->read_buff, sizeof(buff->read_buff))) < 0) {
			return -1;
		} else if (buff->read_cnt == 0) {
			return 0;
		}
		buff->read_ptr = buff->read_buff;
	}

	buff->read_cnt--;
	*ptr = *buff->read_ptr++;
	return 1;
}

ssize_t readline(int fd, void *vptr, size_t maxlen)
{
	int n, rc;
	char c, *ptr;
	Rline buff = {0,};
	ptr = vptr;

	for (n = 1; n < maxlen; n++) {
		if ((rc = my_read(fd, &c, &buff)) == 1 ) {
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
