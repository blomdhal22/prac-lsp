#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

/*
 * 1. 문제점 blocking 된다.
 * 2. 해결, fork 이용
 * 3. 문제점, 오버헤드가 발생한다.
 * 4. 해결, thread이용
 * 5. 문제점, 동기화 문제 발생, 마지막에 입력한 기준으로 출력
 * 6. 해결, thread에 전달 인자 생성해서 전달
 * 7. 문제점, 매번 thread를 생성해야 한다. 자원 효율이 떨어짐
 * 8. 해결, worker thread를 생성해서 큐에 자료가 입력될 때 마다 깨어나서 작업
 *    => mutex, condtion, queue(list)가 필요
 */

struct alarm_entry {
	int sec;
	char msg[64];
};

void *alarm_thread(void *data)
{
	/*
	 * main thread에서 기다리지 않기 위해
	 * thread detach 해 주어야 함.
	 * 독립적인 쓰레드
	 */
	struct alarm_entry *p = (struct alarm_entry*)data;
	pthread_detach(pthread_self());
	sleep(p->sec);
	printf("(%d) %s\n", p->sec, p->msg);
	free(p);
	return 0;
}

int main()
{
	pthread_t thread;
	char line[126];
	struct alarm_entry *p;
	
	while(1) {
		printf("Alarm> ");
		fgets(line, sizeof line, stdin); // 10 hello
		// 2 hello world
		p = (struct alarm_entry*)malloc(sizeof(struct alarm_entry));
		sscanf(line, "%d %64[^\n]", &p->sec, p->msg);
		pthread_create(&thread, 0, alarm_thread, p);
	}

	return 0;
}
