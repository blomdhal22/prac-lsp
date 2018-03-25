#include <stdio.h>
#include <signal.h>

/*
 * SIGINT 발생 시, 프로그램이 종료 된다.
 * SIGINT임에도 불구하고, 종료되지 않기를 원한다면?
 */
int main(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGKILL, SIG_IGN);	// SIGKILL도 무시 가능?

	signal(SIGINT, SIG_DFL);	// Restore
	while(1)
		;

	return 0;
}
