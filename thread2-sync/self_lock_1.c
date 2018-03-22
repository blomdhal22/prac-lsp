#include <stdio.h>
#include <pthread.h>
/*
 * 셀프락을 쓸 일이 있겠는가?
 * 재귀를 써야하는 경우가 있다면 필요하다.
 */

pthread_mutex_t mutex;

int main()
{
	pthread_mutex_init(&mutex, 0);

	pthread_mutex_lock(&mutex);
	pthread_mutex_lock(&mutex);
	printf("Enter Critical section.\n");
	pthread_mutex_unlock(&mutex);

	return 0;
}
