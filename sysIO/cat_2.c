#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	int fd;
	char buff[1024];
	int ret;

	fd = open(argv[1], O_RDONLY);

	while(ret = read(fd, buff, sizeof buff)) {
		write(1, buff, ret);
	}

	close(fd);
	return 0;
}
