#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

/*
 * 재진입 가능한 함수 구현
 *
 * 문제점: thread 별로 호출 횟수를 알고 싶으나 알 수 없음.
 */
void foo(void)
{
	//int count = 0;
	static int count = 0;
	printf("count=%d\n", ++count);
}

void *my_handler1(void *data)
{
	foo();
	foo();

	return 0;
}

void *my_handler2(void *data)
{
	foo();
	foo();
	foo();

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
