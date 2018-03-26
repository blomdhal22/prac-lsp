#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/*
 * 문제점: 명령이 라인단위로 처리되지 못한다.
 *         클라이언트가 렉이 걸려서 패킷이 잘려서 온다면, 
 *         제대로 된 처리를못한다.
 */

// # mkfifo myfifo

/*
result:
he<stop>ll<stop>o

 */

int main(void)
{
	int fd, ret;
	char buffers[1024];
	fd = open("myfifo", O_RDWR);

	while (ret = read(fd, buffers, sizeof buffers))
		write(1, buffers, ret);
	
	return 0;
}
