#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void show_mask()
{
	sigset_t sigset;

	if (sigprocmask(0, NULL, &sigset) < 0)
		printf("sigprocmask error\n");

	if (sigismember(&sigset, SIGINT))	printf("SIGINT\n");
	if (sigismember(&sigset, SIGQUIT))	printf("SIGQUIT\n");
	if (sigismember(&sigset, SIGUSR1))	printf("SIGUSR1\n");
	if (sigismember(&sigset, SIGALRM))	printf("SIGALRM\n");
}

int main()
{
	sigset_t newmask, oldset;

	sigemptyset(&newmask);	// clean up
	sigaddset(&newmask, SIGQUIT);

	/* add SIGQUIT signal to blocked signal list */
	if (sigprocmask(SIG_BLOCK, &newmask, &oldset) < 0)
		printf("sigprocmask error");

	show_mask();

	/* restore previous signal mask */
	if (sigprocmask(SIG_SETMASK, &oldset, NULL) < 0)
		printf("sigprocmask error");

	return 0;
}
