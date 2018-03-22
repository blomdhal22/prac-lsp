#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

/*
 * 재진입 가능한 함수 구현
 *
 * 문제점: thread 별로 호출 횟수를 알고 싶으나 알 수 없음.
 * 해결  : caller로부터 자원을 전달 받음
 * 단점  : 사용자가 쓰기 불편하다. 자원할당 등.
 * 해결  : tls를 이용
 */

/*
result:
tsd=0x7f3ac00008c0
count=1
count=2
count=3
tsd=0x7f3ab80008c0
count=1
count=2
destructor=0x7f3ac00008c0
destructor=0x7f3ab80008c0

NOTE: 주소가 같을 수 있는데, 이것은 같은 메모리가 아니라, 
우연히 사용완료된 메모리 주소를 할당 받은 것이다.
 */
pthread_key_t key;

void foo()
{
	int *tsd;
	tsd = pthread_getspecific(key);
	
	if (tsd == 0) {
		tsd = calloc(1, sizeof(int));
		pthread_setspecific(key, tsd);
		printf("tsd=%p\n", tsd);
	}

	printf("count=%d\n", ++*tsd);
}

void *my_handler1(void *data)
{
	foo();
	foo();
	sleep(1);

	return 0;
}

void *my_handler2(void *data)
{
	foo();
	foo();
	foo();
	sleep(1);

	return 0;
}

void destructor(void *p)
{
	printf("destructor=%p\n", (int*)p);
	free(p);
}

int main()
{
	pthread_t tid1;
	pthread_t tid2;
	pthread_key_create(&key, destructor);

	pthread_create(&tid1, 0, my_handler1, 0);
	pthread_create(&tid2, 0, my_handler2, 0);

	pthread_join(tid1, 0);
	pthread_join(tid2, 0);

	return 0;
}
