#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;
pthread_mutexattr_t attr;

int sum = 1;
int foo(int i)
{
	if (i == 0)
		return 1;

	pthread_mutex_lock(&mutex);
	printf("Enter Critical Section\n");

	sum = i*foo(i-1);
	pthread_mutex_unlock(&mutex);

	return sum;
}

int main()
{
	pthread_mutexattr_init(&attr);
	pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&mutex, &attr);

	foo(5);
	printf("sum = %d\n", sum);

	return 0;
}
