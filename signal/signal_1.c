#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

void catchint(int signo)
{
	printf("SIGINT Receive\n");
}

int main()
{
	signal(SIGINT, catchint);

	printf("sleep call #1\n");	sleep(5);
	printf("sleep call #2\n");	sleep(5);
	printf("sleep call #3\n");	sleep(5);
	printf("sleep call #4\n");	sleep(5);
	printf("Exit\n");

	return 0;

}
