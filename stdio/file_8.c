#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    FILE *fp;
    char buff[1000];
    int ret;
    fp = fopen(argv[1], "r");
    while (ret = fread(buff, 1, sizeof buff, fp)) {
        usleep(100000);
        /*printf("ret=%d\n", ret);*/
        fwrite(buff, 1, ret, stdout);
        /* stdout, line buffer 임으로, 라인단위 출력을 피하기 위해 */
        fflush(stdout); 
    }

    fclose(fp);
    return 0;
}
