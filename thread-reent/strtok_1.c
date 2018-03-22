#include <stdio.h>
#include <string.h>

int main()
{
	char hp[] = "010-1234-5678";
	char *p;
	p = strtok(hp, "-");

    while (p) {
		printf("[%s]\n", p);
		p = strtok(0, "-");
	}

	return 0;
}
