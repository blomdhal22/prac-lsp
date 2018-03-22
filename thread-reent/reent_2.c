#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

/*
 * 재진입 가능한 함수 구현
 *
 * 문제점: thread 별로 호출 횟수를 알고 싶으나 알 수 없음.
 * 해결  : caller로부터 자원을 전달 받음
 * 단점  : 사용자가 쓰기 불편하다. 자원할당 등.
 */
void foo(int *count)
{
	printf("count=%d\n", ++*count);
}

void *my_handler1(void *data)
{
	int c = 0;
	foo(&c);
	foo(&c);

	return 0;
}

void *my_handler2(void *data)
{
	int c = 0;
	foo(&c);
	foo(&c);
	foo(&c);

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
