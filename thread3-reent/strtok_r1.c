#include <stdio.h>
#include <string.h>

int main()
{
	char hp[] = "010-1234-5678";
	char *p;
	char *saveptr;
	p = strtok_r(hp, "-", &saveptr);

    while (p) {
		printf("[%s]\n", p);
		p = strtok_r(0, "-", &saveptr);
	}

	return 0;
}
