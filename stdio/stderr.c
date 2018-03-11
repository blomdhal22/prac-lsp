#include <stdio.h>
#include <unistd.h>

int main(void)
{
    fprintf(stderr, "hello");
    sleep(3);
    return 0;
}
