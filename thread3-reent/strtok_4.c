#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

/*
 * thread 버전
 * 문제점: 멀티 쓰레드일 때, 제대로 동작하지 않음
 * 해결을 위해서 lock을 사용하면 되는 것 처럼 보이나,
 * 동시성이 깨진다.
 */

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *my_handler1(void *data)
{
	char hp[] = "010-1234-5678";
	char *p;

	pthread_mutex_lock(&mutex);
	p = strtok(hp, "-");

    while (p) {
		printf("hp: [%s]\n", p);
		p = strtok(0, "-");
		sleep(1);
	}
	pthread_mutex_unlock(&mutex);

	return 0;
}

void *my_handler2(void *data)
{
	char ip[] = "192.168.0.100";
	char *p;

	pthread_mutex_lock(&mutex);
	p = strtok(ip, ".");

    while (p) {
		printf("ip: [%s]\n", p);
		p = strtok(0, ".");
		sleep(1);
	}
	pthread_mutex_unlock(&mutex);

	return 0;
}

int main()
{
	pthread_t tid1;
	pthread_t tid2;

	pthread_create(&tid1, 0, my_handler1, 0);
	pthread_create(&tid2, 0, my_handler2, 0);

	pthread_join(tid1, 0);
	pthread_join(tid2, 0);

	return 0;
}
