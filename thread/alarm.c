#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/*
 * 1. 문제점 blocking 된다.
 */
int main()
{
	int sec;
	char line[128];
	char msg[64];

	while(1) {
		printf("Alarm> ");
		fgets(line, sizeof line, stdin); // 10 hello
		// 2 hello world
		sscanf(line, "%d %64[^\n]", &sec, msg);
		sleep(sec);
		printf("(%d) %s\n", sec, msg);
	}
	return 0;
}
