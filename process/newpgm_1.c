#include <stdio.h>

// # ./newpgn   one     two
//   argv[0]  argv[1] argv[2]
//   argc=3

int main(int argc, char **argv, char **env)
{
    int i;

    for (i=0; i<argc; i++) {
        printf("argv[%d] = [%s]\n", i, argv[i]);
    }

    printf("----------------\n");
    for (i=0; env[i]; i++) {
        printf("env[%d] = [%s]\n", i, env[i]);
    }

    return 0;
}
