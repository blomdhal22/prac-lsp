#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

void sig(int sig)
{
	int i;
	printf("child die(%d)\n", getpid());
}

int main()
{
	signal(SIGINT, sig);
	pause();

	return 0;
}
