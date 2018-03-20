#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/* 
 * 1. ls 실행은 잘 된다.
 * 2. 그러나, execve 이후에 printf가 실행되지 않는다.
 **/
int main()
{
    char *argv[] = { "ls", (char*)0};

    execve("/bin/ls", argv, 0);

    printf("after\n");

    return 0;
}
