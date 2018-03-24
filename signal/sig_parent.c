#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#define NUM_CHILD	3

int main(int argc, char **argv)
{
	int pid, chpid[NUM_CHILD];
	int i, status;

	for (i = 0; i < NUM_CHILD; i++) {
		if ((pid = fork()) == 0) {
			execlp("./sig_child", "./sig_child", (char*)0);
		}

		chpid[i] = pid;
	}

	printf("sig_parent : %d child_process num\n", NUM_CHILD);
	sleep(3);

	for(i=0; i<NUM_CHILD; i++)
		kill(chpid[i], SIGINT);

	return 0;
}
