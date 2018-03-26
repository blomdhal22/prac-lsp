#include <unistd.h>
#include <stdio.h>
#include <signal.h>

void my_sig(int signo)
{
	printf("my_sig(%d)\n", signo);
}

int main()
{
	signal (SIGALRM, my_sig);
	alarm(3);
	while(1) ;
	return 0;
}
