#include <pthread.h>
#include <stdio.h>

#define MAX_THREAD 4

int sum = 0;
int flag = 0;
void *thread_routine(void *arg)
{
	int i;
	/*
	 * mov    0x200947(%rip),%eax        # 601054 <sum>
	 * add    $0x1,%eax
	 * mov    %eax,0x20093e(%rip)        # 601054 <sum>
	 */

	for (i=0; i<100000000/MAX_THREAD; i++) {
		while(flag) ;
		flag = 1;
		sum++;
		flag = 0;
	}

	return arg;
}

int main(void)
{
	pthread_t thread_id[MAX_THREAD];
	void *thread_result;
	int status, i;

	for(i=0; i<MAX_THREAD; i++)
		status = pthread_create(&thread_id[i], 0, thread_routine, 0);

	for(i=0; i<MAX_THREAD; i++)
		status = pthread_join(thread_id[i], &thread_result);

	printf("sum=%d\n", sum);

	return 0;
}
