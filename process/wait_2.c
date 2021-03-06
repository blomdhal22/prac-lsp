#include <wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/* 
 * 종료 status는 하위 2바이트를 사용
 */
int main()
{
    int status = 0;

    if (fork() == 0)
        exit(7);
    
    wait(&status);  // 정상: 0x0f00

    if ((status & 0xff) == 0) {
        printf("정상 종료: exit(%d)\n", (status >> 8) & 0xff);
    }



    return 0;
}
