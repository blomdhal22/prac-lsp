#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    FILE *fp;
    int ch;
    fp = fopen(argv[1], "r");
    while ((ch = fgetc(fp)) != EOF) {
        usleep(100000);
        fputc(ch, stdout);
        /* stdout, line buffer 임으로, 라인단위 출력을 피하기 위해 */
        fflush(stdout); 
    }

    fclose(fp);
    return 0;
}
