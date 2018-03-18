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
 * 3. shell은 ls 수행 후에도, 다시 shell로 돌아온다. 
 * 4. 어떻게 가능한가?
 **/
int main()
{
    char *argv[] = { "ls", (char*)0};

    printf("prompt> ls\n");
    execve("/bin/ls", argv, 0);
    printf("prompt> \n");

    return 0;
}
