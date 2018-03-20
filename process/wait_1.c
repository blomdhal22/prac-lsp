#include <wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    int status = 0;

    if (fork() == 0)
        exit(7);
    
    wait(&status);  // 정상: 0x0f00

    printf("status=%d\n", (status >> 8) & 0xff);
    return 0;
}
