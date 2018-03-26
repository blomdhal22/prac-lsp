#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// # mkfifo myfifo

/*
 */
int main(void)
{
	int fd;
	char buffers[1024];
	fd = open("myfifo", O_RDWR);
	write(fd, "hello\n", 6);
	return 0;
}
