#include <wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/* 
 * 1. 종료 status는 하위 2바이트를 사용
 * 2. 정상 종료는 상위 1바이트
 * 3. 비정상 종료 처리는 하위 1바이트(signal)
 * 4. 코어 덤프 처리
 * 5. macro 이용해서 처리
 */

void term_stat(int status)
{
    if (WIFEXITED(status)) {
        printf("정상 종료: exit(%d)\n", WEXITSTATUS(status));
    } else if (WIFSIGNALED(status)) {
        printf("비정상 종료: signo(%d) %s\n", WTERMSIG(status)
                ,  WCOREDUMP(status) ? "core dumped" : "");
    }
}

int main()
{
    int status = 0;

    if (fork() == 0) {
        while (1);
    }
    
    wait(&status);  // 정상: 0x0f00

    term_stat(status);

    return 0;
}
