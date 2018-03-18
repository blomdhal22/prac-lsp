#include <wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/* 
 * 종료 status는 하위 2바이트를 사용
 * 정상 종료는 상위 1바이트
 * 비정상 종료 처리는 하위 1바이트
 */
int main()
{
    int status = 0;

    if (fork() == 0) {
        while (1);
    }
    
    wait(&status);  // 정상: 0x0f00

    if ((status & 0xff) == 0) {
        printf("정상 종료: exit(%d)\n", (status >> 8) & 0xff);
    } else {
        printf("비정상 종료: signo(%d)\n", status & 0xff);
    }



    return 0;
}
