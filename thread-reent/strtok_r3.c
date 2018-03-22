#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

/*
 * thread 버전
 * 문제점: 멀티 쓰레드일 때, 제대로 동작하지 않음
 * 개선  : strtor_r, 재진입 가능한 함수를 이용해서 구현
 */
void *my_handler1(void *data)
{
	char hp[] = "010-1234-5678";
	char *p;
	char *save;
	p = strtok_r(hp, "-", &save);

    while (p) {
		printf("hp: [%s]\n", p);
		p = strtok_r(0, "-", &save);
		sleep(1);
	}

	return 0;
}

void *my_handler2(void *data)
{
	char ip[] = "192.168.0.100";
	char *p;
	char *save;
	
	p = strtok_r(ip, ".", &save);

    while (p) {
		printf("ip: [%s]\n", p);
		p = strtok_r(0, ".", &save);
		sleep(1);
	}

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
