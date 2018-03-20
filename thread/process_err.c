#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main()
{
	int fd;

	fd = open("aaa", O_RDONLY);

	printf("fd=%d\n", fd);

	if (fd < 0) {
		printf("errno = %d\n", errno);	
		printf("strerr = %s\n", strerror(errno));	
	}

	return 0;
}
