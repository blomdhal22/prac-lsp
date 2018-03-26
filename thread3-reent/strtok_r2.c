#include <stdio.h>
#include <string.h>
#include <pthread.h>

/*
 * thread 버전
 */
void *my_handler(void *data)
{
	char hp[] = "010-1234-5678";
	char *p;
	char *saveptr;
	p = strtok_r(hp, "-", &saveptr);

    while (p) {
		printf("[%s]\n", p);
		p = strtok_r(0, "-", &saveptr);
	}

	return 0;
}

int main()
{
	pthread_t tid;
	pthread_create(&tid, 0, my_handler, 0);
	pthread_join(tid, 0);

	return 0;
}
