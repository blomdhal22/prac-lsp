#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <syslog.h>

int daemon_init()
{
	pid_t pid;
	int i;

	if (fork() > 0)
		exit(0);

	setsid();		/* become session leader */
	chdir("/");		/* change working dir */
	umask(0);		/* clear out file mode creation mast */

	for (i=0; i<64; i++)
		close(i);

	signal(SIGHCLD, SIG_IGN);

	return 0;
}


int main(void)
{
	daemon_init();
	// printf("daemon\n");
	syslog(1, "my-daemon: %s\n", "daemon");
	//sleep(20);
	while(1)
		;
	return 0;
}
