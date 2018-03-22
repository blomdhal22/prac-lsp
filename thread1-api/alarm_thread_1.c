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
 */

int sec;
char line[128];
char msg[64];

void *alarm_thread(void *data)
{
	/*
	 * main thread에서 기다리지 않기 위해
	 * thread detach 해 주어야 함.
	 * 독립적인 쓰레드
	 */
	pthread_detach(pthread_self());
	sleep(sec);
	printf("(%d) %s\n", sec, msg);
	return 0;
}

int main()
{
	pthread_t thread;
	
	while(1) {
		printf("Alarm> ");
		fgets(line, sizeof line, stdin); // 10 hello
		// 2 hello world
		sscanf(line, "%d %64[^\n]", &sec, msg);
		pthread_create(&thread, 0, alarm_thread, 0);
	}
	return 0;
}
