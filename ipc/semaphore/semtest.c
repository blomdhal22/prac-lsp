#include "semlib.h"
#include <stdio.h>

int main()
{
	int semid = CreateSEM(5000);
	p(semid);
	printf("Enter Critical Section.\n");
	getchar();
	v(semid);
	printf("Leave Critical Section.\n");
	return 0;
}
