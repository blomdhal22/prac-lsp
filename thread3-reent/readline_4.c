#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

/*
 * 문제점: 잘동작하나, 1byte 단위로 읽기때문에, 비효율적임.
 * 개선  : 커널과는 4k단위로 읽어오고, 
 *         호출자에게는 1바이트로 리턴하는 함수 작성
 * 문제점 : static을 사용하면서, 멀티 스레드에 대한 대응이 안된다.
 *          재진입 문제가 발생한다.
 * 개선   : call by address 방식으로 구현
 * 문제점 : 그러나, API 사용이 어렵고, 호출자가 자원관리를 해야 한다.
 *          TLS를 이용하면, 개선 가능하다.
 * 개선   : TLS 적용 버전
 *          고려할 것은, 호출하는 쪽에서 key 생성을 하지 않도록 한다.
 *
 */

#define MAXLINE	4096

typedef struct {
	int		rl_cnt;			/* initialize to 0 */
	char	*rl_bufptr;		/* initialize to rl_buf */
	char 	rl_buf[MAXLINE];
} Rline;

static pthread_key_t rl_key;
static pthread_once_t rl_once = PTHREAD_ONCE_INIT;

static void readline_dest(void *ptr)
{
	free(ptr);	
}

static void readline_once(void)
{
	pthread_key_create(&rl_key, readline_dest);
}

static size_t my_read(int fd, char *ptr, Rline *tsd)
{
	if (tsd->rl_cnt <= 0) {
		if ((tsd->rl_cnt = read(fd, tsd->rl_buf, sizeof(tsd->rl_buf))) < 0) {
			return -1;
		} else if (tsd->rl_cnt == 0) {
			return 0;
		}
		tsd->rl_bufptr = tsd->rl_buf;
	}

	tsd->rl_cnt--;
	*ptr = *tsd->rl_bufptr++;
	return 1;
}

ssize_t readline(int fd, void *vptr, size_t maxlen)
{
	int n, rc;
	char c, *ptr;
	Rline *tsd;

	ptr = vptr;

	pthread_once(&rl_once, readline_once);
	if ((tsd = pthread_getspecific(rl_key)) == NULL) {
		tsd = calloc(1, sizeof(Rline));	/* init to 0 */
		pthread_setspecific(rl_key, tsd);
	}
	
	for (n = 1; n < maxlen; n++) {
		if ((rc = my_read(fd, &c, tsd)) == 1 ) {
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
