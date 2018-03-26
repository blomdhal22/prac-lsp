#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/*
 * 문제점: 명령이 라인단위로 처리되지 못한다.
 *         클라이언트가 렉이 걸려서 패킷이 잘려서 온다면, 
 *         제대로 된 처리를못한다.
 * 해결: readline을 구현, 버퍼에서 입력을 읽으면서, \n 읽을 때 리턴
 */

// # mkfifo myfifo

/*
result:
hello

 */

ssize_t readline(int fd, void *vptr, size_t maxlen);

int main(void)
{
	int fd, ret;
	char buffers[1024];
	fd = open("myfifo", O_RDWR);

	while (ret = readline(fd, buffers, sizeof buffers))
		write(1, buffers, ret);
	
	return 0;
}
