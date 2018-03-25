#include <unistd.h>
#include <stdio.h>
#include <signal.h>


// handler에서 또 다시 alarm을 등록하면 알람이 다시 발생한다.
void my_sig(int signo)
{
	printf("my_sig(%d)\n", signo);
	alarm(1);
}

int main()
{
	signal (SIGALRM, my_sig);
	alarm(1);
	while(1) ;
	return 0;
}
