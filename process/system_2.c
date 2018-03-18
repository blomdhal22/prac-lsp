#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

/*
 * arg까지 고련한 system 함수
 */

int my_system(char* cmd)
{
    pid_t pid;
    int status = 0;
    
    pid = fork();
    
    if (pid == 0) {
        //execlp(cmd, cmd,(char*)0); 
        execl("/bin/sh", "sh", "-c", cmd, (char*)0); 
        printf("failed execution: %s\n", cmd);
        _exit(127);     // 잘못된 명령 처리
    } else if (pid <0){
        status = -1;
    } else {
        waitpid(pid, &status, 0);
    }

    return status;
}

int main(int argc, char **argv)
{
    char buff[128] = {0, };

    printf("prompt> ");
    while(fgets(buff, sizeof buff, stdin)) {
        if (buff[strlen(buff) - 1] == '\n')
            buff[strlen(buff) - 1] = 0;
        my_system(buff);
        printf("prompt> ");
    }

    printf("finish.\n");
	return 0;
}
