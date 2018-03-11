#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    FILE *fp;
    char buff[128];
    fp = fopen(argv[1], "r");
    while (fgets(buff, sizeof buff, fp)) {
        usleep(100000);
        fputs(buff, stdout);
        /* stdout, line buffer 임으로, 라인단위 출력을 피하기 위해 */
        fflush(stdout); 
    }

    fclose(fp);
    return 0;
}
