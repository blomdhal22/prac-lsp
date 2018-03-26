#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void sig_quit(int);

int main()
{
	sigset_t newmask, oldset, pendmask;

	if (signal(SIGQUIT, sig_quit) == SIG_ERR)
		printf("cant't catch SIGQUIT");

	sigemptyset(&newmask);
	sigaddset(&newmask, SIGQUIT);

	/* BLOCK SIGQUIT and save current signal mask */
	if (sigprocmask(SIG_BLOCK, &newmask, &oldset) < 0)
		printf("SIG_BLOCK error");

	sleep(5);		/* SIGQUIT here will remain pending */

	if (sigpending(&pendmask) < 0)
		printf("sigpending error");

	if (sigismember(&pendmask, SIGQUIT))
		printf("\nSIGQUIT pending\n");

	if (sigprocmask(SIG_SETMASK, &oldset, NULL) < 0)
		printf("sigprocmask error");

	printf("SIGQUIT unblocked\n");
	sleep(5);		/* SIGQUIT here will terminate with core file */

	return 0;
}

static void sig_quit(int signo)
{
	printf("caught SIGQUIT\n");

	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
		printf("can't reset SIGQUIT\n");

	return;
}
