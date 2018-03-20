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
 * 4. 어떻게 가능한가? fork를 이용하자
 * 5. 그러나 ls의 출력 결과와, prompt가 겹치는 현상이 발생한다.
 **/
int main()
{
    char *argv[] = { "ls", (char*)0};

    printf("prompt> ls\n");

    if (fork() == 0)
        execve("/bin/ls", argv, 0);

    printf("prompt> \n");

    return 0;
}
