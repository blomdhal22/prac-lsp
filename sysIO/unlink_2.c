#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	int fd, ret;
	char buff[1024];
	fd = open("zzz", O_RDWR | O_CREAT| O_TRUNC, 0666);
	getchar();
	unlink("zzz");
	getchar();
	write(fd, "hello\n", 6);
	lseek(fd, 0, SEEK_SET);

	ret = read(fd, buff, sizeof buff);
	write(1, buff, ret);

	for (;;)
		;
	return 0;
}
