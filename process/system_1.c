#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>

int my_system(char* cmd)
{
    char *argv[] = {cmd, (char*)0};
    char buff[128] = "/bin/";
    pid_t pid;
    int status = 0;
    
    strcat(buff, cmd);

    pid = fork();
    
    if (pid == 0) {
        execve(buff, argv, 0); 
        printf("\nwell done. %d\n", getpid());
        _exit(127);
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
