#include <pthread.h>
#include <unistd.h>
#include "errors.h"

void *thread_routine(void *arg)
{
	while (1) {
		printf("child\n");
		sleep(1);
	}

	return 0;
}

int main(int argc, char **argv)
{
	pthread_t thread_id;
	void *thread_result;
	int status;

	DPRINTF(("hello world\n")); 

	status = pthread_create(&thread_id, 0, thread_routine, 0);

	if (status != 0)
		err_abort(status, "Create thread");

	/*
	status = pthread_join(thread_id, &thread_result);
	if (status != 0)
		err_abort(status, "Join thread");
	
	if (thread_result == 0) {
		DPRINTF(("finish child\n"));	
	}
	*/

	/* main thread만 종료되고, process는 여전히 유지 된다.
	 * 만약, exit()되었다면, child도 같이 종료 된다.
	 * $ ps -eLF로 확인
	 */
	pthread_exit(0);
	printf("main : after\n");

	return 0;
}
