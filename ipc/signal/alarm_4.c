#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void alm(int signo)
{
	printf("SIGALRM Receive");
}

int main()
{
	signal (SIGALRM, alm);
	alarm(10);
	printf("process id pause\n");
	pause();
	printf("process wakeup\n");
	return 0;
}
