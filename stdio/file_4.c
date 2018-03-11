#include <stdio.h>

int main()
{
    char buff[100];
    int ret;

    while(fgets(buff, sizeof buff, stdin))
        fputs(buff, stdout);

    return 0;
}
