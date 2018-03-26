#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// # mkfifo myfifo

/*
 * 네트웍 상황이 좋지 않은 경우를 재현해 보자.
 */
int main(void)
{
	int fd;
	char buffers[1024];
	fd = open("myfifo", O_RDWR);

	write(fd, "he\n", 2);
	getchar();

	write(fd, "ll\n", 2);
	getchar();

	write(fd, "o\n", 2);
	return 0;
}
