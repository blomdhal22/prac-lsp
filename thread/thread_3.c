#include <stdio.h>
#include <pthread.h>

/*
 * result:
 * child  : local=11
 * parent : local=11
 *
 */

void *foo(void *data)
{
	printf("child  : local=%d\n", ++*((int*)data));
	return 0;
}

int main()
{
	int local = 10;
	pthread_t thread;
	pthread_create(&thread, 0, foo, &local);
	pthread_join(thread, 0);

	printf("parent : local=%d\n", local);

	return 0;
}
