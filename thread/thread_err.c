#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

/*
 * thread인 경우, errno가 아닌, 리턴값을 기준으로 에러 처리를 해야 한다.
 */
int main()
{
	int ret;
	pthread_t thread = 0;
	ret = pthread_join(thread, 0);

	printf("ret=%d\n", ret);

	if (ret > 0) {
		printf("errno = %d\n", errno);	
		printf("strerr = %s\n", strerror(ret));	
	}

	return 0;
}
