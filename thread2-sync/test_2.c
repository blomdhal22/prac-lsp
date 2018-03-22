#include <pthread.h>
#include <stdio.h>

#define MAX_THREAD 4

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int sum = 0;
void *thread_routine(void *arg)
{
	int local, i;

	for (i=0; i<10000000/MAX_THREAD; i++) {
		pthread_mutex_lock(&lock);
		local = sum;
		local++;
		sum = local;
		pthread_mutex_unlock(&lock);
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
